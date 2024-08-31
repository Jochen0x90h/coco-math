#include "noise.hpp"
#include "math.hpp"
#include <cstdint>
#include "permute8.hpp" // generated permute table


namespace coco {
namespace math {

// helper function: calculate bumps of varying height in the range [-1.0, 1.0]
inline float bump(uint8_t i, float x) {
    // quadratic function with zero crossings at x=0 and x=1 and minimum of y=-0.5 at x=0.5
    float y = 2.0f * (x * x - x);

    auto hash = permute8[i];
    float u, v;
    if (hash & 8) {
        u = y;
        v = y;
    } else {
        if (hash & 4) {
            u = 0;
            v = y;
        } else {
            u = y;
            v = 0;
        }
    }

    if (hash & 1)
        u = -u;
    if (hash & 2)
        v = -v;

    // return sum of u and v (maximum value is +-1.0)
    return u + v;
}

float noise(float x) {
    // integer part of x
    int i = roundToInt(x - 0.5f);

    // fractional part of x
    float f = x - float(i);

    // bump for position i and negative bump for next position
    float g1 = bump(i, f);
    float g2 = -bump(i + 1, f);

    // interpolate between the bumps
    return g1 + (g2 - g1) * f;
}

} // namespace math
} // namespace coco
