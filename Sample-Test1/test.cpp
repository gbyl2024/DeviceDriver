#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../Project24/DeviceDriver.cpp"
#include "../Project24/FlashMemoryDevice.h"

using namespace testing;
using namespace std;

class MockingFlashMemoryDevice :public FlashMemoryDevice {
public:
	// FlashMemoryDevice을(를) 통해 상속됨
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, WriteException) {
	MockingFlashMemoryDevice hw;
	DeviceDriver driver(&hw);
	EXPECT_CALL(hw, read)
		.Times(1)
		.WillRepeatedly(Return(0x7));

	EXPECT_THROW(driver.write(0xF4, 0x7), WriteFailException);
}

TEST(TestCaseName, TestReadRepeated) {
	MockingFlashMemoryDevice hw;
	DeviceDriver driver(&hw);
	EXPECT_CALL(hw, read)
		.Times(5)
		.WillRepeatedly(Return(0x7));

	driver.read(0XF4);
}

TEST(TestCaseName, TestReadException) {
	MockingFlashMemoryDevice hw;
	DeviceDriver driver(&hw);
	EXPECT_CALL(hw, read)
		.Times(2)
		.WillOnce(Return(0x6))
		.WillRepeatedly(Return(0x7));

	EXPECT_THROW(driver.read(0xF4), ReadFailException);
}
