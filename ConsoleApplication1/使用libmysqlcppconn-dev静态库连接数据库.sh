#visual studio 2017 Community �����ƽ̨C++��Ŀ(ʹ��libmysqlcppconn-dev��̬���������ݿ�)

��1.��Ŀ׼����
===============================================================================
#�½���ĿConsoleApplication1
ģ��·��:Visual C++/��ƽ̨/Linux/����̨Ӧ�ó���(Linux)

�����룩
#��װlibmysqlcppconn���ļ�(���Զ���װboost-dev��)
sudo apt-get install libmysqlcppconn-dev  
#�����ù� dpkg -L libmysqlcppconn-dev�鿴���������ļ��ṹ

�����룩
#����libmysqlcppconn-devͷ�ļ���windows����
cd /usr/include
sudo tar zcvf usr_include_libmysqlcppconn.tar.gz mysql_* cppconn/*
#��ͨ��xftp����������->��ѹ->������windowsĿ¼(C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\Linux\include\usr\include)

(��ѡ)
#��ʾָ��ϵͳincludeĿ¼(��Ŀ�������ʹ��С����include mysql��ͷ�ļ�,���Բ����������, ��MysqlHelper.h�ж�Ӧʹ��ð������mysqlͷ�ļ�����)
#��Ŀ->�Ҽ�->��Ŀ����->VC++Ŀ¼->����Ŀ¼����(C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\Linux\include\usr\include)

�����룩
#��Ŀ-�Ҽ�->��Ŀ����->������->����->��������(��̬��lib��ͷ.a����):mysqlcppconn
or
#��Ŀ-�Ҽ�->��Ŀ����->������->����->����������:��дȫ·��:/usr/lib/libmysqlcppconn.a

��2.���ݿ�׼����
===============================================================================
#����,��װmysql������
sudo apt-get install mariadb-server
sudo /etc/init.d/mysql start
sudo mysql #ֱ�ӵ�¼

#�½��û�
create user 'ubuntu'@'%' identified by '123';

#�½����ݿ⡢�������������
:<<SQL
-- --------------------------------------------------------
-- ����:                           127.0.0.1
-- �������汾:                        5.5.27 - MySQL Community Server (GPL)
-- ����������ϵͳ:                      Win32
-- HeidiSQL �汾:                  9.4.0.5125
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- ���� test_mysql_cppconn �����ݿ�ṹ
DROP DATABASE IF EXISTS `test_mysql_cppconn`;
CREATE DATABASE IF NOT EXISTS `test_mysql_cppconn` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `test_mysql_cppconn`;

-- ����  �� test_mysql_cppconn.hello �ṹ
DROP TABLE IF EXISTS `hello`;
CREATE TABLE IF NOT EXISTS `hello` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- ���ڵ�����  test_mysql_cppconn.hello �����ݣ�5 rows
DELETE FROM `hello`;
/*!40000 ALTER TABLE `hello` DISABLE KEYS */;
INSERT INTO `hello` (`id`, `name`) VALUES
	(1, 'z'),
	(2, 'w'),
	(3, '��'),
	(4, '��'),
	(5, '��');
/*!40000 ALTER TABLE `hello` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;

SQL

#����Ȩ��
grant all privileges on test_mysql_cppconn.* to ubuntu;
flush privileges;

(3.��Ŀ���ɡ�����Զ������IP���˻������룬���ԡ�����)
OK!