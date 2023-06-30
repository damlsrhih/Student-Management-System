#include <stdio.h>
#include <string.h>
#include "password.h"
#include "clear.h"
#include "student.h"
#include "main.h"
#include "hash.h"
#include "os.h"
#include <mysql.h>
#include <time.h>
#include <windows.h> 

//结构体重定义问题
//getpwd 回退显示问题
//修改密码
bool connectDB1(MYSQL &mysql) {
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


int change_ps(int uc)
{
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[256];	// SQL语句
	char *p = NULL;
	s1 student1 = {};        //暂存数据
	int user = 0;			//存放用户操作
	int user1 = 0;           //存放用户操作
	int i = 0;              
	char user_name[20] = { '\0' };         //存放用户名但已经被废弃  
	char user_password[11] = { '\0' };       //存放用户输入的密码
	char newuser_password[11] = { '\0' };       //存放用户新输入的密码
	char newuser_password1[11] = { '\0' };		//用于同用户新输入的密码比较
	if (!connectDB1(mysql)) {
		return false;
	}

	// C语言组合字符串

	snprintf(sql, 256, "SELECT password FROM students WHERE id = %d;", uc);
	//printf_s("查询sql语句：%s\n", sql);

	// 查询数据
	//int ret = mysql_query(&mysql, "select * from student;");		// 等效于下面一行代码
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf_s("执行查询语句，查询返回结果：%d\n", ret);

	if (ret) {
		printf("数据查询失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}
	//printf_s("数据查询成功！\n");
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	p = row[0];
	if (1)
	{
		printf_s("请输入您的原密码\n");
		Getpwd(student1.password);
		if (strcmp(student1.password, p) == 0)
		{
			clear();
			printf_s("请输入您的新密码\n");
			Getpwd(newuser_password);
			while (true)
			{
				if (strcmp(newuser_password, p) == 0)
				{
					clear();
					printf_s("新旧密码不能一致,请重新输入\n");//退出识别最后再做
					Getpwd(newuser_password);
					printf_s("\n");

				}
				else
				{
					break;
				}
			}

			printf_s("\n");
			printf_s("请确认您的新密码\n");
			Getpwd(newuser_password1);
			printf_s("\n");
			if (strcmp(newuser_password, newuser_password1) == 0)
			{
				printf_s("您确定修改密码吗\n");
				printf_s("输入1确定      输入2退出\n");
				scanf_s("%d", &user1);
				if (user1 == 1)
				{
					for (int i = 0; i < 6; i++)//6是密码长度
					{
						student1.password[i] = newuser_password[i];

					}
				}
				if (user1 == 2)
				{
					return 0;
				}
				if (user1 != 1 && user1 != 2)
				{
					printf_s("请输入正确指令");
				}
			}
			else
			{
				while (true)
				{
					printf_s("两次输入的密码不一致\n");
					printf_s("输入1重新确认密码         输入2退出密码修改\n");
					scanf_s("%d", &user);
					if (user == 1)
					{
						clear();
						printf_s("请确认您的新密码\n");
						Getpwd(newuser_password1);
						printf_s("\n");
						if (strcmp(newuser_password, newuser_password1) == 0)
						{
							printf_s("您确定修改密码吗\n");
							printf_s("输入1确定      输入2退出\n");
							scanf_s("%d", &user1);
							if (user1 == 1)
							{
								for (int i = 0; i < 6; i++)//6是密码长度
								{
									student1.password[i] = newuser_password[i];
								}
							}
							if (user1 == 2)
							{
								return 0;
							}
							if (user1 != 1 && user1 != 2)
							{
								printf_s("请输入正确指令");
							}
							break;
						}
						else
						{
							continue;
						}
					}
					if (user == 2)
					{
						break;
					}
					if (user != 1 && user != 2)
					{
						printf_s("请输入正确指令\n");
					}
				}

			}
		}
		else
		{
			printf_s("\n");
			printf_s("输入密码错误\n");
			Sleep(5000);
			return 0;
		}
		if (newuser_password != NULL)
		{
			printf_s("密码修改成功\n");
			printf_s("5s后返回上一级\n");
			int j = 0;
			while (newuser_password != '\0')
			{
				newuser_password[j]--;
				j++;
			}
			altTableData2(uc, newuser_password, 2);
			Sleep(5000);
		}
		
	}
	if (uc == 2 || uc == 4)
	{
		printf_s("登录失败\n");
		return 0;
	}
	if (uc == 3)
	{
		printf_s("很抱歉管理员密码无法更改\n");
		return 0;
	}
	// 释放结果集
	mysql_free_result(res);
	snprintf(sql, 256, "SELECT password FROM students WHERE id = %d;", uc);
	snprintf(sql, 256, "UPDATE ");
	// 关闭数据库
	mysql_close(&mysql);
	return 0;
}


