#pragma once
#include <vector>
#include "world/worldobjects/WorldObject.h"

// A node in the road network. Only changes road data; World places and removes roads.
class Road : public WorldObject {

public:
    explicit Road(Cell* cell);

    // Unlinks from all neighbors.
    ~Road() override;

    // No copying: a copy would share links its neighbors don't know about.
    Road(const Road&) = delete;
    Road& operator=(const Road&) = delete;

    // Many to Many roads
    const std::vector<Road*>& getNeighboringRoads() const;
    void addNeighboringRoad(Road* road);

    // Many to One Houses
    const std::vector<WorldObject*>& getConnectedBuildings() const;
    void addConnectedBuilding(WorldObject* building);       // ignores nullptr and duplicates
    void removeConnectedBuilding(WorldObject* building);    // does nothing if not connected

    bool isConnectedToBuilding() const;                         // serves at least one building
    bool isConnectedTo(const WorldObject* building) const;     // serves this specific one

    // True if nothing connects to this road: no neighboring roads and no buildings.
    bool isIsolated() const;

private:
    // does not own | owns links to other objects
    std::vector<Road*> neighboringRoads;
    std::vector<WorldObject*> connectedBuildings;
};
