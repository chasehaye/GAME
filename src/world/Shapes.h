#pragma once
#include <vector>

// One cell of a shape, as a step from the shape's anchor (top-left) cell.
struct Offset {
    int dx;
    int dy;
};

// The footprints a multi-cell building can have. Add a value here and a case in
// offsetsFor() to add a shape.
enum class FootprintShape {
    Square2x2,
    Rect2x3,
};

// The cells a shape covers, as offsets from its anchor cell.
const std::vector<Offset>& offsetsFor(FootprintShape shape);
