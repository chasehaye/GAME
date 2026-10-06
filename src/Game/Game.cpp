#include "game/Game.h"
#include "raylib.h"

namespace {
// grid size in cells
constexpr int kGridWidth = 30;
constexpr int kGridHeight = 20;
}

Game::Game() : world(kGridWidth, kGridHeight) {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    // 0, 0 = use the monitor's resolution
    InitWindow(0, 0, "Game Dev Project");
    ToggleFullscreen();
    SetTargetFPS(240);
    // Size and center the grid on screen
    pixelMapper.fitToScreen(kGridWidth, kGridHeight, GetScreenWidth(), GetScreenHeight());

    // TEMPORARY: one house placed by hand so it can be seen and connected to.
    // Replace with random spawning in World::update once that exists.
    world.placeHouse(world.getGrid().getCell(kGridWidth / 2, kGridHeight / 2));
}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        handleInput();
        updateGameState(GetFrameTime());
        render.drawFrame(pixelMapper, world);
    }
}

void Game::handleInput() {
    input = readInput(pixelMapper, world.getGrid());
    playerController.update(input, world, pixelMapper);
}

void Game::updateGameState(float dt) {
    world.update(dt);
}
