#include "DeviceDriver.h"
#include <stdexcept>
#include <iostream>

using namespace std;

class WriteFailException :public std::exception {
};

class ReadFailException :public std::exception {
};


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int readValue = (int)(m_hardware->read(address));
    readConditionCheck(readValue, address);
    return readValue;
}

void DeviceDriver::readConditionCheck(int readValue, long address)
{
    for (int i = 0; i < 4; i++) {
        if (readValue != (int)(m_hardware->read(address)))
            throw ReadFailException();
    }
}

void DeviceDriver::write(long address, int data)
{
    writeConditionCheck(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::writeConditionCheck(long address)
{
    int readValue = (int)(m_hardware->read(address));
    if (readValue != BLANK_VALUE) {
        throw WriteFailException();
    }
}
