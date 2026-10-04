#include "world/worldobjects/Road.h"
#include <algorithm>
#include "world/map/Cell.h"

Road::Road(Cell* cell) : WorldObject(cell) {}

Road::~Road() {
    // Remove this road from each neighbor's list. Only the other roads' lists change
    // here; this road's own list is destroyed along with it.
    for (Road* neighbor : neighbors) {
        std::erase(neighbor->neighbors, this);
    }
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

bool Road::isIsolated() const {
    // !!! TODO (when houses are added): also require !connectedBuilding. See Road.h.
    return neighbors.empty();
}