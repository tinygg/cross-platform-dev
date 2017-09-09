#visual studio 2017 Community 编译跨平台C++项目(使用libmysqlcppconn-dev静态库连接数据库)

（1.项目准备）
===============================================================================
#新建项目ConsoleApplication1
模板路径:Visual C++/跨平台/Linux/控制台应用程序(Linux)

（必须）
#安装libmysqlcppconn库文件(会自动安装boost-dev包)
sudo apt-get install libmysqlcppconn-dev  
#可以用过 dpkg -L libmysqlcppconn-dev查看开发包的文件结构

（必须）
#拷贝libmysqlcppconn-dev头文件至windows本地
cd /usr/include
sudo tar zcvf usr_include_libmysqlcppconn.tar.gz mysql_* cppconn/*
#再通过xftp传输至本地->解压->复制至windows目录(C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\Linux\include\usr\include)

(可选)
#显示指定系统include目录(项目里面可以使用小括号include mysql的头文件,可以不做这个操作, 但MysqlHelper.h中对应使用冒号引用mysql头文件即可)
#项目->右键->项目属性->VC++目录->包含目录填入(C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\Linux\include\usr\include)

（必须）
#项目-右键->项目属性->链接器->输入->库依赖项(静态库lib开头.a结束):mysqlcppconn
or
#项目-右键->项目属性->链接器->输入->附加依赖项:填写全路径:/usr/lib/libmysqlcppconn.a

（2.数据库准备）
===============================================================================
#测试,安装mysql服务器
sudo apt-get install mariadb-server
sudo /etc/init.d/mysql start
sudo mysql #直接登录

#新建用户
create user 'ubuntu'@'%' identified by '123';

#新建数据库、表，插入测试数据
:<<SQL
-- --------------------------------------------------------
-- 主机:                           127.0.0.1
-- 服务器版本:                        5.5.27 - MySQL Community Server (GPL)
-- 服务器操作系统:                      Win32
-- HeidiSQL 版本:                  9.4.0.5125
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- 导出 test_mysql_cppconn 的数据库结构
DROP DATABASE IF EXISTS `test_mysql_cppconn`;
CREATE DATABASE IF NOT EXISTS `test_mysql_cppconn` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `test_mysql_cppconn`;

-- 导出  表 test_mysql_cppconn.hello 结构
DROP TABLE IF EXISTS `hello`;
CREATE TABLE IF NOT EXISTS `hello` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- 正在导出表  test_mysql_cppconn.hello 的数据：5 rows
DELETE FROM `hello`;
/*!40000 ALTER TABLE `hello` DISABLE KEYS */;
INSERT INTO `hello` (`id`, `name`) VALUES
	(1, 'z'),
	(2, 'w'),
	(3, '你'),
	(4, '好'),
	(5, '！');
/*!40000 ALTER TABLE `hello` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;

SQL

#赋予权限
grant all privileges on test_mysql_cppconn.* to ubuntu;
flush privileges;

(3.项目生成、设置远程连接IP、账户、密码，调试、运行)
OK!