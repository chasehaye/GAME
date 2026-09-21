#pragma once
#include <string>

class Player
{
public:
    Player();

    void create();

private:
    std::string name;
    int health;
    int attackDamage;
};