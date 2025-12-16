#include "../include/NPC/Bull.h"

Bull::Bull(int x, int y) : NPC(BullType, x, y, 30, 10) {}
Bull::Bull(std::istream &is) : NPC(BullType, is) {}

bool Bull::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Bull>(this,[](Bull*){}));
}

void Bull::print()
{
    std::cout << *this;
}

void Bull::save(std::ostream &os) 
{
    os << BullType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Bull &Bull)
{
    os << "Bull: " << *static_cast<NPC *>(&Bull) << std::endl;
    return os;
}