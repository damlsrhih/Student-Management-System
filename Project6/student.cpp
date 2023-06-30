#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "password.h"
#include "clear.h"
#include "main.h"
#include "hash.h"
#include <mysql.h>

gl guanli = {"admin","benjo"};        //管理员信息
char random[6] = { '\0' };            //生成验证码（验证码包含数字大小写英文）


bool connectDB2(MYSQL &mysql) {        //防止内存占用bug的权宜之计
	// 1.初始化数据库句柄
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

	//printf("数据库选择成功！\n");

	return true;
}



char *randint()            //生成验证码
{
	/*48-57,65-90,97-122*/
	int i = 0;
	int c = 0;
	char *p = random;
	srand((unsigned)time(NULL));
	for (i = 0; i < 5; i++)
	{
		c = rand() % 3 + 1;
		if (c > 2)
		{
			c = 0;
		}
		if (c == 0)
		{
			random[i] = abs(rand()) % 10 + 48;;
		}
		if (c == 1)
		{
			random[i] = abs(rand()) % 26 + 65;
		}
		if (c == 2)
		{
			random[i] = abs(rand() % 26 + 97);
		}
	}

	FILE * fp;
	errno_t err = fopen_s(&fp, "./Text.txt", "w+");
	fprintf(fp, "%s", random);
	fclose(fp);
	fp = NULL;
	return p;
}

int stu_login()                    //学生登录
{
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[256];	// SQL语句
	char *p1 = NULL;       //存放密码
	int user_id1 = 0;      //存放id
	char user_password[11] = { '\0' };    //输入的密码
	char user_epassword[6] = { '\0' };    //输入的验证码
	int i = 0;
	printf_s("请输入您的用户名:\n");
	fflush(stdin);
	scanf_s("%d", &user_id1);
	if (!connectDB2(mysql)) {
		return false;
	}

	// C语言组合字符串

	snprintf(sql, 256, "SELECT password FROM students WHERE id = %d;", user_id1);
	//printf_s("查询sql语句：%s\n", sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf_s("执行查询语句，查询返回结果：%d\n", ret);

	if (ret) {
		printf("数据查询失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}

	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	p1 = row[0];
	printf_s("请输入您的密码:\n");
	Getpwd(user_password);
	printf_s("%s\n", user_password);
	printf_s("请输入验证码:\n");
	printf_s("请注意验证码区分大小写!\n");
	char *p = randint();
	fflush(stdin);
	scanf_s("%s", user_epassword, 6);
	clear();
	//scanf_s 里面buf的值应该大于你输入的字符串的长度否则写入失败
	if (!ret)
	{
		if (strcmp(user_password, p1) == 0)
		{
			if (strcmp(user_epassword, p) == 0)//epassword 验证码
			{
				printf_s("登录成功\n");
				return user_id1;
			}
			else
			{
				printf_s("登录失败:验证码错误\n");
				return 2;
			}
		}
		else
		{
			printf_s("登录失败:用户名或密码错误\n");
			return 0;
		}
	}
	else
	{
		printf_s("登录失败:用户名或密码错误\n");
		return 0;
	}

}

int gl_login()          //管理登录
{
	char user_name[11] = { '\0' };    //管理用户名
	char user_password[11] = { '\0' };  //管理密码
	printf_s("请输入您的用户名\n");
	fflush(stdin);
	scanf_s("%s", user_name, 10);
	printf_s("请输入您的密码\n");
	Getpwd(user_password);
	clear();
	if (strcmp(user_name, guanli.name) == 0)
	{
		if (strcmp(user_password, guanli.password) == 0)
		{
			printf_s("登录成功\n");
			return 1;
		}
		else
		{
			printf_s("登录失败:用户名或密码错误\n");
			return 0;
		}
	}
	else
	{
		printf_s("登录失败:用户名或密码错误\n");
		return 0;
	}
}
/*int con_log()
{

	实现替换for循环内的东西

}*/
int login()           //登录界面
{
	int user = 0;
	int login_over = 0; //判断登录状态 0用户名密码错误 1登录成功 2验证码错误
	int yz = 0;     //判断重新登录还是退出 1重新登录 2退出
	int i = 0;
	int out = 0;  //返回登录状态
	printf_s("请输入您的身份\n");
	printf_s("\t输入1为学生");
	printf_s("\t输入2为管理员\n");
	fflush(stdin);
	scanf_s("%d", &user);
	clear();
	if (user == 1)
	{
		for (i = 0; i < 3; i++)
		{
			login_over = stu_login();
			printf_s("\n");
			if (login_over == 0 && i != 2)
			{
				printf_s("\n");
				printf_s("请检查您的用户名或密码\n");
				printf_s("\t输入1重新登录     输入2退出\n");
				fflush(stdin);
				scanf_s("%d", &yz);
				if (yz == 1)
				{
					clear();
					continue;
				}
				if (yz == 2)
				{
					clear();
					printf_s("欢迎您下次使用\n");
					return out = login_over;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("请输入正确指令\n");
						fflush(stdin);
						scanf_s("%d", &yz);
						if (yz == 1 || yz == 2)
						{
							break;
						}
					}
				}
			}
			if (login_over != 0 && login_over != 2)
			{
				break;
			}
			if (login_over == 2 && i != 2)
			{
				printf_s("\n");
				printf_s("\t输入1重新登录     输入2退出\n");
				fflush(stdin);
				scanf_s("%d", &yz);
				if (yz == 1)
				{
					clear();
					continue;
				}
				if (yz == 2)
				{
					clear();
					printf_s("欢迎您下次使用\n");
					return out = 2;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("请输入正确指令\n");
						fflush(stdin);
						scanf_s("%d", &yz);
						if (yz == 1 || yz == 2)
						{
							break;
						}
					}
				}
			}
		}
		if (login_over != 0 && login_over != 2)
		{
			return out = login_over;
		}
		if (i >= 2)
		{
			return out = 2;
		}
	}
	if(user == 2)
	{
		for (i = 0; i < 3; i++)
		{
			login_over = gl_login();
			if (login_over == 0 && i != 2)
			{
				printf_s("\n");
				printf_s("请检查您的用户名或密码\n");
				printf_s("\t输入1重新登录     输入2退出\n");
				fflush(stdin);
				scanf_s("%d", &yz);
				if (yz == 1)
				{
					clear();
					continue;
				}
				if (yz == 2)
				{
					printf_s("欢迎您下次使用\n");
					return out = 3;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("请输入正确指令\n");
						fflush(stdin);
						scanf_s("%d", &yz);
						if (yz == 1 || yz == 2)
						{
							break;
						}
					}
				}
			}
			if (login_over == 1)
			{
				break;
			}
			if (login_over == 2 && i != 2)
			{
				printf_s("\n");
				printf_s("\t输入1重新登录     输入2退出\n");
				fflush(stdin);
				scanf_s("%d", &yz);
				if (yz == 1)
				{
					clear();
					continue;
				}
				if (yz == 2)
				{
					printf_s("欢迎您下次使用\n");
					return out = 4;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("请输入正确指令\n");
						fflush(stdin);
						scanf_s("%d", &yz);
						if (yz == 1 || yz == 2)
						{
							break;
						}
					}
				}
			}
		}
		if (login_over == 1)
		{
			return out = 3;
		}
		if (i >= 2)
		{
			return out = 4;
		}
	}
}