#ifndef DATABASE_HANDLER_INTERFACE
#define DATABASE_HANDLER_INTERFACE
#include <stdint.h>

class DatabaseHandlerInterface
{
	public:
		virtual uint8_t CreateDatabase(const char* databaseName) = 0;
		virtual uint8_t ProbeDatabase(const char * databaseName) = 0;
		virtual uint8_t Connect() = 0;
		virtual uint8_t Disconnect() = 0;
		virtual uint8_t Open() = 0;
		virtual uint8_t CreateTable(const char* tableName, const char* values) = 0;
		virtual uint8_t Insert(const char* tableName, const char* values) = 0;
		virtual uint8_t Remove() = 0;
};

#endif
