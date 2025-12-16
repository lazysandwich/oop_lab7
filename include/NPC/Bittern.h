#pragma once
#include "../NPC.h"

struct Bittern : public NPC
{
    Bittern(int x, int y);
    Bittern(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bittern &Bittern);
};