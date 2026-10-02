#pragma once
#include "raylib.h"

class Cell;
class Grid;
class PixelMapper;

// Everything the player did this frame, read once at the top of the frame and passed
// to whoever needs it. Facts only: what each input *means* is decided by the receiver.
struct InputState {
    Vector2 mousePosition{};           // mouse position in screen pixels
    Cell* hoveredCell = nullptr;       // cell under the mouse, or nullptr if off the grid

    bool leftMousePressed = false;     // left button went down this frame
    bool leftMouseDown = false;        // left button held (also true on the frame it went down)
    bool leftMouseReleased = false;    // left button came up this frame
    bool rightMouseDown = false;       // right button held (also true on the frame it went down)

    bool escapePressed = false;        // Esc went down this frame
};

// Reads the mouse and keyboard for this frame. The only place that calls raylib's
// input functions, so every part of the game sees the same picture of the frame.
InputState readInput(const PixelMapper& pixelMapper, Grid& grid);
