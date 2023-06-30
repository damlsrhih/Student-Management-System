#include <mysql.h>
#include <stdio.h>

bool connectDB3(MYSQL &mysql) {     
	mysql_init(&mysql);

	// 2.设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "UTF8");

	// 3.连接数据库

	MYSQL *ret = mysql_real_connect(&mysql, "127.0.0.1", "root", "7895123460", "stu_data", 3306, NULL, 0);
	if (ret == NULL) {
		printf("数据库连接失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}

	//printf("数据连接成功！\n");

	// 选择数据库
	int res = mysql_select_db(&mysql, "stu_data");
	if (res) {
		printf("选择数据库失败！失败原因%s\n", mysql_error(&mysql));
		return false;
	}

	printf("数据库选择成功！\n");

	return true;
}

int main()                    //学生登录
{
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体

	if (!connectDB3(mysql)) {
		return false;
	}
}