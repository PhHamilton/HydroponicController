#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "acutest.h"
#include "fileHandler.h"
#include "stringFormatter.h"
#include "dataTypeConverter.h"

const char* testFilePath = "utility";

FileHandler fileHandler;

void test_readNonExistingFile()
{
	/*	
		1. Read an nonexisting file
		2. Read an existing file
		3. Read the available files
	*/	

	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd)); 

	char filePath[PATH_MAX];
	sprintf(filePath, "%s/%s/%s", (const char*)cwd, testFilePath, "IDoNotExist");	

	uint8_t actual = fileHandler.ReadFile(filePath);	
	uint8_t expected = UNABLE_TO_OPEN_FILE;

	TEST_CHECK_(actual == expected, "Opening an nonexisting file, expected: %i, actual: %i", expected, actual);
}

void test_readExistingFile()
{
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd)); 

	char filePath[PATH_MAX];
	sprintf(filePath, "%s/%s/%s", (const char*)cwd, testFilePath, "direction");	

	//uint8_t actual = fileHandler.ReadFile(filePath);
	uint8_t actual = fileHandler.ReadFile("/Users/Philip/Documents/Programming/HydroponicController/utility/direction");
	uint8_t expected = OK;

	char* actualString = fileHandler.GetFileContent();
	const char* expectedString = "in\0";

	TEST_CHECK_(actual == expected, "Opening an existing file, expected: %i, actual: %i", expected, actual);
	TEST_CHECK_(strcmp(actualString, expectedString) == 0, "Reading an existing file, expected: %s, actual: %s", expectedString, actualString);
}

void test_writeToFile()
{
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd)); 

	char filePath[PATH_MAX];	
	sprintf(filePath, "%s/%s/%s", (const char*)cwd, testFilePath, "direction");	

	const char* expectedString = "out";
	uint8_t actual = fileHandler.WriteToFile(filePath, expectedString);

	uint8_t expected = OK;

	TEST_CHECK_(actual == expected, "Opening a file to writen, expected: %i, actual: %i", expected, actual);

	fileHandler.ReadFile(filePath);
	const char* actualString = fileHandler.GetFileContent();

	TEST_CHECK_(strcmp(actualString, expectedString) == 0, "Reading an existing file, expected: %s, actual: %s", expectedString, actualString);

	// Restore back to "in"
	fileHandler.WriteToFile(filePath, "in");
}

void test_addStrings()
{
	StringFormatter formatter; 
	const char* string1 = "abc";
	const char* string2 = "def";

	const char* result = formatter.AddTwoStrings(string1, string2);
	const char* expected = "abcdef";
	TEST_CHECK_(strcmp(result, expected) == 0, "Adding strings, %s and %s, expected %s, actual: %s", string1, string2, expected, result);

	const char* result2 = formatter.AddTwoStrings(string2, string1);
	const char* expected2 = "defabc";
	TEST_CHECK_(strcmp(result2, expected2) == 0, "Adding strings, %s and %s, expected %s, actual: %s", string2, string1, expected2, result2);
	TEST_CHECK_(strcmp(result, expected) == 0, "Checking previous test!, %s and %s, expected %s, actual: %s", string1, string2, expected, result);
}

void test_typeConverter()
{
	DataTypeConverter converter;
	const char* testValues[7] = {"1", "10", "100", "1000", "-1", "500000", "1000000000"};
	int32_t expected[7] = {1, 10, 100, 1000, -1, 500000, 1000000000};
	for(int i = 0; i < 7; i++)
	{
		int32_t actual = converter.ConvertStringToInt(testValues[i], strlen(testValues[i])); 
		TEST_CHECK_(expected[i] == actual, "Testing TypeConverter, Expected: %i, Actual: %i", expected[i], actual);
		char* reverted = converter.ConvertIntToString(expected[i]);
		TEST_CHECK_(strcmp(reverted, testValues[i]) == 0, "Testing TypeConverter, Expected: %s, Actual: %s", testValues[i], reverted);
	}

}
TEST_LIST = 
{
	{"Reading an non-existing file", test_readNonExistingFile},  
	{"Reading an existing file", test_readExistingFile},  
	{"Writing to an existing file", test_writeToFile},  
	{"Adding two strings", test_addStrings},  
	{"Converting string to int", test_typeConverter},  
	{0}
};
