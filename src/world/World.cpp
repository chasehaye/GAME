#include "world/World.h"
#include "world/map/Cell.h"

World::World(int width, int height) : grid(width, height) {}

Grid& World::getGrid() {
    return grid;
}

const Grid& World::getGrid() const {
    return grid;
}

Road* World::placeRoad(Cell* cell) {
    if (Road* existing = Road::on(cell)) {
        return existing;
    }

    std::unique_ptr<Road> road = Road::placeOn(cell);
    if (!road) {
        return nullptr;
    }

    // World only keeps the road alive; the cell already points at it.
    roads.push_back(std::move(road));
    return roads.back().get();
}

void World::connectRoads(Cell* a, Cell* b) {
    // Checked first so no stray road gets placed on a cell that can't be linked.
    if (!a || !b || !a->isNeighborOf(*b)) {
        return;
    }

    Road* roadA = placeRoad(a);
    Road* roadB = placeRoad(b);
    if (roadA && roadB) {
        roadA->addNeighbor(roadB);
    }
}

const std::vector<std::unique_ptr<Road>>& World::getRoads() const {
    return roads;
}

void World::update(float /*dt*/) {
}
