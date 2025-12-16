#pragma once
#include "../NPC.h"

struct Druid : public NPC
{
    Druid(int x, int y);
    Druid(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    
    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Druid &druid);
};