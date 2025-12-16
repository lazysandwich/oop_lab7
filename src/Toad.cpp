#include "../include/NPC/Toad.h"

Toad::Toad(int x, int y) : NPC(ToadType, x, y, 1, 10) {}
Toad::Toad(std::istream &is) : NPC(ToadType, is) {}

bool Toad::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Toad>(this,[](Toad*){}));
}

void Toad::print()
{
    std::cout << *this;
}

void Toad::save(std::ostream &os) 
{
    os << ToadType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Toad &Toad)
{
    os << "Toad: " << *static_cast<NPC *>(&Toad) << std::endl;
    return os;
}