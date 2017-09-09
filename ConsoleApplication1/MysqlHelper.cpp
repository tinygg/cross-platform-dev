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
		//��̬��
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


//���������unique_ptr conn��stat�����ײ����ڴ�й©,Ŀǰû���ֶ��ͷŵ�demo,
//��uniq_ptr�����ķ��ص�sql::ResultSet*����Ҳ��unique_ptr�������뿪�����壬unique_ptr�ͻ��������Բ����ʺϷ�װ�������˷��������ã�����
//sql::ResultSet* MysqlHelper::Query(const char* sql)
//{
	//��Ҫ�޸�
	
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
	//free(this->stmt);//��Ҫ�޸�
	//delete this->conn;
	//free(this->conn);//��Ҫ�޸�
	//this->driver->threadEnd();
}


MysqlHelper::~MysqlHelper()
{
	cout << "���� MysqlHelper ing...";
	//this->Close();
}
