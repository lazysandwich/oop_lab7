#pragma once
#include "../NPC.h"

struct Toad : public NPC
{
    Toad(int x, int y);
    Toad(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Toad &Toad);
};