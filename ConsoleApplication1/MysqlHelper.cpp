#include "MysqlHelper.h"
#include "INIParser.h"

int db_instance;

sql::Driver* MysqlHelper::driver;
sql::SQLString MysqlHelper::conn_str;
sql::SQLString MysqlHelper::db_name;
sql::SQLString MysqlHelper::username;
sql::SQLString MysqlHelper::passwd;

MysqlHelper::MysqlHelper()
{
	if (db_instance == 0)
	{
		this->driver = get_driver_instance();
		//静态化
		INIParser ini_parser;
		ini_parser.ReadINI("conf.ini");
		string mysql_addr = ini_parser.GetValue("default", "mysql_addr");
		string mysql_port = ini_parser.GetValue("default", "mysql_port");
		string mysql_name = ini_parser.GetValue("default", "mysql_name");
		string mysql_pwd = ini_parser.GetValue("default", "mysql_pwd");
		string db_name = ini_parser.GetValue("default", "db_name");
		string conn_str = "tcp://" + mysql_addr + ":" + mysql_port;

		this->conn_str = sql::SQLString(conn_str.c_str());
		this->db_name = sql::SQLString(db_name.c_str());
		this->username = sql::SQLString(mysql_name.c_str());
		this->passwd = sql::SQLString(mysql_pwd.c_str());

		db_instance = 1;
	}
}

MysqlHelper::MysqlHelper(const char* db_name, const char* conn_str, const char* username, const char* passwd)
{
	this->driver = get_driver_instance();

	this->conn_str = conn_str;
	this->db_name = db_name;
	this->username = username;
	this->passwd = passwd;
}


//如果不采用unique_ptr conn和stat很容易产生内存泄漏,目前没有手动释放的demo,
//用uniq_ptr产生的返回的sql::ResultSet*必须也是unique_ptr，但是离开方法体，unique_ptr就会销毁所以并不适合封装起来，此方法不可用！！！
//sql::ResultSet* MysqlHelper::Query(const char* sql)
//{
	//重要修改
	
	//sql::Connection* conn;
	//sql::Statement* stmt;
	//conn = this->driver->connect(this->conn_str.c_str(), this->username.c_str(), this->passwd.c_str());	
	//stmt = conn->createStatement();	
	//return stmt->executeQuery(sql::SQLString(sql));

	//std::unique_ptr<sql::Connection> conn(this->driver->connect(this->conn_str.c_str(), this->username.c_str(), this->passwd.c_str()));
	//conn->setSchema(db_name.c_str());
	//std::unique_ptr<sql::Statement> stmt(conn->createStatement());
	//std::unique_ptr<sql::ResultSet> rlt(stmt->executeQuery(sql::SQLString(sql)));
//}

void MysqlHelper::Close()
{
	//delete this->stmt;
	//free(this->stmt);//重要修改
	//delete this->conn;
	//free(this->conn);//重要修改
	//this->driver->threadEnd();
}


MysqlHelper::~MysqlHelper()
{
	cout << "析构 MysqlHelper ing...";
	//this->Close();
}
