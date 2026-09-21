#include "Game.h"
#include <iostream>

Game::Game()
{
    running = true;
}

void Game::run()
{
    while (running)
    {
        std::cout << "Game is running!\n";

        char input;
        std::cin >> input;

        if (input == 'q')
        {
            running = false;
        }
    }
}