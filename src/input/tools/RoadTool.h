#pragma once

class Cell;
class PixelMapper;
class World;
struct InputState;

// Turns the player's mouse drags into road actions: which cell a road starts on and
// which neighbor it extends to. Remembers the drag in progress between frames.
// Changes the game only through World, which owns the roads and their rules.
class RoadTool {

public:
    void updateAdd(const InputState& input, World& world, const PixelMapper& pixelMapper);
    void updateRemove(const InputState& input, World& world);

private:
    void startDrag(const InputState& input);
    void continueDrag(const InputState& input, World& world, const PixelMapper& pixelMapper);

    // The last cell this drag reached, or nullptr when not dragging.
    Cell* lastDragCell = nullptr;
};
