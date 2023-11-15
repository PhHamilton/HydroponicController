#ifndef ADS1015_H
#define ADS1015_H
#include <stdint.h>
#include "fileManager.h"
#include "fileHandler.h"
#include "i2cHandler.h"

#define CONVERSION_REGISTER 0x00
#define CONFIG_REGISTER		0x01

typedef enum
{
	continous,
	single_shot
}ADS1015_MODES;

typedef enum
{
	A0 = 0x04,
	A1 = 0x05,
	A2 = 0x06,
	A3 = 0x07
}ADS1015_CHANNELS;

typedef enum
{
	SPS_128,
	SPS_250,
	SPS_490,
	SPS_920,
	SPS_1600,
	SPS_2400,
	SPS_3300
}ADS1015_DATA_RATE;

typedef struct
{
	uint8_t deviceAddress;
	const char* i2cAdapter;
	ADS1015_MODES mode;
	ADS1015_DATA_RATE dataRate;
}ADS1015_CONFIG;
	

class ADS1015
{
	public:
		ADS1015(ADS1015_CONFIG config);
		uint16_t Read(ADS1015_CHANNELS channel);
	private:
		ADS1015_CONFIG _config;
		ADS1015_CHANNELS _currentChannel;
		uint16_t _latestValue;
		uint8_t _buf[3];
		I2CHandler _i2cHandler;
};


#endif
