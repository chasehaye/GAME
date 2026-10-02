#pragma once
#include "world/worldobjects/WorldObject.h"

class Cell {

public:
    Cell(int x, int y);

    int getX() const;
    int getY() const;

    // Two cells are equal if they are at the same position. What's on them
    // doesn't matter.
    bool operator==(const Cell& other) const;

    // True if the other cell touches this one, diagonals included. A cell is not
    // its own neighbor.
    bool isNeighborOf(const Cell& other) const;

    WorldObject* getObject() const;
    void setObject(WorldObject* object);

private:
    int x;
    int y;
    WorldObject* object = nullptr;
};
