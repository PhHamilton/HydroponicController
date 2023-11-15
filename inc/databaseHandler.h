#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER
#include <stdio.h>
#include <stdlib.h>
#include </usr/include/postgresql/libpq-fe.h>
#include "databaseHandlerInterface.h"
#include "stringFormatter.h"

class PostgresHandler : public DatabaseHandlerInterface
{
	public:
		PostgresHandler(const char* connInfo);
		uint8_t CreateDatabase(const char* databaseName) override;
		uint8_t ProbeDatabase(const char * databaseName) override;
		uint8_t Connect() override;
		uint8_t Disconnect() override;
		uint8_t Open() override;
		uint8_t CreateTable(const char* tableName, const char* values) override;
		uint8_t Insert(const char* tableName, const char* values) override;
		uint8_t Remove() override;

	private:
		PGconn *_conn;
		PGresult *_res;
		
		uint8_t _checkResultStatus(const char* errorMessage);
		uint8_t _checkConnectionResultStatus(const char* errorMessage);
		PGresult* _sendQuery(const char* query);
		void _printErrorAndExit(const char* errorMessage);
		void _exit();

		StringFormatter _formatter;	
};
#endif
