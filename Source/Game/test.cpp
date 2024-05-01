#include <gtest/gtest.h>
//#include "./car_test.h"

int main(int argc, char * argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(LaptopTest, DefaultInfo) {
	Laptop l1;
	ASSERT_EQ(l1.size(), 16);
	ASSERT_EQ(l1.os(), "Windows");
	ASSERT_NEAR(l1.keyboard_size(), 1.0, 0.0001);
	ASSERT_EQ(l1.information(), "A 16-inch laptop loaded with Windows");
}
