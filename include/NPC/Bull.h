#pragma once
#include "../NPC.h"

struct Bull : public NPC
{
    Bull(int x, int y);
    Bull(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bull &Bull);
};