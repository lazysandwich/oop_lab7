#include "../include/NPC/Druid.h"

Druid::Druid(int x, int y) : NPC(DruidType, x, y, 10, 10) {}
Druid::Druid(std::istream &is) : NPC(DruidType, is) {}

bool Druid::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Druid>(this,[](Druid*){}));
}

void Druid::print()
{
    std::cout << *this;
}

void Druid::save(std::ostream &os) 
{
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Druid &druid)
{
    os << "Druid: " << *static_cast<NPC *>(&druid) << std::endl;
    return os;
}