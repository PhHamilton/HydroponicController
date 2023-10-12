#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "acutest.h"
#include "fileHandler.h"

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

TEST_LIST = 
{
	{"Reading an non-existing file", test_readNonExistingFile},  
	{"Reading an existing file", test_readExistingFile},  
	{"Writing to  an existing file", test_writeToFile},  
	{0}
};
