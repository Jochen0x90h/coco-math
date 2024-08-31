#pragma once

/*
    Color conversion functions
    HSV: hsv2rgb
*/

#include <coco/math.hpp>


namespace coco {
namespace math {

// https://gist.github.com/983/e170a24ae8eba2cd174f
inline float3 hsv2rgb(float3 c) {
    float3 K = {1.0f, 2.0f / 3.0f, 1.0f / 3.0f};
    float3 p = abs(fract(c.x + K) * 6.0f - 3.0f);
    return c.z * mix(K.xxx(), clamp(p - 1.0f, 0.0f, 1.0f), c.y);
}

} // namespace math
} // namespace coco
