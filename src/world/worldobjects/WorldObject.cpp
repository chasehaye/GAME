#include "world/worldobjects/WorldObject.h"
#include <utility>

// Delegates to the list constructor, so one-cell objects are just a list of one.
WorldObject::WorldObject(Cell* cell) : WorldObject(std::vector<Cell*>{cell}) {}

// std::move hands the list over instead of copying it.
WorldObject::WorldObject(std::vector<Cell*> cells) : cells(std::move(cells)) {}

const std::vector<Cell*>& WorldObject::getCells() const {
    return cells;
}

Cell* WorldObject::getCell() const {
    return cells.empty() ? nullptr : cells.front();
}
