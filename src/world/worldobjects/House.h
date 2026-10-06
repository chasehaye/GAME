#pragma once
#include <vector>
#include "world/worldobjects/WorldObject.h"

class Road;
class Vehicle;

class House : public WorldObject {

public:
    House(Cell* cell, Road* driveway);

    House(const House&) = delete;
    House& operator=(const House&) = delete;

    Road* getDriveway() const;

    void setDriveway(Road* road);

private:
    // does not own | owns links to other objects
    Road* driveway;
    std::vector<Vehicle*> vehicles;
};
