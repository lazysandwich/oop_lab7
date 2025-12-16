#include "../include/NPC/Dragon.h"

Dragon::Dragon(int x, int y) : NPC(DragonType, x, y, 50, 30) {}
Dragon::Dragon(std::istream &is) : NPC(DragonType, is) {}

bool Dragon::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Dragon>(this,[](Dragon*){}));
}

void Dragon::print()
{
    std::cout << *this;
}

void Dragon::save(std::ostream &os) 
{
    os << DragonType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Dragon &dragon)
{
    os << "dragon: " << *static_cast<NPC *>(&dragon) << std::endl;
    return os;
}