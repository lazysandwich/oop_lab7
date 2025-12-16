#include "../include/NPC/Princess.h"

Princess::Princess(int x, int y) : NPC(PrincessType, x, y, 1, 1) {}
Princess::Princess(std::istream &is) : NPC(PrincessType, is) {}

bool Princess::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Princess>(this,[](Princess*){}));
}

void Princess::print()
{
    std::cout << *this;
}

void Princess::save(std::ostream &os) 
{
    os << PrincessType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Princess &Princess)
{
    os << "Princess: " << *static_cast<NPC *>(&Princess) << std::endl;
    return os;
}