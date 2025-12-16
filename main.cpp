#include "include/all_file_in_1_file.h"
#include <sstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <optional>
#include <array>
#include <atomic>

std::atomic<bool> stop{false};

using namespace std::chrono_literals;
std::mutex print_mutex;

class TextObserver : public IFightObserver
{
private:
    TextObserver() {};

public:
    static std::shared_ptr<IFightObserver> get()
    {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override
    {
        if (win)
        {
            std::lock_guard<std::mutex> lck(print_mutex);
            std::cout << std::endl
                      << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

std::shared_ptr<NPC> factory(std::istream &is)
{
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type)
    {
        switch (type)
        {
        case BanditType:
            result = std::make_shared<Bandit>(is);
            break;
        case BearType:
            result = std::make_shared<Bear>(is);
            break;
        case BitternType:
            result = std::make_shared<Bittern>(is);
            break;
        case BullType:
            result = std::make_shared<Bull>(is);
            break;   
        case DragonType:
            result = std::make_shared<Dragon>(is);
            break;
        case DruidType:
            result = std::make_shared<Druid>(is);
            break;
        case ElfType:
            result = std::make_shared<Elf>(is);
            break;
        case KnightType:
            result = std::make_shared<Knight>(is);
            break;
        case MuskratType:
            result = std::make_shared<Muskrat>(is);
            break;
        case OrcType:
            result = std::make_shared<Orc>(is);
            break;
        case PegasusType:
            result = std::make_shared<Pegasus>(is);
            break;
        case PrincessType:
            result = std::make_shared<Princess>(is);
            break;   
        case SlaverType:
            result = std::make_shared<Slaver>(is);
            break;
        case SquirrelType:
            result = std::make_shared<Squirrel>(is);
            break;
        case ToadType:
            result = std::make_shared<Toad>(is);
            break;
        case WerewolfType:
            result = std::make_shared<Werewolf>(is);
            break;
        }
    }
    else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y)
{
    std::shared_ptr<NPC> result;
    switch (type)
    {
    case BanditType:
        result = std::make_shared<Bandit>(x, y);
        break;
    case BearType:
        result = std::make_shared<Bear>(x, y);
        break;
    case BitternType:
        result = std::make_shared<Bittern>(x, y);
        break;
    case BullType:
        result = std::make_shared<Bull>(x, y);
        break;
    case DragonType:
        result = std::make_shared<Dragon>(x, y);
        break;
    case DruidType:
        result = std::make_shared<Druid>(x, y);
        break;
    case ElfType:
        result = std::make_shared<Elf>(x, y);
        break;
    case KnightType:
        result = std::make_shared<Knight>(x, y);
        break;
    case MuskratType:
        result = std::make_shared<Muskrat>(x, y);
        break;
    case OrcType:
        result = std::make_shared<Orc>(x, y);
        break;
    case PegasusType:
        result = std::make_shared<Pegasus>(x, y);
        break;
    case PrincessType:
        result = std::make_shared<Princess>(x, y);
        break;
    case SlaverType:
        result = std::make_shared<Slaver>(x, y);
        break;
    case SquirrelType:
        result = std::make_shared<Squirrel>(x, y);
        break;
    case ToadType:
        result = std::make_shared<Toad>(x, y);
        break;
    case WerewolfType:
        result = std::make_shared<Werewolf>(x, y);
        break;
    default:
        break;
    }
    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

void save(const set_t &array, const std::string &filename)
{
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        n->print();
    return os;
}

set_t fight(const set_t &array, size_t distance)
{
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) &&
                attacker->is_close(defender, distance) &&
                defender->accept(attacker))
                dead_list.insert(defender);

    return dead_list;
}

struct print : std::stringstream
{
    ~print()
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lck(print_mutex);
        std::cout << this->str();
        std::cout.flush();
    }
};

struct FightEvent
{
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager
{
private:
    std::queue<FightEvent> events;
    FightManager() {}
    std::mutex mtx;
public:
    static FightManager &get()
    {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent &&event)
    {
        std::lock_guard<std::mutex> lck(mtx);
        events.push(event);
    }

    void operator()()
    {
        while (!stop.load())
        {
            std::optional<FightEvent> event;
            if (!events.empty())
            {
                std::lock_guard<std::mutex> lck(mtx);
                event = events.back();
                events.pop();
            }

            if (event)
                if (event->attacker->is_alive())
                    if (event->defender->is_alive()) {
                        int attack_a = 1 + rand() % 6;
                        int defense_b = 1 + rand() % 6;
                        bool a_kills = attack_a > defense_b;
                        if (a_kills) 
                            event->defender->must_die();
                    }
        }
    }
};

int main() {
    set_t array;
    const int MAX_X{100};
    const int MAX_Y{100};

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i)
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % MAX_X,
                             std::rand() % MAX_Y));

    std::cout << "Starting list:" << std::endl
              << array;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&array, MAX_X, MAX_Y]()
                            {
            while (!stop.load()) {
                for (const std::shared_ptr<NPC> & npc : array)
                    if(npc->is_alive()) {
                        int dist_x = std::rand() % (1 + npc->move_dist);
                        int dist_y = npc->move_dist - dist_x;
                        int sign_x = std::rand() % 2;
                        int sign_y = std::rand() % 2;
                        if (sign_x == 0) 
                            dist_x *= -1;
                        if (sign_y == 0) 
                            dist_y *= -1;
                        npc->move(dist_x, 
                                  dist_y, MAX_X, MAX_Y);
                    }

                for (const std::shared_ptr<NPC> & npc : array)
                    for (const std::shared_ptr<NPC> & other : array) 
                        if ((other != npc) && (npc->is_alive()) && (other->is_alive()) && (npc->is_close(other, npc->kill_dist)))
                          FightManager::get().add_event({npc, other});
                std::this_thread::sleep_for(10ms);
             }        
        });

    const int grid{20}, step_x{MAX_X / grid}, step_y{MAX_Y / grid};
    std::array<char, grid * grid> fields{0};
    auto start = std::chrono::steady_clock::now();
    while (!stop.load()) {
        if (std::chrono::steady_clock::now() - start >= 30s)
            stop.store(true);
        fields.fill(0);
        for (const std::shared_ptr<NPC> &npc : array) {
            const auto [x, y] = npc->position();
            int i = x / step_x;
            int j = y / step_y;
            if (npc->is_alive()) {
                switch (npc->get_type())
                {
                case BanditType:
                    fields[i + grid * j] = 'B';
                    break;
                case BearType:
                    fields[i + grid * j] = '1';
                    break;
                case BitternType:
                    fields[i + grid * j] = '2';
                    break;
                case BullType:
                    fields[i + grid * j] = '3';
                    break;
                case DragonType:
                    fields[i + grid * j] = 'D';
                    break;
                case DruidType:
                    fields[i + grid * j] = '4';
                    break;
                case ElfType:
                    fields[i + grid * j] = 'E';
                    break;
                case KnightType:
                    fields[i + grid * j] = 'K';
                    break;
                case MuskratType:
                    fields[i + grid * j] = 'M';
                    break;
                case OrcType:
                    fields[i + grid * j] = 'O';
                    break;
                case PegasusType:
                    fields[i + grid * j] = 'P';
                    break;
                case PrincessType:
                    fields[i + grid * j] = '5';
                    break;
                case SlaverType:
                    fields[i + grid * j] = 'S';
                    break;
                case SquirrelType:
                    fields[i + grid * j] = '6';
                    break;
                case ToadType:
                    fields[i + grid * j] = 'T';
                    break;
                case WerewolfType:
                    fields[i + grid * j] = '7';
                    break;
                default:
                    break;
                }
            }
            else
                fields[i + grid * j] = '.';
        }
        for (int j = 0; j < grid; ++j) {
            for (int i = 0; i < grid; ++i) {
                char c = fields[i + j * grid];
                if (c != 0)
                    std::cout << "[" << c << "]";
                else
                    std::cout << "[ ]";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(1s);
    };

    move_thread.join();
    fight_thread.join();

    return 0;
}