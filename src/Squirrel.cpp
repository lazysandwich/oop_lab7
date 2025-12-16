#include "../include/NPC/Squirrel.h"

Squirrel::Squirrel(int x, int y) : NPC(SquirrelType, x, y, 5, 5) {}
Squirrel::Squirrel(std::istream &is) : NPC(SquirrelType, is) {}

bool Squirrel::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Squirrel>(this,[](Squirrel*){}));
}

void Squirrel::print()
{
    std::cout << *this;
}

void Squirrel::save(std::ostream &os) 
{
    os << SquirrelType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Squirrel &Squirrel)
{
    os << "Squirrel: " << *static_cast<NPC *>(&Squirrel) << std::endl;
    return os;
}