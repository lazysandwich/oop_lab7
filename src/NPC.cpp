#include "../include/NPC.h"

NPC::NPC(NpcType t, int _x, int _y, int move_distance, int kill_distance)
    : type(t), x(_x), y(_y), move_dist(move_distance), kill_dist(kill_distance), alive(true) {}

    NPC::NPC(NpcType t, std::istream &is) : type(t), alive(true) {
        is >> x >> y >> move_dist >> kill_dist;
    }

void NPC::subscribe(std::shared_ptr<IFightObserver> observer)
{
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win)
{
    auto self = shared_from_this();
    for (auto &o : observers)
        o->on_fight(self, defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance)
{
    std::lock_guard<std::mutex> lck(mtx);
    auto [ox, oy] = other->position();
    int dx = x - ox;
    int dy = y - oy;
    return dx * dx + dy * dy <= int(distance * distance);
}

bool NPC::fight(std::shared_ptr<NPC> other) {
    if (!other || !other->is_alive())
        return false;
    int attack = rand() % 6 + 1;
    int defense = rand() % 6 + 1;
    bool win = attack >= defense;
    if (win)
        other->must_die();
    else
        must_die();
    fight_notify(other, win);
    return win;
}

NpcType NPC::get_type() const
{
    return type;
}

std::pair<int, int> NPC::position() const
{
    return {x, y};
}

void NPC::save(std::ostream &os)
{
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc)
{
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y)
{
    std::lock_guard<std::mutex> lck(mtx);

    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y += shift_y;
}

bool NPC::is_alive() const
{
    return alive;
}

void NPC::must_die()
{
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}