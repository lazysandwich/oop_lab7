#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <new>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>
#include <shared_mutex>

struct NPC;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType
{
    Unknown = 0,
    BanditType = 1,
    BearType = 2,
    BitternType = 3,
    BullType = 4,
    DragonType = 5,
    DruidType = 6,
    ElfType = 7,
    KnightType = 8,
    MuskratType = 9,
    OrcType = 10,
    PegasusType = 11,
    PrincessType = 12,
    SlaverType = 13,
    SquirrelType = 14,
    ToadType = 15,
    WerewolfType = 16
};

struct IFightObserver
{
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

class NPC : public std::enable_shared_from_this<NPC>
{
private:
    std::mutex mtx;

    NpcType type;
    int x{0};
    int y{0};
    bool alive{true};

    std::vector<std::shared_ptr<IFightObserver>> observers;

public:
    int move_dist;
    int kill_dist;
    
    NPC(NpcType t, int _x, int _y, int move_distance, int kill_distance);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance);

    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;
    bool fight(std::shared_ptr<NPC> other);

    virtual void print() = 0;
    std::pair<int, int> position() const;
    NpcType get_type() const;

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);

    void move(int shift_x, int shift_y, int max_x, int max_y);

    bool is_alive() const;
    void must_die();
};