#include "../include/NPC/Bittern.h"

Bittern::Bittern(int x, int y) : NPC(BitternType, x, y, 50, 10) {}
Bittern::Bittern(std::istream &is) : NPC(BitternType, is) {}

bool Bittern::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Bittern>(this,[](Bittern*){}));
}

void Bittern::print()
{
    std::cout << *this;
}

void Bittern::save(std::ostream &os) 
{
    os << BitternType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Bittern &Bittern)
{
    os << "Bittern: " << *static_cast<NPC *>(&Bittern) << std::endl;
    return os;
}