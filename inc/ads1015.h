#ifndef ADS1015_H
#define ADS1015_H
#include <stdint.h>
#include "fileManager.h"
#include "fileHandler.h"


class ADS1015
{
	public:
		ADS1015(uint8_t deviceAdress, const char* i2cAdapter);
		uint8_t Initialize();
		uint8_t Read(uint8_t channel);
		~ADS1015();
	private:
		uint8_t _deviceAddress;
		const char* _filePath;
		FileHandler _fileHandler;
		FileManager _fileManager;
};
#endif
