#include "pwm.h"
#include <string.h>

PWMOutput::PWMOutput(const char* pinNumber) : _fileManager(&_fileHandler)
{
	_pinNumber = pinNumber;
	_filePath = _formatter.AddThreeStrings(PWM_PATH, "/pwmchip0/pwm", _pinNumber);
	_export(_pinNumber);
}

uint8_t PWMOutput::Enable()
{
	return _setEnableState("1");
}

uint8_t PWMOutput::SetDutyCycle(uint8_t percentage)
{
	uint32_t dutyCycle = _convertPercentageToNanoSeconds(percentage); 
	
	char* storedValuePath = _formatter.AddTwoStrings(_filePath, "/duty_cycle");

	printf("Setting DutyCycle to: %u, at: %s\n", dutyCycle, storedValuePath);
	return _fileHandler.WriteToFile(storedValuePath, _converter.ConvertIntToString(dutyCycle));
	return 0;
}

uint8_t PWMOutput::SetPeriod(const char* period)
{
	_period = period;

	char* storedValuePath = _formatter.AddTwoStrings(_filePath, "/period");

	printf("Setting Period to: %s, at: %s\n", _period, storedValuePath);
	return _fileHandler.WriteToFile(storedValuePath, _period);
}
uint8_t PWMOutput::Disable()
{
	return _setEnableState("0");
}

uint32_t PWMOutput::_convertPercentageToNanoSeconds(uint8_t percentage)
{
	if(percentage > 100) percentage = 100;
	else if(percentage < 0) percentage = 0;

	return (uint32_t) ((float)percentage/100 * _converter.ConvertStringToInt(_period, strlen(_period)));

}
uint8_t PWMOutput::_setEnableState(const char* state)
{
	char* storedValuePath = _formatter.AddTwoStrings(_filePath, "/enable");

	printf("Setting Enable to: %s, at: %s\n", state, storedValuePath);
	return _fileHandler.WriteToFile(storedValuePath, state);
}



uint8_t PWMOutput::_export(const char* pinNumber)
{
	char* exportPath = _formatter.AddTwoStrings(PWM_PATH, "/pwmchip0/export");
	uint8_t rc = _fileHandler.WriteToFile(exportPath, pinNumber); 
	printf("Writing: %s, to: %s\n", pinNumber, exportPath);
	return rc;
}

uint8_t PWMOutput::_unexport(const char* pinNumber)
{
	char* exportPath = _formatter.AddTwoStrings(PWM_PATH, "/pwmchip0/unexport");
	uint8_t rc = _fileHandler.WriteToFile(exportPath, pinNumber); 
	return rc;
}
