#pragma once
#include "../NPC.h"

struct Muskrat : public NPC
{
    Muskrat(int x, int y);
    Muskrat(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Muskrat &Muskrat);
};