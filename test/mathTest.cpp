#include <coco/math.hpp>
#include <coco/StreamOperators.hpp>
#include <coco/debug.hpp>
#include <cmath>


using namespace coco;
using namespace coco::math;


bool check(float difference) {
    return abs(difference) <= 1e-4f;
}

void testFract() {
    debug::out << "*** testFract\n";
    bool result = true;
    for (int i = -20; i <= 20; ++i) {
        float x = i * 0.1f;

        float y = fract(x);
        float z = x - std::floor(x);
        float d = y - z;

        debug::out << flt(y) << ' ' << flt(z) << ' ' << flt(d) << '\n';
        result &= check(d);
    }
    debug::out << (result ? "OK\n" : "ERROR\n");
}

void testSin() {
    debug::out << "*** testSin\n";
    bool result = true;
    for (int i = -20; i <= 20; ++i) {
        float x = i * 0.1f;

        float y = sin(x * 6.2831853f);
        float z = std::sin(x * 6.2831853f);
        float d = y - z;

        debug::out << flt(y) << ' ' << flt(z) << ' ' << flt(d) << '\n';
        result &= check(d);
    }
    debug::out << (result ? "OK\n" : "ERROR\n");
}

void testCos() {
    debug::out << "*** testCos\n";
    bool result = true;
    for (int i = -20; i <= 20; ++i) {
        float x = i * 0.1f;

        float y = cos(x * 6.2831853f);
        float z = std::cos(x * 6.2831853f);
        float d = y - z;

        debug::out << flt(y) << ' ' << flt(z) << ' ' << flt(d) << '\n';
        result &= check(d);
    }
    debug::out << (result ? "OK\n" : "ERROR\n");
}

void testAtan() {
    debug::out << "*** testAtan\n";
    bool result = true;
    for (int i = -10; i <= 10; ++i) {
        float x = i * 0.1f * 3.1415926f;

        float a = cos(x);
        float b = sin(x);

        float y = atan(b, a);
        float z = std::atan2(b, a);
        float d = y - z;

        debug::out << flt(y) << ' ' << flt(z) << ' ' << flt(d) << '\n';
        result &= check(d);
    }
    debug::out << (result ? "OK\n" : "ERROR\n");
}

int main() {
    math::init();

    testFract();
    testSin();
    testCos();
    testAtan();

    return 0;
}
