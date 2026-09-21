#include "Player.h"
#include <iostream>

Player::Player()
{
    name = "";
    health = 100;
    attackDamage = 10;
}

void Player::create()
{
    std::cout << "Enter your player name then press enter:\n";

    std::cin >> name;

    std::cout << "Name set to " << name << "\n";
}