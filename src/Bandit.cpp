#include "../include/NPC/Bandit.h"

Bandit::Bandit(int x, int y) : NPC(BanditType, x, y, 10, 10) {}
Bandit::Bandit(std::istream &is) : NPC(BanditType, is) {}

bool Bandit::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Bandit>(this, [](Bandit*){}));
}
void Bandit::print()
{
    std::cout << *this;
}

void Bandit::save(std::ostream &os) 
{
    os << BanditType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Bandit &bandit)
{
    os << "Bandit: " << *static_cast<NPC *>(&bandit) << std::endl;
    return os;
}