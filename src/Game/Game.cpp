#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game()
{
    running = true;
}

void Game::processInput(char input)
{
    std::cout << "Got your input -> " << input << "\n";
}

void Game::quit()
{
    std::cout << "Are you sure you want to quit? (y/n): ";

    char confirm;
    std::cin >> confirm;

    if (confirm == 'y')
    {
        running = false;
    }
}

void Game::run()
{
    std::cout << "Press (q) any time to quit" << "\n";

    Player player;
    player.create();

    
    
    while (running)
    {
        char input;
        std::cin >> input;
        if (input == 'q')
        {
            quit();
        }
        else
        {
            processInput(input);
        }
    }
}