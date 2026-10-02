#pragma once

class Cell;
class PixelMapper;
class World;

// Draws the game. Only reads what it's given; it never changes game state.
class Renderer {

public:
    // Draws one whole frame: begin, clear, every layer in order, end.
    void drawFrame(const PixelMapper& pixelMapper, const World& world, const Cell* hoveredCell) const;

private:
    void drawGrid(const PixelMapper& pixelMapper) const;
    void drawRoads(const PixelMapper& pixelMapper, const World& world) const;
    void drawHover(const PixelMapper& pixelMapper, const Cell* hoveredCell) const;
};
