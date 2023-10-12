#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include "fileManager.h"
#include "fileHandler.h"

#define GPIO_PATH "/sys/class/gpio/"

typedef enum
{
	INPUT,
	OUTPUT
}GPIO_MODE;

typedef enum
{
	LOW,
	HIGH,
} PIN_STATES;

typedef enum 
{
	RISING,
	FALLING
} DETECTION_TYPE;

typedef enum
{
} GPIO_ERROR_CODES;

class GPIO
{
	public:
		GPIO(uint8_t pinNumber);
		uint8_t Get();
		uint8_t Set(GPIO_MODE mode);
		uint8_t Toggle();
		uint8_t EnableSoftwareDebounce(uint8_t debounceTime);
	private:
		uint8_t _write();
		uint8_t _read();
		uint8_t _export();
		uint8_t _debounceTime;
		uint8_t _pinNumber;
		
		FileManager _fileManager;
		FileHandler _fileHandler;		
};

#endif
