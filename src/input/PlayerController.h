#pragma once
#include "input/tools/RoadTool.h"

class PixelMapper;
class World;
struct InputState;

class PlayerController {

public:
    void update(const InputState& input, World& world, const PixelMapper& pixelMapper);

private:
    RoadTool roadTool;
};
