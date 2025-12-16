#include "../include/NPC/Werewolf.h"

Werewolf::Werewolf(int x, int y) : NPC(WerewolfType, x, y, 40, 5) {}
Werewolf::Werewolf(std::istream &is) : NPC(WerewolfType, is) {}

bool Werewolf::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Werewolf>(this,[](Werewolf*){}));
}

void Werewolf::print()
{
    std::cout << *this;
}

void Werewolf::save(std::ostream &os) 
{
    os << WerewolfType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Werewolf &Werewolf)
{
    os << "Werewolf: " << *static_cast<NPC *>(&Werewolf) << std::endl;
    return os;
}