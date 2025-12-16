#pragma once
#include "../NPC.h"

struct Bandit : public NPC
{
    Bandit(int x, int y);
    Bandit(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bandit &bandit);
};