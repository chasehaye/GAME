#pragma once
#include <memory>
#include <vector>
#include "world/map/Grid.h"
#include "world/worldobjects/Road.h"

class Cell;

// All game state, and the rules for changing it. The only place that creates, owns,
// and destroys world objects, and the only place that changes what's on a cell.
// Knows nothing about input, the screen, or raylib.
class World {

public:
    World(int width, int height);

    Grid& getGrid();
    const Grid& getGrid() const;

    // Road logic ---------------------------------------------------------------------------------

    // The road on this cell, or nullptr if the cell is missing, empty, or holds
    // something that isn't a road.
    Road* roadAt(Cell* cell) const;

    // Puts a road on the cell if it's empty, and returns it. If the cell already has a
    // road, returns that one instead. Returns nullptr if the cell is missing or holds
    // something that isn't a road.
    Road* placeRoad(Cell* cell);

    // Links two neighboring cells with road, placing a road on either one first if
    // needed. Does nothing if the cells aren't neighbors or can't hold a road.
    void connectRoads(Cell* a, Cell* b);

    // Removes the road on the cell, if there is one. Safe to call on empty or
    // missing cells.
    void removeRoad(Cell* cell);

    const std::vector<std::unique_ptr<Road>>& getRoads() const;

    // Update logic -------------------------------------------------------------------------------

    // Moves the world forward by dt seconds: everything that happens without the player.
    void update(float dt);

private:
    Grid grid;

    // Owns every road. Cells and other roads only point at them.
    std::vector<std::unique_ptr<Road>> roads;
};
