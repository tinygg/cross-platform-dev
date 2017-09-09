using namespace std;

#include <sstream>
#include <string>
#include "MysqlHelper.h"
using namespace std;
#define TBLNAME "hello"

void Query()
{
	ostringstream sql_oss;
	sql_oss << "select * from `" << TBLNAME << "` where 1 = 1";
	//hz不是真实频率,因为低于1hz的参数被放大到1hz来译码

	string sql_str = sql_oss.str();//输出
	cout << "sql_str = " << sql_str.c_str() << endl;

	MysqlHelper mysql_config;
	sql::Driver* driver = MysqlHelper::driver;
	std::unique_ptr<sql::Connection> conn(driver->connect(MysqlHelper::conn_str, MysqlHelper::username, MysqlHelper::passwd));
	conn->setSchema(mysql_config.db_name);
	std::unique_ptr<sql::Statement> stmt(conn->createStatement());
	std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery(sql::SQLString(sql_oss.str().c_str())));

	while (rs->next())
	{
		cout << "id=" << rs->getInt("id") << "| name=" << rs->getString("name").c_str() << endl;
	}

	driver = NULL;
}

int main() {
	Query();
	return 0;
}
