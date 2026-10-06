#include "world/worldobjects/House.h"

House::House(Cell* cell, Road* driveway) : WorldObject(cell), driveway(driveway) {}

Road* House::getDriveway() const {
    return driveway;
}

void House::setDriveway(Road* road) {
    driveway = road;
}
