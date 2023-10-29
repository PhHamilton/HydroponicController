#ifndef I2C_HANDLER
#define I2C_HANDLER

#include <stdint.h>
#include "fileHandler.h"
#include "fileManager.h"
#include "stringFormatter.h"

#define I2C_PATH "/dev"
#define I2C_BUFF_SIZE 256

class I2CHandler
{
	public:
		I2CHandler(uint8_t deviceAddress, const char* I2CAdapter);
		uint8_t Initialize();
		uint8_t Write(uint8_t data[], uint8_t dataSize);
		uint8_t Read(uint8_t buf[], uint8_t dataSize);
		uint16_t ReadRegister(uint8_t reg, uint8_t dataSize);
		~I2CHandler();
	private: 
		int8_t _openI2CBus();
		int8_t _setSlaveAddress();
		char _buffer[I2C_BUFF_SIZE];
		
		uint8_t _deviceAddress;
		const char* _i2cDevice;		
		int8_t _i2cFile;	
		FileHandler _fileHandler;
		FileManager _fileManager;
		StringFormatter _formatter;
};

#endif
