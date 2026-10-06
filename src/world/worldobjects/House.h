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

private:
    Road* driveway;                    // not owned: World owns all roads
    std::vector<Vehicle*> vehicles;    // not owned; unused until vehicles exist
};
