#include "input/InputHandler.h"
#include "render/PixelMapper.h"

InputState readInput(const PixelMapper& pixelMapper, Grid& grid) {
    InputState input;

    input.mousePosition = GetMousePosition();
    input.hoveredCell = pixelMapper.cellAt(input.mousePosition, grid);

    input.leftMousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    input.leftMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    input.leftMouseReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    input.rightMouseDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

    input.escapePressed = IsKeyPressed(KEY_ESCAPE);

    return input;
}
