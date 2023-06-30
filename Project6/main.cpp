#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "clear.h"
#include "change_password.h"
#include "hash.h"
#include "rank.h"
#include "os.h"
#include "main.h"
#include <windows.h>
//19811000 ww 12345 cp8 98 100 99 55

//已知存在的bug
//1.管理员修改时即使id不存在也可以修改的bug
//2.管理员可以删除不存在的id的bug
//4.输入密码时不能使用回退键的bug
//缺陷
//对数据库返回值进行操作会导致内存已占用的bug（该bug可以通过将部分代码转移文档从而规避）
//冗余代码
//os内存在部分没有使用的代码（包括生成链表的代码）

int main1()
{
	s1 student1 = {};                      //暂存输入结构体的变量
	int(*p[])() = { login, };              //一个用于存放登录函数的指针
	int login_over = 0;                    //判断登录状态
	int user_choice = 0;                   //用户选择
	int uc = 0;                            //用户选择
	int uc1 = 0;                           //用户选择
	int ch_age = 0;                        //一个没啥用的变量，在废弃的修改函数中会用到
	int ch_id = 0;						   //保存唯一id
	char ch_name[10] = {};                 //废弃函数中用到的变量
	char ch_name1[15] = { '\0' };          //废弃函数中用到的变量
	char choice[100] = { '\0' };           //废弃函数中用到的变量
	char choice1[50] = { '\0' };		   //用于存放查询内容
	char **m = NULL;                       //废弃的指针
	char *n = NULL;                        //同上
	bool user_next = false;                 //判断第一次登录
	while (true)
	{
		clear();
		printf_s("\t欢迎来到学生管理系统\n");
		printf_s("输入1登录       输入2进入查询系统        输入3退出\n");
		fflush(stdin);
		scanf_s("%d", &user_choice);
		if (user_choice == 1)
		{
			login_over = p[0]();
			if (login_over == 3)
			{
				while (true)
				{
					printf_s("欢迎使用学生管理系统（管理员账号）\n");
					printf_s("输入1添加学生信息     输入2修改学生信息      输入3删除学生信息      输入4查询所有学生信息     输入5退出\n");
					fflush(stdin);
					scanf_s("%d", &uc);
					if (uc == 1)
					{
						clear();
						printf_s("请输入添加学生信息\n");
						fflush(stdin);
						scanf_s("%s %s %s %d %d %d %d", student1.name, 20, student1.password, 20, student1.classes, 10, &student1.en_score, &student1.ch_score,
							&student1.math_score, &student1.age);
						addTableData(student1.name, student1.password, student1.classes, student1.en_score, student1.ch_score,
							student1.math_score, student1.age);
						while (true)
						{
							printf_s("输入1继续      输入2退出\n");
							uc = 0;
							scanf_s("%d", &uc);
							if (uc == 1)
							{
								clear();
								student1 = {};
								printf_s("请输入添加学生信息\n");
								fflush(stdin);
								scanf_s("%s %s %s %d %d %d %d", student1.name, 20, student1.password, 20, student1.classes, 10, &student1.en_score, &student1.ch_score,
									&student1.math_score, &student1.age);
								addTableData(student1.name, student1.password, student1.classes, student1.en_score, student1.ch_score,
									student1.math_score, student1.age);
								Sleep(5000);
								clear();
								continue;
							}
							if (uc == 2)
							{
								clear();
								uc = 0;
								break;
							}
						}
					}
					if (uc == 2)
					{
						while (true)
						{
							printf_s("请输入1单项修改      输入2批量修改      输入3退出\n");
							fflush(stdin);
							scanf_s("%d", &uc1);
							clear();
							if (uc1 == 1)
							{
								student1 = {};
								while (true)
								{
									printf_s("请输入要修改的学号\n");
									fflush(stdin);
									scanf_s("%d", &ch_id);
									uc = 0;
									printf_s("输入1修改姓名   输入2修改密码   输入3修改班级   输入4修改英语成绩   输入5修改语文成绩    输入6修改数学成绩    输入7修改年龄\n");
									fflush(stdin);
									scanf_s("%d", &uc);
									printf_s("请输入要修改的内容\n");
									if (uc == 1)
									{
										fflush(stdin);
										scanf_s("%s",&student1.name,10);
										altTableData2(ch_id, student1.name, uc);
										uc = 0;
										printf_s("输入1继续     输入2退出\n");
										fflush(stdin);
										scanf_s("%d", &uc);
										if (uc == 1)
										{
											clear();
											uc = 0;
											continue;

										}
										if (uc == 2)
										{
											clear();
											uc = 0;
											uc1 = 0;
											break;
										}
									}
									if (uc == 2)
									{
										fflush(stdin);
										scanf_s("%s", &student1.password,20);
										altTableData2(ch_id, student1.password, uc);
										uc = 0;
										printf_s("输入1继续     输入2退出\n");
										fflush(stdin);
										scanf_s("%d", &uc);
										if (uc == 1)
										{
											clear();
											uc = 0;
											continue;

										}
										if (uc == 2)
										{
											clear();
											uc = 0;
											uc1 = 0;
											break;
										}
									}
									if (uc == 3)
									{
										fflush(stdin);
										scanf_s("%s", &student1.classes,10);
										altTableData2(ch_id, student1.classes, uc);
										uc = 0;
										printf_s("输入1继续     输入2退出\n");
										fflush(stdin);
										scanf_s("%d", &uc);
										if (uc == 1)
										{
											clear();
											uc = 0;
											continue;

										}
										if (uc == 2)
										{
											clear();
											uc = 0;
											uc1 = 0;
											break;
										}
									}
									if (uc == 4)
									{
										fflush(stdin);
										scanf_s("%d", &student1.en_score);
										altTableData3(ch_id, student1.en_score, uc);
										uc = 0;
										printf_s("输入1继续     输入2退出\n");
										fflush(stdin);
										scanf_s("%d", &uc);
										if (uc == 1)
										{
											clear();
											uc = 0;
											continue;

										}
										if (uc == 2)
										{
											clear();
											uc = 0;
											uc1 = 0;
											break;
										}
									}
									if (uc == 5)
									{
										fflush(stdin);
										scanf_s("%d", &student1.ch_score);
										altTableData3(ch_id, student1.ch_score, uc);
										uc = 0;
										printf_s("输入1继续     输入2退出\n");
										fflush(stdin);
										scanf_s("%d", &uc);
										if (uc == 1)
										{
											clear();
											uc = 0;
											continue;

										}
										if (uc == 2)
										{
											clear();
											uc = 0;
											uc1 = 0;
											break;
										}
									}
									if (uc == 6)
									{
										fflush(stdin);
										scanf_s("%d", &student1.math_score);
										altTableData3(ch_id, student1.math_score, uc);
										uc = 0;
										printf_s("输入1继续     输入2退出\n");
										fflush(stdin);
										scanf_s("%d", &uc);
										if (uc == 1)
										{
											clear();
											uc = 0;
											continue;

										}
										if (uc == 2)
										{
											clear();
											uc = 0;
											uc1 = 0;
											break;
										}
									}
									if (uc == 7)
									{
										fflush(stdin);
										scanf_s("%d", &student1.age);
										altTableData3(ch_id, student1.age, uc);
										uc = 0;
										printf_s("输入1继续     输入2退出\n");
										fflush(stdin);
										scanf_s("%d", &uc);
										if (uc == 1)
										{
											clear();
											uc = 0;
											continue;

										}
										if (uc == 2)
										{
											clear();
											uc = 0;
											uc1 = 0;
											break;
										}
									}
								}
							}
							if (uc1 == 2)
							{
								student1 = {};
								while (true)
								{
									printf_s("请输入要修改的学号\n");
									fflush(stdin);
									scanf_s("%d", &ch_id);
									uc = 0;
									printf_s("请输入要修改的内容\n");
									fflush(stdin);
									scanf_s("%s %s %s %d %d %d %d", student1.name, 20, student1.password, 20, student1.classes, 10, 
										&student1.en_score, &student1.ch_score, &student1.math_score, &student1.age);
									altTableData1(ch_id, student1.name, student1.password, student1.classes, student1.en_score, 
										student1.ch_score, student1.math_score, student1.age);
									printf_s("输入1继续     输入2退出\n");
									fflush(stdin);
									scanf_s("%d", &uc);
									if (uc == 1)
									{
										clear();
										uc = 0;
										continue;

									}
									if (uc == 2)
									{
										clear();
										uc = 0;
										uc1 = 0;
										break;
									}
								}
							}
							if (uc1 == 3)
							{
								clear();
								uc1 = 0;
								break;
							}
						}
					}
					if (uc == 3)
					{
						while (true)
						{
							uc = 0;
							printf_s("输入1按id删除    输入2批量删除     输入3退出\n");
							fflush(stdin);
							scanf_s("%d", &uc);
							if (uc == 1)
							{
								while (true)
								{
									clear();
									printf_s("请输入要删除的学号\n");
									fflush(stdin);
									scanf_s("%d", &ch_id);
									clear();
									delTableData(ch_id);
									printf_s("5s后可继续操作");
									Sleep(5000);
									clear();
									uc = 0;
									printf_s("输入1继续       输入2退出\n");
									fflush(stdin);
									scanf_s("%d", &uc);
									if (uc == 1)
									{
										uc = 0;
										clear();
										continue;
									}
									if (uc == 2)
									{
										uc = 0;
										clear();
										break;
									}
								}
							}
							if (uc == 2)
							{
								clear();
								int ch_max = 0;
								int ch_min = 0;
								printf_s("请输入删除的范围\n");
								fflush(stdin);
								scanf_s("%d %d", &ch_min, &ch_max);
								printf_s("输入1确定删除   输入2返回\n");
								uc = 0;
								fflush(stdin);
								scanf_s("%d", &uc);
								if (uc == 1)
								{
									clear();
									delTableData1(ch_max, ch_min);
									Sleep(5000);
									clear();
									uc = 0;
									break;
								}
								if (uc == 2)
								{
									uc = 0;
									break;
								}
							}
							if (uc == 3)
							{
								clear();
								uc = 0;
								break;
							}
						}
					}
					if (uc == 4)
					{
						clear();
						uc = 0;
						printf_s("输入1默认顺序查询    输入2按单科成绩查询    输入3按名次查询\n");
						fflush(stdin);
						scanf_s("%d", &uc);
						if (uc == 1)
						{
							queTableData();
						}
						if (uc == 2)
						{
							printf_s("请输入科目\n");
							fflush(stdin);
							scanf_s("%s", choice1, 20);
							queTableData4(choice1);
						}
						if (uc == 3)
						{
							char demo[10] = "rank";
							queTableData3(demo);
						}
						uc = 0;
						printf_s("输入1返回上一级        输入2退出\n");
						fflush(stdin);
						scanf_s("%d", &uc);
						if (uc == 1)
						{
							uc = 0;
							clear();
							continue;
						}
						if (uc == 2)
						{
							uc = 0;
							clear();
							break;
						}
					}
					if (uc == 5)
					{
						clear();
						break;
					}
					if (uc != 0 && uc != 1 && uc != 2 && uc != 3 && uc != 4 && uc != 5)
					{
						while (uc != 1 && uc != 2 && uc != 3 && uc != 4 && uc != 5)
						{
							clear();
							printf_s("请输入正确指令\n");
							fflush(stdin);
							scanf_s("%d", &uc);
						}
					}
				}
			}

			if (login_over != 0 && login_over != 1 && login_over != 2 && login_over != 3)
			{
				while (true)
				{
					if (user_next == false)
					{
						clear();
						queTableData2(login_over);
					}
					if (user_next == true)
					{
						clear();
						printf_s("欢迎使用学生管理系统（学生账号）\n");
					}
					printf_s("输入1查询本人信息          输入2修改密码          输入3退出\n");
					uc = 0;
					fflush(stdin);
					scanf_s("%d", &uc);
					if (uc == 1)
					{
						while (true)
						{
							clear();
							queTableData1(login_over);
							printf_s("\n");
							printf_s("输入1退出\n");
							uc = 0;
							fflush(stdin);
							scanf_s("%d", &uc);
							if (uc == 1)
							{
								user_next = true;
								uc = 0;
								break;
							}
						}
					}
					if (uc == 2)
					{
						clear();
						change_ps(login_over);
						user_next = true;
					}
					if (uc == 3)
					{
						clear();
						uc = 0;
						user_next = true;
						break;
					}
				}

			}
		}
		if (user_choice == 2)
		{
			printf_s("输入查询id\n");
			fflush(stdin);
			scanf_s("%d", &ch_id);
			queTableData1(ch_id);
			printf_s("\n");
			printf_s("5s后返回上一级\n");
			Sleep(5000);
			continue;
		}
		if (user_choice == 3)
		{
			printf_s("感谢您的使用\n");
			break;
		}
	}

	return 0;
}