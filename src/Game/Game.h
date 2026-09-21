#pragma once
#include <string>

class Game {
    
public:
    Game();

    void run();

private:
    void quit();
    bool running;
    void processInput(char input);
};