#include "world/worldobjects/House.h"

House::House(Cell* cell, Road* driveway) : WorldObject(cell), driveway(driveway) {}

Road* House::getDriveway() const {
    return driveway;
}
