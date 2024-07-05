#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    void readConditionCheck(int readValue, long address);
    void writeConditionCheck(long address);
    const int BLANK_VALUE = 0xFF;
};
