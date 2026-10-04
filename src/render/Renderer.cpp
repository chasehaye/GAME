#include "render/Renderer.h"
#include "raylib.h"
#include "render/PixelMapper.h"
#include "world/World.h"
#include "world/map/Cell.h"

namespace {
constexpr Color kBackground{238, 232, 220, 255};
constexpr Color kGridLine{200, 190, 170, 255};
constexpr Color kRoad{88, 90, 100, 255};
// Road dot radius, as a fraction of the cell size. Roads are drawn twice this wide.
constexpr float kRoadRadius = 0.18f;
}

// Draw order is layer order: anything drawn later appears on top.
void Renderer::drawFrame(const PixelMapper& pixelMapper, const World& world) const {
    BeginDrawing();
    ClearBackground(kBackground);

    drawGrid(pixelMapper);
    drawRoads(pixelMapper, world);

    EndDrawing();
}

void Renderer::drawGrid(const PixelMapper& pixelMapper) const {
    const int cellSize = pixelMapper.getCellSize();
    const int offsetX = pixelMapper.getOffsetX();
    const int offsetY = pixelMapper.getOffsetY();
    const int gridWidth = pixelMapper.getGridWidth();
    const int gridHeight = pixelMapper.getGridHeight();

    const int gridPixelWidth = gridWidth * cellSize;
    const int gridPixelHeight = gridHeight * cellSize;

    for (int x = 0; x <= gridWidth; x++) {
        const int lineX = offsetX + x * cellSize;
        DrawLine(lineX, offsetY, lineX, offsetY + gridPixelHeight, kGridLine);
    }
    for (int y = 0; y <= gridHeight; y++) {
        const int lineY = offsetY + y * cellSize;
        DrawLine(offsetX, lineY, offsetX + gridPixelWidth, lineY, kGridLine);
    }
}

void Renderer::drawRoads(const PixelMapper& pixelMapper, const World& world) const {
    const float roadRadius = pixelMapper.getCellSize() * kRoadRadius;

    // Links first, as thick lines as wide as a dot. Each link is stored on both roads,
    // so it gets drawn from both ends; the two lines are identical, so that's harmless.
    for (const auto& road : world.getRoads()) {
        const Vector2 from = pixelMapper.cellCenter(*road->getCell());
        for (const Road* neighbor : road->getNeighbors()) {
            DrawLineEx(from, pixelMapper.cellCenter(*neighbor->getCell()), roadRadius * 2, kRoad);
        }
    }

    // Then a dot on every road, on top, so joins and corners come out round.
    for (const auto& road : world.getRoads()) {
        DrawCircleV(pixelMapper.cellCenter(*road->getCell()), roadRadius, kRoad);
    }
}
