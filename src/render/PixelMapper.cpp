#include "render/PixelMapper.h"
#include <algorithm>
#include "world/map/Cell.h"
#include "world/map/Grid.h"

namespace {
// Smallest gap kept between the grid and the screen edge, in pixels.
constexpr int kPadding = 50;
}

void PixelMapper::fitToScreen(int newGridWidth, int newGridHeight, int screenWidth, int screenHeight) {
    gridWidth = newGridWidth;
    gridHeight = newGridHeight;

    const int availableWidth = screenWidth - kPadding * 2;
    const int availableHeight = screenHeight - kPadding * 2;

    const int cellWidth = availableWidth / gridWidth;
    const int cellHeight = availableHeight / gridHeight;

    cellSize = std::min(cellWidth, cellHeight);

    offsetX = (screenWidth - gridWidth * cellSize) / 2;
    offsetY = (screenHeight - gridHeight * cellSize) / 2;
}

Cell* PixelMapper::cellAt(Vector2 screenPos, Grid& grid) const {
    const float localX = screenPos.x - offsetX;
    const float localY = screenPos.y - offsetY;

    if (localX < 0 || localY < 0 || cellSize <= 0) {
        return nullptr;
    }

    const int gridX = static_cast<int>(localX) / cellSize;
    const int gridY = static_cast<int>(localY) / cellSize;

    return grid.getCell(gridX, gridY);
}

Vector2 PixelMapper::cellCenter(const Cell& cell) const {
    return {
        offsetX + cell.getX() * cellSize + cellSize / 2.0f,
        offsetY + cell.getY() * cellSize + cellSize / 2.0f
    };
}

Rectangle PixelMapper::cellBounds(const Cell& cell) const {
    return {
        static_cast<float>(offsetX + cell.getX() * cellSize),
        static_cast<float>(offsetY + cell.getY() * cellSize),
        static_cast<float>(cellSize),
        static_cast<float>(cellSize)
    };
}

int PixelMapper::getCellSize() const {
    return cellSize;
}

int PixelMapper::getOffsetX() const {
    return offsetX;
}

int PixelMapper::getOffsetY() const {
    return offsetY;
}

int PixelMapper::getGridWidth() const {
    return gridWidth;
}

int PixelMapper::getGridHeight() const {
    return gridHeight;
}
