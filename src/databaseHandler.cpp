#include "databaseHandler.h"

PostgresHandler::PostgresHandler(const char* connInfo)
{
	_conn = PQconnectdb(connInfo);
	uint8_t result = _checkConnectionResultStatus("Connection to PostgreSQL failed: ");
}

uint8_t PostgresHandler::CreateDatabase(const char* databaseName)
{
	const char *query = _formatter.AddTwoStrings((const char*)"CREATE DATABASE ", databaseName);
	_res = _sendQuery(query);
	uint8_t result =  _checkResultStatus("Database creation failed: ");
	PQclear(_res);	
	return result;	
}

uint8_t PostgresHandler::_checkResultStatus(const char* errorMessage)
{
	if(PQresultStatus(_res) != PGRES_COMMAND_OK)
	{
		_printErrorAndExit(errorMessage);
		return 1;
	}
	
	return 0;
}

uint8_t PostgresHandler::ProbeDatabase(const char *databaseName)
{
	const char* query = _formatter.AddTwoStrings((const char*)"SELECT 1 FROM pg_database WHERE datname = ", databaseName);
	_res = _sendQuery(query);
	
	if(PQresultStatus(_res) != PGRES_TUPLES_OK)
	{
		const char* errorMessage = _formatter.AddThreeStrings((const char*)"Failed to probe database: ", (const char*)PQerrorMessage, "\n");
		_printErrorAndExit(errorMessage);
		return 2;
	}	
	
	if(PQntuples(_res) > 0)
	{
		//Database exist
		return 0;
	}
	else
	{
		PQclear(_res);
		const char* query = _formatter.AddTwoStrings("CREATE DATABASE ", databaseName);
		_res = _sendQuery(query);
		const char* errorMessage = _formatter.AddThreeStrings("Database creation failed: ", (const char*)PQerrorMessage, "\n");
		PQclear(_res);
		return _checkConnectionResultStatus(errorMessage);
	}
}


PGresult* PostgresHandler::_sendQuery(const char* query)
{
	return PQexec(_conn, query);
}

uint8_t PostgresHandler::CreateTable(const char* tableName, const char* values)
{
	const char* query = _formatter.AddThreeStrings((const char*)"CREATE TABLE ", tableName, values);
	// DO STUFF!	
}

uint8_t PostgresHandler::_checkConnectionResultStatus(const char* errorMessage)
{
	if(PQstatus(_conn) != CONNECTION_BAD)
	{
		_printErrorAndExit(errorMessage);
		return 1;
	}
	
	return 0;
}

void PostgresHandler::_printErrorAndExit(const char* errorMessage)
{
	const char* msg = _formatter.AddThreeStrings(errorMessage, (const char*)PQerrorMessage, "\n");
	fprintf(stderr, msg);
	_exit();
}

void PostgresHandler::_exit()
{
	PQclear(_res);
	PQfinish(_conn);
	exit(1);
}
