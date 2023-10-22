#ifndef PWM_H
#define PWM_H

#include <stdio.h>
#include <stdint.h>
#include "fileHandler.h"
#include "fileManager.h"
#include "stringFormatter.h"
#include "dataTypeConverter.h"

#define PWM_PATH "/sys/class/pwm"
#define PWM_PERIOD "1000000" // 1 kHz

class PWMOutput
{
	public:
		PWMOutput(const char* pinNumber);
		uint8_t Enable();
		uint8_t SetPeriod(const char* period);
		uint8_t SetDutyCycle(uint8_t percentage);
		uint8_t Disable();
		~PWMOutput(){_unexport(_pinNumber);}
	private:
		const char* _pinNumber;
		uint8_t _write(const char* fileName, const char* value);
		uint8_t _read();
		uint32_t _convertPercentageToNanoSeconds(uint8_t percentage);
		uint8_t _setEnableState(const char* state);
		uint8_t _export(const char *pinNumber);
		uint8_t _unexport(const char *pinNumber);
		const char* _period;

		char* _filePath = new char[MAX_STRING_SIZE];
		FileHandler _fileHandler;
		FileManager _fileManager; 
		StringFormatter _formatter;
		DataTypeConverter _converter;
};


#endif
