#pragma once
#include "../NPC.h"

struct Knight : public NPC
{
    Knight(int x, int y);
    Knight(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    friend std::ostream &operator<<(std::ostream &os, Knight &knight);

    bool accept(std::shared_ptr<NPC> visitor) override;
};