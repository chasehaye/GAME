#include "input/tools/RoadTool.h"
#include "input/InputHandler.h"
#include "render/PixelMapper.h"
#include "world/World.h"
#include "world/map/Cell.h"
#include "world/map/Grid.h"

namespace {
// How close the mouse must get to a neighbor's center to extend the road, as a
// fraction of the cell size. At 0.5 neighboring circles just touch; any larger and
// two neighbors could match at once. Smaller leaves more room for wobble on diagonals.
constexpr float kSnapRadius = 0.4f;
}

void RoadTool::updateAdd(const InputState& input, World& world, const PixelMapper& pixelMapper) {
    if (!input.leftMouseDown) {
        lastDragCell = nullptr;
        return;
    }
    if (input.leftMousePressed) {
        startDrag(input);
    }
    continueDrag(input, world, pixelMapper);
}

void RoadTool::startDrag(const InputState& input) {
    // Only remember where the drag starts. Nothing is placed until the mouse reaches a
    // neighbor; then connectRoads puts road on both tiles (if empty) and links them.
    lastDragCell = input.hoveredCell;
}

void RoadTool::continueDrag(const InputState& input, World& world, const PixelMapper& pixelMapper) {
    if (!lastDragCell) {
        return;
    }

    // Only the last cell's neighbors are candidates. The drag extends once the mouse
    // gets near a neighbor's center
    Grid& grid = world.getGrid();
    const float snapRadius = pixelMapper.getCellSize() * kSnapRadius;
    for (Cell* neighbor : grid.getNeighboringCells(*lastDragCell)) {
        if (CheckCollisionPointCircle(input.mousePosition, pixelMapper.cellCenter(*neighbor), snapRadius)) {
            world.connectRoads(lastDragCell, neighbor);
            lastDragCell = neighbor;
            return;
        }
    }
}


void RoadTool::updateRemove(const InputState& input, World& world) {
    if (input.rightMouseDown) {
        world.removeRoad(input.hoveredCell);
    }
}