#pragma once
#include <memory>
#include <vector>
#include "world/worldobjects/WorldObject.h"

class Road : public WorldObject {

public:
    explicit Road(Cell* cell);

    // Cleans up after itself: unlinks from every neighbor and detaches from its cell,
    // so nothing is left pointing at a road that no longer exists.
    ~Road() override;

    // A copy would share the neighbor list without the neighbors knowing about
    // it, and destroying the copy would unlink the original.
    Road(const Road&) = delete;
    Road& operator=(const Road&) = delete;

    // Creates a road on an empty cell and attaches it to that cell. Returns nullptr if
    // the cell is missing or already holds something. The caller takes ownership and
    // must keep the road alive while it's on the cell (World does this).
    static std::unique_ptr<Road> placeOn(Cell* cell);

    // The road on this cell, or nullptr if the cell is missing, empty, or holds
    // something that isn't a road.
    static Road* on(Cell* cell);

    // Links this road and the other one, on both sides. Does nothing if the roads
    // aren't on neighboring cells, or are already linked.
    void addNeighbor(Road* road);
    const std::vector<Road*>& getNeighbors() const;

private:
    // linked neighboring roads
    std::vector<Road*> neighbors;
};
