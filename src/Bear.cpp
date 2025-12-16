#include "../include/NPC/Bear.h"

Bear::Bear(int x, int y) : NPC(BearType, x, y, 5, 10) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

bool Bear::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Bear>(this,[](Bear*){}));
}

void Bear::print()
{
    std::cout << *this;
}

void Bear::save(std::ostream &os) 
{
    os << BearType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Bear &Bear)
{
    os << "Bear: " << *static_cast<NPC *>(&Bear) << std::endl;
    return os;
}