#pragma once
#include "../NPC.h"

struct Pegasus : public NPC
{
    Pegasus(int x, int y);
    Pegasus(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Pegasus &Pegasus);
};