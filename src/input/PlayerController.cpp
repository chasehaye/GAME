#include "input/PlayerController.h"

void PlayerController::update(const InputState& input, World& world, const PixelMapper& pixelMapper) {
    roadTool.updateAdd(input, world, pixelMapper);
    roadTool.updateRemove(input, world);
}
