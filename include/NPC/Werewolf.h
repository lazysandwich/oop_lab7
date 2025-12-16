#pragma once
#include "../NPC.h"

struct Werewolf : public NPC
{
    Werewolf(int x, int y);
    Werewolf(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Werewolf &Werewolf);
};