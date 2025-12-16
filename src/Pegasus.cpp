#include "../include/NPC/Pegasus.h"

Pegasus::Pegasus(int x, int y) : NPC(PegasusType, x, y, 30, 10) {}
Pegasus::Pegasus(std::istream &is) : NPC(PegasusType, is) {}

bool Pegasus::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Pegasus>(this,[](Pegasus*){}));
}

void Pegasus::print()
{
    std::cout << *this;
}

void Pegasus::save(std::ostream &os) 
{
    os << PegasusType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Pegasus &Pegasus)
{
    os << "Pegasus: " << *static_cast<NPC *>(&Pegasus) << std::endl;
    return os;
}