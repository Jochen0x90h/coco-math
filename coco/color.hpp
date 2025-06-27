#pragma once

/*
    Color conversion functions
    HSV: hsv2rgb
*/

#include <coco/math.hpp>


namespace coco {
namespace math {

/// @brief Convert from RGB (red, green, blue) to HSV (hue, saturation, value)
/// see https://gist.github.com/983/e170a24ae8eba2cd174f
/// @param c Color in RGB where each component ranges from 0 to 1
inline float3 rgb2hsv(float3 c) {
    float4 K = {0.0f, -1.0f / 3.0f, 2.0f / 3.0f, -1.0f};
  //float4 p = mix(float4(c.bg, K.wz), float4(c.gb, K.xy), step(c.b, c.g));
    float4 p = mix(float4(c.z, c.y, K.w, K.z), float4(c.y, c.z, K.x, K.y), step(c.z, c.y));
  //float4 q = mix(float4(p.xyw, c.r), float4(c.r, p.yzx), step(p.x, c.r));
    float4 q = mix(float4(p.x, p.y, p.w, c.x), float4(c.x, p.y, p.z, p.x), step(p.x, c.x));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return {abs(q.z + (q.w - q.y) / (6.0f * d + e)), d / (q.x + e), q.x};
}

/// @brief Convert from HSV (hue, saturation, value) to RGB (red, green, blue)
/// @param c Color in HSV where each component ranges from 0 to 1
inline float3 hsv2rgb(float3 c) {
    float3 K = {1.0f, 2.0f / 3.0f, 1.0f / 3.0f};
    float3 p = abs(fract(c.x + K) * 6.0f - 3.0f);
    return c.z * mix(K.xxx(), clamp(p - 1.0f, 0.0f, 1.0f), c.y);
}

} // namespace math
} // namespace coco
