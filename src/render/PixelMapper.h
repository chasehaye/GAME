#pragma once
#include "raylib.h"

class Cell;
class Grid;

// Where the grid sits on screen. The one place that converts between cells and pixels:
// drawing uses it cell -> pixel, mouse input uses it pixel -> cell.
class PixelMapper {

public:
    // Picks the largest square cell size that fits the grid on the screen with padding,
    // and centers the grid. Call again whenever the grid or screen size changes.
    void fitToScreen(int newGridWidth, int newGridHeight, int screenWidth, int screenHeight);

    // The cell under a screen position, or nullptr if the position is off the grid.
    Cell* cellAt(Vector2 screenPos, Grid& grid) const;

    Vector2 cellCenter(const Cell& cell) const;
    Rectangle cellBounds(const Cell& cell) const;

    int getCellSize() const;
    int getOffsetX() const;
    int getOffsetY() const;
    int getGridWidth() const;
    int getGridHeight() const;

private:
    int cellSize = 0;
    int offsetX = 0;     // pixel position of the grid's top-left corner
    int offsetY = 0;
    int gridWidth = 0;   // in cells
    int gridHeight = 0;
    int kPadding = 50;
};
