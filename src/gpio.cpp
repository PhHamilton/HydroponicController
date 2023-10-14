#include "gpio.h"
#include <stdint.h>

GPIO::GPIO(const char* pinNumber) : _fileManager(&_fileHandler)
{
	sprintf(_filePath, "%s/gpio%s", GPIO_PATH, pinNumber);
}

uint8_t GPIO::Get()
{
	char storedValuePath[PATH_MAX];
	sprintf(storedValuePath, "%s/value", _filePath);
	return _fileManager.ReadFile(storedValuePath);
}

uint8_t GPIO::Set(GPIO_MODE mode)
{
	const char* GPIOModeString = (mode == INPUT) ? "in" : "out";

	return _fileHandler.WriteToFile(GPIO_PATH, GPIOModeString);
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
