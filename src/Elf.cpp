#include "../include/NPC/Elf.h"

Elf::Elf(int x, int y) : NPC(ElfType, x, y, 10, 50) {}
Elf::Elf(std::istream &is) : NPC(ElfType, is) {}

bool Elf::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Elf>(this,[](Elf*){}));
}

void Elf::print()
{
    std::cout << *this;
}

void Elf::save(std::ostream &os) 
{
    os << ElfType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Elf &Elf)
{
    os << "Elf: " << *static_cast<NPC *>(&Elf) << std::endl;
    return os;
}