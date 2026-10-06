#include "world/worldobjects/Road.h"
#include <algorithm>
#include "world/map/Cell.h"

Road::Road(Cell* cell) : WorldObject(cell) {}

Road::~Road() {
    // Remove this road from each neighbor's list. Only the other roads' lists change
    // here; this road's own list is destroyed along with it.
    for (Road* neighbor : neighboringRoads) {
        std::erase(neighbor->neighboringRoads, this);
    }
}

void Road::addNeighboringRoad(Road* road) {
    if (!road || !getCell()->isNeighborOf(*road->getCell())) {
        return;
    }

    const bool alreadyLinked = std::find(neighboringRoads.begin(), neighboringRoads.end(), road) != neighboringRoads.end();
    if (alreadyLinked) {
        return;
    }

    // links road to neighbor
    neighboringRoads.push_back(road);
    // links neighbor to road
    road->neighboringRoads.push_back(this);
}

const std::vector<Road*>& Road::getNeighboringRoads() const {
    return neighboringRoads;
}

const std::vector<WorldObject*>& Road::getConnectedBuildings() const {
    return connectedBuildings;
}

void Road::addConnectedBuilding(WorldObject* building) {
    if (!building || isConnectedTo(building)) {
        return;
    }
    connectedBuildings.push_back(building);
}

void Road::removeConnectedBuilding(WorldObject* building) {
    std::erase(connectedBuildings, building);
}

bool Road::isConnectedToBuilding() const {
    return !connectedBuildings.empty();
}

bool Road::isConnectedTo(const WorldObject* building) const {
    return std::find(connectedBuildings.begin(), connectedBuildings.end(), building) != connectedBuildings.end();
}

bool Road::isIsolated() const {
    // A driveway has no road neighbors at first, but its buildings keep it connected.
    return neighboringRoads.empty() && !isConnectedToBuilding();
}