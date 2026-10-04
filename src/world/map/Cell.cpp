#include "world/map/Cell.h"
#include <cstdlib>

Cell::Cell(int x, int y) : x(x), y(y) {}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

WorldObject* Cell::getObject() const {
    return object;
}

void Cell::setObject(WorldObject* object) {
    this->object = object;
}

bool Cell::isNeighborOf(const Cell& other) const {
    // Neighbors differ by at most one in each direction.
    return !(*this == other) && std::abs(x - other.x) <= 1 && std::abs(y - other.y) <= 1;
}

bool Cell::operator==(const Cell& other) const {
    return x == other.x && y == other.y;
}