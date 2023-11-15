#include "ads1015.h"
#include <stdio.h>
#include <string.h>

ADS1015::ADS1015(ADS1015_CONFIG config) : _i2cHandler(config.deviceAddress, config.i2cAdapter)
{
    // Set default settings!
    _buf[0] = 0x01;
    _buf[1] = 0xC0;
    _buf[2] = 0x83;
	
	memcpy(&_config, &config, sizeof(config));	

    _i2cHandler.Open();
    _i2cHandler.Write(_buf, 3); 
    _i2cHandler.Close();
}

uint16_t ADS1015::Read(ADS1015_CHANNELS channel)
{
    _i2cHandler.Open();
    if(channel != _currentChannel) // We need to update the config register!
    {
        
        _buf[0] = CONFIG_REGISTER;
        _i2cHandler.Write(_buf, 3);
        // Change the config register, set so that we keep reding the config register!
        _buf[0] = CONVERSION_REGISTER;
        _i2cHandler.Write(_buf, 1);
    }
    else
    {
        
    }
    _buf[0] = 0x00;
    
    _i2cHandler.Write(_buf, 1);
    _i2cHandler.Read(_buf, 2);

    _i2cHandler.Close();

    printf("Read Hex Values = 0x%02X%02X \t", _buf[0], _buf[1]);
    _latestValue = _buf[0] << 4 | _buf[1] >> 4;
    return _latestValue;
}
