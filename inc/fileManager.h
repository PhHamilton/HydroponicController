#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include "fileHandlerInterface.h"
#include "fileHandler.h"

class FileManager
{
	public:
		FileManager(FileHandlerInterface *handler);
		uint8_t ReadFile(const char* filePath);
		const char* GetFileContent(); 
		uint8_t WriteToFile(const char* filePath, const char* data);
	private: 
		FileHandlerInterface *_fileHandler;
};
#endif
