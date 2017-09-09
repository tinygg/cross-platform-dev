#pragma once

#include <string>
#include <cppconn/driver.h>
#include <cppconn/statement.h>

using namespace std;

class MysqlHelper
{
public:
	static sql::Driver* driver;
	static sql::SQLString conn_str;
	static sql::SQLString db_name;
	static sql::SQLString username;
	static sql::SQLString passwd;

	MysqlHelper();
	MysqlHelper(const char* db_name , const char* conn_str = "tcp://127.0.0.1:3306", const char* user_name = "root", const char* passwd = "root");
	//sql::ResultSet* Query(const char* sql);
	void Close();
	~MysqlHelper();
};

