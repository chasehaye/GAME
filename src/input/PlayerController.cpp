#include "input/PlayerController.h"

void PlayerController::update(const InputState& input, World& world, const PixelMapper& pixelMapper) {
    roadTool.update(input, world, pixelMapper);
}
