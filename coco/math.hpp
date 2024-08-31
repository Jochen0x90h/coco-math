#pragma once

/*
    Math functions
    Basic: abs, min, max, clamp, mix,
    Rounding and truncation: roundToInt, floor, ceil, round, trunc, fract
    Mathematical: sqrt
    Trigonometric: sin, cos, atan
*/

#include <coco/Vector3.hpp>
#include <algorithm>
#ifdef STM32G4
#include <coco/platform/platform.hpp>
#else
#include <cmath>
#endif


namespace coco {
namespace math {

#ifdef STM32G4

/// @brief Initalize math functions
/// @return dummy value for static initialization
inline int init() {
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_CORDICEN;
    __NOP();
    __NOP();
    return 0;
}

#else

/// @brief Initalize math functions
/// @return dummy value for static initialization
inline int init() {
    return 0;
}

#endif

using std::abs;
using std::min;
using std::max;
using std::clamp;

/// @brief performs a linear interpolation between x and y using a to weight between them
/// @param x First value
/// @param y Second value
/// @param a Interpolator
/// @return Interpolated value
inline float mix(float x, float y, float a) {
	return x * (1.0f - a) + y * a;
}

#ifdef STM32G4

/// @brief Round like round() and then convert to int
/// @param x Argument
/// @return Nearest integer
__attribute__((always_inline)) static inline int roundToInt(float x) {
    int r;
    __asm__ __volatile__ (
      "vcvtr.s32.f32   %[r], %[x]"
        : [r] "=t" (r) // output
        : [x] "0" (x) // input(s)
        : // list of clobbered registers
    );
    return r;
}

/// @brief Returns a value equal to the nearest integer that is less than or equal to x.
/// @param x Argument
/// @return Floor value
inline float floor(float x) {
    float b = int(x);
    return b > x ? b - 1.0f : b;
}

/// @brief Returns a value equal to the nearest integer that is greater than or equal to x.
/// @param x Argument
/// @return Ceil value
inline float ceil(float x) {
    float b = int(x);
    return b < x ? b + 1.0f : b;
}

/// @brief Returns a value equal to the nearest integer to x. The fractional part of 0.5 will round toward the nearest even integer. For example, both 3.5 and 4.5 will round to 4.0.
/// @param x Argument
/// @return Rounded value
inline float round(float x) {
    return float(roundToInt(x));
}

/// @brief Returns a value equal to the nearest integer to x whose absolute value is not larger than the absolute value of x.
/// @param x Argument
/// @return Truncated value
inline float trunc(float x) {
    return int(x);
}

/// @brief Returns the fractional part of x. This is calculated as x - floor(x).
/// @param x Argument
/// @return Fractional part
inline float fract(float x) {
    return x - floor(x);
}

/// @brief Returns the square root of x.
/// @param x Argument
/// @return Square root
inline float sqrt(float x) {
    float y;
    __asm__ __volatile__ (
      "vsqrt.f32   %[y], %[x]"
        : [y] "=t" (y) // output
        : [x] "0" (x) // input(s)
        : // list of clobbered registers
    );
    return y;
}

/// @brief Sine function. Don't forget to call math::init()
/// @param x Argument
/// @return sine of x
inline float sin(float x) {
    CORDIC->CSR = 1 // sin/cos
        | (4 << CORDIC_CSR_PRECISION_Pos) // iterations/4
        | CORDIC_CSR_ARGSIZE // 16 bit input
        | CORDIC_CSR_RESSIZE // 16 bit output
        | 0; // one write (both args are packed)

    float y = x * 0.1591549f;
	int angle = roundToInt(y * 65536.0f) - (roundToInt(y - 0.5f) << 16);
    CORDIC->WDATA = angle // angle
        | 0x7fff0000; // amplitude of sin/cos
    int16_t result = CORDIC->RDATA;

	return float(result) * 3.0518509e-05f;
}

/// @brief Cosine function. Don't forget to call math::init()
/// @param x Argument
/// @return cosine of x
inline float cos(float x) {
    CORDIC->CSR = 0 // cos/sin
        | (4 << CORDIC_CSR_PRECISION_Pos) // iterations/4
        | CORDIC_CSR_ARGSIZE // 16 bit input
        | CORDIC_CSR_RESSIZE // 16 bit output
        | 0; // one write (both args are packed)

    float y = x * 0.1591549f;
	int angle = roundToInt(y * 65536.0f) - (roundToInt(y - 0.5f) << 16);
    CORDIC->WDATA = angle // angle
        | 0x7fff0000; // amplitude of sin/cos
    int16_t result = CORDIC->RDATA;

	return float(result) * 3.0518509e-05f;
}

/// @brief Arctangent function. Don't forget to call math::init()
/// @param y y coordinate
/// @param x x coordinate
/// @return arctangent of y and x in range [-pi, pi)
inline float atan(float y, float x) {
    CORDIC->CSR = 3 // modulus
        | (4 << CORDIC_CSR_PRECISION_Pos) // iterations/4
        | CORDIC_CSR_ARGSIZE // 16 bit input
        | CORDIC_CSR_RESSIZE // 16 bit output
        | 0; // one write (both args are packed)

    float scale = 32767.0f / max(abs(x), abs(y));
    int a = roundToInt(x * scale);
    int b = roundToInt(y * scale);
    CORDIC->WDATA = (a & 0xffff) | (b << 16);
    int result = int32_t(CORDIC->RDATA) >> 16;

	return float(result) * 9.5873799e-05f;
}

#else

inline int roundToInt(float x) {
    return int(round(x));
}

using std::floor;
using std::round;
using std::ceil;
using std::trunc;

/// @brief Returns the fractional part of x. This is calculated as x - floor(x).
/// @param x Argument
/// @return Fractional part
inline float fract(float x) {
	return x - floor(x);
}

using std::sqrt;

using std::sin;
using std::cos;

/// @brief Arctangent function.
/// @param y y coordinate
/// @param x x coordinate
/// @return arctangent of y and x in range [-pi, pi)
inline float atan(float y, float x) {
    return std::atan2(y, x);
}

#endif

// float2
// ------


// float3
// ------

inline float3 abs(float3 x) {
	return {abs(x.x), abs(x.y), abs(x.z)};
}

inline float3 min(float3 x, float y) {
	return {min(x.x, y), min(x.y, y), min(x.z, y)};
}

inline float3 min(float3 x, float3 y) {
	return {min(x.x, y.x), min(x.y, y.y), min(x.z, y.z)};
}

inline float3 max(float3 x, float y) {
	return {max(x.x, y), max(x.y, y), max(x.z, y)};
}

inline float3 max(float3 x, float3 y) {
	return {max(x.x, y.x), max(x.y, y.y), max(x.z, y.z)};
}

inline float3 clamp(float3 x, float minVal, float maxVal) {
	return {clamp(x.x, minVal, maxVal), clamp(x.y, minVal, maxVal), clamp(x.z, minVal, maxVal)};
}

inline float3 clamp(float3 x, float3 minVal, float3 maxVal) {
	return {clamp(x.x, minVal.x, maxVal.x), clamp(x.y, minVal.y, maxVal.y), clamp(x.z, minVal.z, maxVal.z)};
}

inline float3 mix(float3 x, float3 y, float a) {
	return x * (1.0f - a) + y * a;
}

inline float3 mix(float3 x, float3 y, float3 a) {
	return x * (1.0f - a) + y * a;
}

inline float3 floor(float3 x) {
	return {floor(x.x), floor(x.y), floor(x.z)};
}

inline float3 ceil(float3 x) {
	return {ceil(x.x), ceil(x.y), ceil(x.z)};
}

inline float3 round(float3 x) {
	return {round(x.x), round(x.y), round(x.z)};
}

inline float3 trunc(float3 x) {
	return {trunc(x.x), trunc(x.y), trunc(x.z)};
}

inline float3 fract(float3 x) {
	return {fract(x.x), fract(x.y), fract(x.z)};
}

inline float3 sqrt(float3 x) {
	return {sqrt(x.x), sqrt(x.y), sqrt(x.z)};
}

inline float3 sin(float3 x) {
	return {sin(x.x), sin(x.y), sin(x.z)};
}

inline float3 cos(float3 x) {
	return {cos(x.x), cos(x.y), cos(x.z)};
}

inline float3 atan(float3 y, float3 x) {
	return {atan(y.x, x.x), atan(y.y, x.y), atan(y.z, x.z)};
}

// float4
// ------

} // namespace math
} // namespace coco
