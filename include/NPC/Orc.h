#pragma once
#include "../NPC.h"

struct Orc : public NPC
{
    Orc(int x, int y);
    Orc(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Orc &Muskrat);
};