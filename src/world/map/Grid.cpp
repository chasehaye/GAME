#include "world/map/Grid.h"

Grid::Grid(int width, int height) : width(width), height(height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cells.emplace_back(x, y);
        }
    }
}

bool Grid::isInBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

Cell* Grid::getCell(int x, int y) {
    if (!isInBounds(x, y)) {
        return nullptr;
    }
    return &cells[y * width + x];
}

std::vector<Cell*> Grid::getNeighboringCells(const Cell& cell) {
    // x/y steps to each neighbor: up, right, down, left, then the four diagonals.
    constexpr int kOffsets[8][2] = {
        {0, -1}, {1, 0}, {0, 1}, {-1, 0},
        {-1, -1}, {1, -1}, {-1, 1}, {1, 1}
    };

    std::vector<Cell*> neighbors;
    for (const auto& offset : kOffsets) {
        // getCell returns nullptr past the grid's edge, so edge cells get fewer neighbors.
        if (Cell* neighbor = getCell(cell.getX() + offset[0], cell.getY() + offset[1])) {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}
