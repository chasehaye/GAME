#pragma once
#include <vector>
#include "world/map/Cell.h"

class Grid {

public:
    Grid(int width, int height);

    // The real cells around this one (up to 8, diagonals included), not copies.
    std::vector<Cell*> getNeighboringCells(const Cell& cell);
    Cell* getCell(int x, int y);

private:
    bool isInBounds(int x, int y) const;

    std::vector<Cell> cells;
    int width;
    int height;
};
