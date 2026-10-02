#pragma once
#include "raylib.h"
#include "input/InputHandler.h"
#include "input/PlayerController.h"
#include "render/PixelMapper.h"
#include "render/Renderer.h"
#include "world/World.h"

class Game {

public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void run();

private:
    World world; // game state: the grid, everything on it, and the rules for changing it

    PixelMapper pixelMapper; // display: where the grid sits on screen (cells <-> pixels)

    Renderer render; // draws using the two above

    InputState input; // this frame's input, refreshed at the top of every frame by handleInput()

    PlayerController playerController; // turns this frame's input into actions, through the active tool

    void handleInput();

    // Moves the game forward by dt seconds: everything that happens without player input.
    void updateGameState(float dt);
};
