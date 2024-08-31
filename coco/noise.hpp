#pragma once

/*
    Noise functions
    Inspired by FastLED noise functions: http://fastled.io/docs/3.1/noise_8cpp_source.html
*/


namespace coco {
namespace math {

/**
 * Generate noise in the range [-1.0, 1.0]
 * @param x input argument of noise (pattern repeats at 256.0)
 * @return noise function at given x
 */
float noise(float x);

} // namespace math
} // namespace coco
