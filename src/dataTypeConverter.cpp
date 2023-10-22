#include "dataTypeConverter.h"
#include <math.h>

int32_t DataTypeConverter::ConvertStringToInt(const char* string, uint8_t size)
{
	int32_t result = 0;
	uint8_t negativeValue, startIndex;

	if(string[0] == '-')
	{
		negativeValue = 1;
		startIndex = 1;
	}
	else
	{
		negativeValue = 0;
		startIndex = 0;
	}	
	for(int i = startIndex; i < size; i++)
		result += (string[i]-0x30) * pow(10, (size-1) - i);
	
	return (negativeValue) ? -result : result;

}

char* DataTypeConverter::ConvertIntToString(int32_t intNumber)
{
	uint8_t nDigits, negativeValue;
	int32_t sIntNumber = intNumber;
	if(intNumber < 0)
	{
		sIntNumber *= -1;
		negativeValue = 1;	
		nDigits = floor(log10(sIntNumber)) + 2; // + 2 to include the negative sign!
	}
	else
	{
		negativeValue = 0;
		nDigits = floor(log10(sIntNumber)) + 1;
	}

	char* num = new char[nDigits + 1];
	
	for(int i = 0; i < nDigits; i++)
	{
		num[nDigits-(i+1)] = 0x30 + sIntNumber % 10; 
		sIntNumber /= 10;
	} 
	
	num[nDigits] = '\0';
	if(negativeValue)
		num[0] = '-';

	return num;
}
