#include "world/World.h"
#include "world/map/Cell.h"

World::World(int width, int height) : grid(width, height) {}

Grid& World::getGrid() {
    return grid;
}

const Grid& World::getGrid() const {
    return grid;
}

Road* World::roadAt(Cell* cell) const {
    if (!cell) {
        return nullptr;
    }
    // dynamic_cast checks at run time whether the object is really a Road, and gives
    // nullptr if it isn't.
    return dynamic_cast<Road*>(cell->getObject());
}

Road* World::placeRoad(Cell* cell) {
    if (Road* existing = roadAt(cell)) {
        return existing;
    }
    if (!cell || cell->getObject()) {
        return nullptr;
    }

    // Create, own, and attach in one step, so a road can never exist without an owner.
    // The unique_ptr in `roads` owns it; the cell only points at it.
    roads.push_back(std::make_unique<Road>(cell));
    Road* road = roads.back().get();
    cell->setObject(road);
    return road;
}

void World::connectRoads(Cell* a, Cell* b) {
    // Checked here as well as in addNeighboringRoad, so no stray road gets placed on a cell
    // that can't be linked anyway.
    if (!a || !b || !a->isNeighborOf(*b)) {
        return;
    }

    Road* roadA = placeRoad(a);
    Road* roadB = placeRoad(b);
    if (roadA && roadB) {
        roadA->addNeighboringRoad(roadB);
    }
}

void World::removeRoad(Cell* cell) {
    Road* road = roadAt(cell);
    if (!road) {
        return;
    }

    // A road that serves any building can't be erased; it goes only once no building
    // uses it any more.
    if (road->isConnectedToBuilding()) {
        return;
    }

    // Copy the neighbors before deleting: once the road is gone, its list is gone too.
    const std::vector<Road*> formerNeighbors = road->getNeighboringRoads();

    // Detach from the cell first, so it never points at a deleted road.
    cell->setObject(nullptr);

    // Erasing the unique_ptr deletes the road, and ~Road() unlinks it from its
    // neighbors. std::erase_if (C++20) removes every element the check returns true for.
    std::erase_if(roads, [road](const std::unique_ptr<Road>& owned) {
        return owned.get() == road;
    });

    // Any former neighbor left with no connections at all is removed too. This can't
    // cascade further: an isolated road has no neighbors left to orphan.
    for (Road* neighbor : formerNeighbors) {
        if (neighbor->isIsolated()) {
            removeRoad(neighbor->getCell());
        }
    }
}

const std::vector<std::unique_ptr<Road>>& World::getRoads() const {
    return roads;
}

House* World::houseAt(Cell* cell) const {
    if (!cell) {
        return nullptr;
    }
    return dynamic_cast<House*>(cell->getObject());
}

House* World::placeHouse(Cell* cell) {
    if (House* existing = houseAt(cell)) {
        return existing;
    }
    if (!cell || cell->getObject()) {
        return nullptr;
    }

    // check and add available driveway
    Cell* drivewayCell = nullptr;
    std::vector<Cell*> neighboringCells = grid.getNeighboringCells(*cell);
    for (Cell* neighbor : neighboringCells) {
        if (!neighbor->getObject()) {
            drivewayCell = neighbor;
            break;
        }
    }
    if (!drivewayCell) {
        return nullptr;
    }
    Road* driveway = placeRoad(drivewayCell);

    houses.push_back(std::make_unique<House>(cell, driveway));
    House* house = houses.back().get();
    cell->setObject(house);

    // The other half of the link: the driveway knows which buildings it serves.
    driveway->addConnectedBuilding(house);
    return house;
}

const std::vector<std::unique_ptr<House>>& World::getHouses() const {
    return houses;
}










void World::update(float /*dt*/) {
}
