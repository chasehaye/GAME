#pragma once

class Cell;

// Anything that sits on a grid cell: roads now, houses and stores later.
class WorldObject {

public:
    explicit WorldObject(Cell* cell);
    virtual ~WorldObject() = default;

    // The cell this object sits on. Not owned: the Grid owns its cells.
    Cell* getCell() const;

private:
    Cell* cell;
};
