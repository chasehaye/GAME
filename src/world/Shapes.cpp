#include "world/Shapes.h"

const std::vector<Offset>& offsetsFor(FootprintShape shape) {
    // static: each list is built once, the first time it's needed, then reused.
    static const std::vector<Offset> square2x2 = {
        {0, 0}, {1, 0},
        {0, 1}, {1, 1},
    };
    static const std::vector<Offset> rect2x3 = {
        {0, 0}, {1, 0},
        {0, 1}, {1, 1},
        {0, 2}, {1, 2},
    };

    switch (shape) {
        case FootprintShape::Square2x2: return square2x2;
        case FootprintShape::Rect2x3:   return rect2x3;
    }
    return square2x2;   // unreachable; keeps the compiler happy
}
