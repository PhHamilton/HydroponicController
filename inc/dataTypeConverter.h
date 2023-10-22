#ifndef DATA_TYPE_CONVERTER_H
#define DATA_TYPE_CONVERTER_H

#include <stdint.h>

class DataTypeConverter
{
	public: 
		int32_t ConvertStringToInt(const char* string, uint8_t size);
		char* ConvertIntToString(int32_t intNumber);
};

#endif
