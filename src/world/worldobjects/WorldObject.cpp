#include "world/worldobjects/WorldObject.h"

WorldObject::WorldObject(Cell* cell) : cell(cell) {}

Cell* WorldObject::getCell() const {
    return cell;
}
