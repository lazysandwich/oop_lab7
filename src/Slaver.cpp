#include "../include/NPC/Slaver.h"

Slaver::Slaver(int x, int y) : NPC(SlaverType, x, y, 10, 10) {}
Slaver::Slaver(std::istream &is) : NPC(SlaverType, is) {}

bool Slaver::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Slaver>(this,[](Slaver*){}));
}

void Slaver::print()
{
    std::cout << *this;
}

void Slaver::save(std::ostream &os) 
{
    os << SlaverType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Slaver &Slaver)
{
    os << "Slaver: " << *static_cast<NPC *>(&Slaver) << std::endl;
    return os;
}