#include "fileManager.h"


FileManager::FileManager(FileHandlerInterface *handler)
{
	_fileHandler = handler;
}
uint8_t FileManager::ReadFile(const char* filePath)
{
	return _fileHandler->ReadFile(filePath);
}

const char* FileManager::GetFileContent()
{
	return _fileHandler->GetFileContent();
}

uint8_t FileManager::WriteToFile(const char* filePath, const char* data)
{
	return _fileHandler->WriteToFile(filePath, data);
}
	
