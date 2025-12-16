#pragma once
#include "../NPC.h"

struct Princess : public NPC
{
    Princess(int x, int y);
    Princess(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Princess &Princess);
};