#pragma once
#include "../NPC.h"

struct Squirrel : public NPC
{
    Squirrel(int x, int y);
    Squirrel(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Squirrel &Squirrel);
};