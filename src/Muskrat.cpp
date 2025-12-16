#include "../include/NPC/Muskrat.h"

Muskrat::Muskrat(int x, int y) : NPC(MuskratType, x, y, 5, 20) {}
Muskrat::Muskrat(std::istream &is) : NPC(MuskratType, is) {}

bool Muskrat::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Muskrat>(this,[](Muskrat*){}));
}

void Muskrat::print()
{
    std::cout << *this;
}

void Muskrat::save(std::ostream &os) 
{
    os << MuskratType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Muskrat &Muskrat)
{
    os << "Muskrat: " << *static_cast<NPC *>(&Muskrat) << std::endl;
    return os;
}