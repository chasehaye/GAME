#pragma once
#include <vector>

class Cell;

// Anything that sits on the grid: roads, houses, destinations. Covers one or more cells
// (its footprint), in any shape.
class WorldObject {

public:
    // A one-cell object (roads, houses).
    explicit WorldObject(Cell* cell);

    // A multi-cell object. The first cell is its anchor.
    explicit WorldObject(std::vector<Cell*> cells);

    virtual ~WorldObject() = default;

    // Every cell this object covers. Not owned: the Grid owns its cells.
    const std::vector<Cell*>& getCells() const;

    // The anchor (first) cell. For one-cell objects, simply the cell it sits on.
    Cell* getCell() const;

private:
    std::vector<Cell*> cells;
};
