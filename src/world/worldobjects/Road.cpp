#include "world/worldobjects/Road.h"
#include <algorithm>
#include "world/map/Cell.h"

Road::Road(Cell* cell) : WorldObject(cell) {}

std::unique_ptr<Road> Road::placeOn(Cell* cell) {
    if (!cell || cell->getObject()) {
        return nullptr;
    }

    auto road = std::make_unique<Road>(cell);
    cell->setObject(road.get());
    return road;
}

Road* Road::on(Cell* cell) {
    if (!cell) {
        return nullptr;
    }
    // dynamic_cast checks at run time whether the object is really a Road, and gives
    // nullptr if it isn't.
    return dynamic_cast<Road*>(cell->getObject());
}

void Road::addNeighbor(Road* road) {
    if (!road || !getCell()->isNeighborOf(*road->getCell())) {
        return;
    }

    const bool alreadyLinked = std::find(neighbors.begin(), neighbors.end(), road) != neighbors.end();
    if (alreadyLinked) {
        return;
    }

    // links road to neighbor
    neighbors.push_back(road);
    // links neighbor to road
    road->neighbors.push_back(this);
}

const std::vector<Road*>& Road::getNeighbors() const {
    return neighbors;
}
