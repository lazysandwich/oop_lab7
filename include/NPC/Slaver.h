#pragma once
#include "../NPC.h"

struct Slaver : public NPC
{
    Slaver(int x, int y);
    Slaver(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Slaver &Slaver);
};