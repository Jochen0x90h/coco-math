#include <coco/math.hpp>
#include <coco/StreamOperators.hpp>
#include <coco/debug.hpp>
#include <cmath>


using namespace coco;
using namespace coco::math;
//namespace cm = coco::math;

inline float logx(float x) noexcept {
    float y = log(x / 10.0f) - 2.3026f; // log(10)
    //debug::out << flt(x / 10.0f) << '\n';
    return y;
}


bool check(float difference) {
    return abs(difference) <= 1e-4f;
}


void testColorTemperature() {
    debug::out << "*** test color temperature\n";
    bool result = true;
    //for (int t = 1800; t <= 2200; t += 1) {
    for (int t = 1000; t <= 40000; t += 100) {
        float temperature = t / 100.0f;

        float red1;
        float green1;
        float blue1;
        if (temperature <= 66.0f) {
            red1 = 255.0f;
            green1 = 99.4708025861f * std::log(temperature) - 161.1195681661f - 0.629f;
            blue1 = (temperature < 19.05f) ? 0.0f : (138.5177312231f * std::log(temperature - 10.0f) - 305.0447927307f);
        } else {
            red1 = 329.698727446f * std::pow(temperature - 60.0f, -0.1332047592f);
            green1 = 288.1221695283f * std::pow(temperature - 60.0f, -0.0755148492f);
            blue1 = 255.0f;
        }

        float red2;
        float green2;
        float blue2;
        if (temperature <= 66.0f) {
            red2 = 255.0f;
            green2 = 99.4708025861f * logx(temperature) - 161.1195681661f - 0.629f;
            blue2 = (temperature < 19.05f) ? 0.0f : (138.5177312231f * logx(temperature - 10.0f) - 305.0447927307f);
        } else {
            red2 = 329.698727446f * std::pow(temperature - 60.0f, -0.1332047592f);
            green2 = 288.1221695283f * std::pow(temperature - 60.0f, -0.0755148492f);
            blue2 = 255.0f;
        }

        debug::out << flt(t) << ": ";
        debug::out << flt(red1, 3, -1) << ' ' << flt(green1, 3, -1) << ' ' << flt(blue1, 3, -1) << ' ';
        debug::out << flt(red2, 3, -1) << ' ' << flt(green2, 3, -1) << ' ' << flt(blue2, 3, -1) << '\n';
        //result &= check(d);
    }
    debug::out << (result ? "OK\n" : "ERROR\n");
}

int main() {
    math::init();

    testColorTemperature();

    return 0;
}
