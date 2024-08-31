#include <gtest/gtest.h>
#include <coco/color.hpp>
#include <coco/math.hpp>
#include <coco/noise.hpp>


using namespace coco;
using namespace coco::math;


// test floor based on int cast
inline float floor2(float a) {
    float b = int(a);
    return b > a ? b - 1.0f : b;
}
TEST(cocoTest, floor) {
    EXPECT_EQ(floor2(10.5f), 10.0f);
    EXPECT_EQ(floor2(10.99f), 10.0f);
    EXPECT_EQ(floor2(-10.5f), -11.0f);
    EXPECT_EQ(floor2(-10.01f), -11.0f);

    EXPECT_EQ(floor2(4194303.5f), 4194303.0f);
    EXPECT_EQ(floor2(-4194303.5f), -4194304.0f);
}

// test ceil based on int cast
inline float ceil2(float a) {
    float b = int(a);
    return b < a ? b + 1.0f : b;
}
TEST(cocoTest, ceil) {
    EXPECT_EQ(ceil2(10.5f), 11.0f);
    EXPECT_EQ(ceil2(10.01f), 11.0f);
    EXPECT_EQ(ceil2(-10.5f), -10.0f);
    EXPECT_EQ(ceil2(-10.99f), -10.0f);

    EXPECT_EQ(ceil2(4194303.5f), 4194304.0f);
    EXPECT_EQ(ceil2(-4194303.5f), -4194303.0f);
}


// color
// -----

TEST(LedControl, hsv2rgb) {
	{
		float3 hsv = {0, 1.0, 1.0};
		float3 color = hsv2rgb(hsv);
		EXPECT_FLOAT_EQ(color.x, 1.0f);
		EXPECT_FLOAT_EQ(color.y, 0);
		EXPECT_FLOAT_EQ(color.z, 0);
	}
	{
		float3 hsv = {0.25f / 6.0f, 1.0, 1.0};
		float3 color = hsv2rgb(hsv);
		EXPECT_FLOAT_EQ(color.x, 1.0f);
		EXPECT_FLOAT_EQ(color.y, 0.25f);
		EXPECT_FLOAT_EQ(color.z, 0);
	}
	{
		float3 hsv = {1.25f / 6.0f, 1.0, 1.0};
		float3 color = hsv2rgb(hsv);
		EXPECT_FLOAT_EQ(color.x, 0.75f);
		EXPECT_FLOAT_EQ(color.y, 1.0f);
		EXPECT_FLOAT_EQ(color.z, 0);
	}
}


// noise
// -----

TEST(cocoTest, noise) {
    float last = noise(0);
    float minValue = 0;
    float maxValue = 0;
    for (int i = 0; i < 65536; ++i) {
        float n = noise(i / 256.0f);

        // check range
        EXPECT_GE(n, -1.0f);
        EXPECT_LE(n, 1.0f);
        minValue = min(minValue, n);
        maxValue = max(maxValue, n);

        // check slope
        EXPECT_TRUE(std::abs(last - n) <= 1.0f/64.0f);
        last = n;
    }

    EXPECT_FLOAT_EQ(minValue, -1.0f);
    EXPECT_FLOAT_EQ(maxValue, 1.0f);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int success = RUN_ALL_TESTS();
    return success;
}
