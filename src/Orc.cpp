#include "../include/NPC/Orc.h"

Orc::Orc(int x, int y) : NPC(OrcType, x, y, 20, 10) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

bool Orc::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Orc>(this,[](Orc*){}));
}

void Orc::print()
{
    std::cout << *this;
}

void Orc::save(std::ostream &os) 
{
    os << OrcType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Orc &Orc)
{
    os << "Orc: " << *static_cast<NPC *>(&Orc) << std::endl;
    return os;
}