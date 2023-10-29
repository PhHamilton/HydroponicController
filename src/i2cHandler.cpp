#include "i2cHandler.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


I2CHandler::I2CHandler(uint8_t deviceAddress, const char* I2CAdapter) : _fileManager(&_fileHandler)
{
	_deviceAddress = deviceAddress;
	_i2cDevice = _formatter.AddThreeStrings(I2C_PATH, "/", I2CAdapter);
}

uint8_t I2CHandler::Initialize()
{
	_openI2CBus();
	_setSlaveAddress();	
	return 0;
}

uint8_t I2CHandler::Write(uint8_t data[], uint8_t dataSize)
{

	if(write(_i2cFile, data, dataSize) != dataSize)
	{
		perror("Error writing to the I2C device");
		return 1;
	}

	return 0;	
}

uint8_t I2CHandler::Read(uint8_t buf[], uint8_t dataSize)
{
	if(read(_i2cFile, buf, dataSize) != dataSize)
	{
		perror("Error reading from the I2C device");
		return 1;
	}
	return 0;	
}

uint16_t I2CHandler::ReadRegister(uint8_t reg, uint8_t dataSize)
{
	return 0;
}
	
int8_t I2CHandler::_openI2CBus()
{
	if((_i2cFile = open(_i2cDevice, O_RDWR)) < 0)
	{
		perror("Error opening the I2C device");
		return 1;
	}
	return 0;
}

int8_t I2CHandler::_setSlaveAddress()
{
	if(ioctl(_i2cFile, I2C_SLAVE, _deviceAddress))
	{
		perror("Error setting I2C slave address");
		return 1;
	}
	return 0;
}

I2CHandler::~I2CHandler()
{
	close(_i2cFile);
}
