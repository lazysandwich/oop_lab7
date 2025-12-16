#pragma once
#include "../NPC.h"

struct Bear : public NPC
{
    Bear(int x, int y);
    Bear(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bear &Bear);
};