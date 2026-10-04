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

    // Links both ways. Ignores non-adjacent roads and existing links.
    void addNeighbor(Road* road);

    const std::vector<Road*>& getNeighbors() const;

    // True if nothing connects to this road.
    // !!! TODO (houses): a driveway has no road neighbors. Add `WorldObject* connectedBuilding`,
    // check `neighbors.empty() && !connectedBuilding`, and block erasing driveways in World.
    bool isIsolated() const;

private:
    std::vector<Road*> neighbors;
};
