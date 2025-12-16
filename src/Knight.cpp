#include "../include/NPC/Knight.h"

Knight::Knight(int x, int y) : NPC(KnightType, x, y, 30, 10) {}
Knight::Knight(std::istream &is) : NPC(KnightType, is) {}

void Knight::print()
{
    std::cout << *this;
}

bool Knight::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Knight>(this,[](Knight*){}));
}

void Knight::save(std::ostream &os)
{
    os << KnightType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Knight &knight)
{
    os << "knight: " << *static_cast<NPC *>(&knight) << std::endl;
    return os;
}