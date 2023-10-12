#include "gpio.h"
#include <stdint.h>

GPIO::GPIO(uint8_t pinNumber) : _fileManager(&_fileHandler)
{
	_pinNumber = pinNumber;

}

uint8_t GPIO::Get()
{
	return 0; 
}

uint8_t GPIO::Set(GPIO_MODE mode)
{
	const char* GPIOModeString = (mode == INPUT) ? "in" : "out";

	uint8_t rc = _fileManager.WriteToFile(GPIO_PATH, GPIOModeString);
	return 0;
}

uint8_t GPIO::Toggle()
{
	return 0;
}
uint8_t GPIO::EnableSoftwareDebounce(uint8_t debounceTime)
{
	_debounceTime = debounceTime;
	return 0;
}

uint8_t GPIO::_write()
{
	return 0;
}

uint8_t GPIO::_read()
{
	return 0;
}

uint8_t GPIO::_export()
{
	return 0;
}
