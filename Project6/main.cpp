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

//��֪���ڵ�bug
//1.����Ա�޸�ʱ��ʹid������Ҳ�����޸ĵ�bug
//2.����Ա����ɾ�������ڵ�id��bug
//4.��������ʱ����ʹ�û��˼���bug
//ȱ��
//�����ݿⷵ��ֵ���в����ᵼ���ڴ���ռ�õ�bug����bug����ͨ�������ִ���ת���ĵ��Ӷ���ܣ�
//�������
//os�ڴ��ڲ���û��ʹ�õĴ��루������������Ĵ��룩

int main1()
{
	s1 student1 = {};                      //�ݴ�����ṹ��ı���
	int(*p[])() = { login, };              //һ�����ڴ�ŵ�¼������ָ��
	int login_over = 0;                    //�жϵ�¼״̬
	int user_choice = 0;                   //�û�ѡ��
	int uc = 0;                            //�û�ѡ��
	int uc1 = 0;                           //�û�ѡ��
	int ch_age = 0;                        //һ��ûɶ�õı������ڷ������޸ĺ����л��õ�
	int ch_id = 0;						   //����Ψһid
	char ch_name[10] = {};                 //�����������õ��ı���
	char ch_name1[15] = { '\0' };          //�����������õ��ı���
	char choice[100] = { '\0' };           //�����������õ��ı���
	char choice1[50] = { '\0' };		   //���ڴ�Ų�ѯ����
	char **m = NULL;                       //������ָ��
	char *n = NULL;                        //ͬ��
	bool user_next = false;                 //�жϵ�һ�ε�¼
	while (true)
	{
		clear();
		printf_s("\t��ӭ����ѧ������ϵͳ\n");
		printf_s("����1��¼       ����2�����ѯϵͳ        ����3�˳�\n");
		fflush(stdin);
		scanf_s("%d", &user_choice);
		if (user_choice == 1)
		{
			login_over = p[0]();
			if (login_over == 3)
			{
				while (true)
				{
					printf_s("��ӭʹ��ѧ������ϵͳ������Ա�˺ţ�\n");
					printf_s("����1���ѧ����Ϣ     ����2�޸�ѧ����Ϣ      ����3ɾ��ѧ����Ϣ      ����4��ѯ����ѧ����Ϣ     ����5�˳�\n");
					fflush(stdin);
					scanf_s("%d", &uc);
					if (uc == 1)
					{
						clear();
						printf_s("���������ѧ����Ϣ\n");
						fflush(stdin);
						scanf_s("%s %s %s %d %d %d %d", student1.name, 20, student1.password, 20, student1.classes, 10, &student1.en_score, &student1.ch_score,
							&student1.math_score, &student1.age);
						addTableData(student1.name, student1.password, student1.classes, student1.en_score, student1.ch_score,
							student1.math_score, student1.age);
						while (true)
						{
							printf_s("����1����      ����2�˳�\n");
							uc = 0;
							scanf_s("%d", &uc);
							if (uc == 1)
							{
								clear();
								student1 = {};
								printf_s("���������ѧ����Ϣ\n");
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
							printf_s("������1�����޸�      ����2�����޸�      ����3�˳�\n");
							fflush(stdin);
							scanf_s("%d", &uc1);
							clear();
							if (uc1 == 1)
							{
								student1 = {};
								while (true)
								{
									printf_s("������Ҫ�޸ĵ�ѧ��\n");
									fflush(stdin);
									scanf_s("%d", &ch_id);
									uc = 0;
									printf_s("����1�޸�����   ����2�޸�����   ����3�޸İ༶   ����4�޸�Ӣ��ɼ�   ����5�޸����ĳɼ�    ����6�޸���ѧ�ɼ�    ����7�޸�����\n");
									fflush(stdin);
									scanf_s("%d", &uc);
									printf_s("������Ҫ�޸ĵ�����\n");
									if (uc == 1)
									{
										fflush(stdin);
										scanf_s("%s",&student1.name,10);
										altTableData2(ch_id, student1.name, uc);
										uc = 0;
										printf_s("����1����     ����2�˳�\n");
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
										printf_s("����1����     ����2�˳�\n");
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
										printf_s("����1����     ����2�˳�\n");
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
										printf_s("����1����     ����2�˳�\n");
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
										printf_s("����1����     ����2�˳�\n");
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
										printf_s("����1����     ����2�˳�\n");
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
										printf_s("����1����     ����2�˳�\n");
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
									printf_s("������Ҫ�޸ĵ�ѧ��\n");
									fflush(stdin);
									scanf_s("%d", &ch_id);
									uc = 0;
									printf_s("������Ҫ�޸ĵ�����\n");
									fflush(stdin);
									scanf_s("%s %s %s %d %d %d %d", student1.name, 20, student1.password, 20, student1.classes, 10, 
										&student1.en_score, &student1.ch_score, &student1.math_score, &student1.age);
									altTableData1(ch_id, student1.name, student1.password, student1.classes, student1.en_score, 
										student1.ch_score, student1.math_score, student1.age);
									printf_s("����1����     ����2�˳�\n");
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
							printf_s("����1��idɾ��    ����2����ɾ��     ����3�˳�\n");
							fflush(stdin);
							scanf_s("%d", &uc);
							if (uc == 1)
							{
								while (true)
								{
									clear();
									printf_s("������Ҫɾ����ѧ��\n");
									fflush(stdin);
									scanf_s("%d", &ch_id);
									clear();
									delTableData(ch_id);
									printf_s("5s��ɼ�������");
									Sleep(5000);
									clear();
									uc = 0;
									printf_s("����1����       ����2�˳�\n");
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
								printf_s("������ɾ���ķ�Χ\n");
								fflush(stdin);
								scanf_s("%d %d", &ch_min, &ch_max);
								printf_s("����1ȷ��ɾ��   ����2����\n");
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
						printf_s("����1Ĭ��˳���ѯ    ����2�����Ƴɼ���ѯ    ����3�����β�ѯ\n");
						fflush(stdin);
						scanf_s("%d", &uc);
						if (uc == 1)
						{
							queTableData();
						}
						if (uc == 2)
						{
							printf_s("�������Ŀ\n");
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
						printf_s("����1������һ��        ����2�˳�\n");
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
							printf_s("��������ȷָ��\n");
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
						printf_s("��ӭʹ��ѧ������ϵͳ��ѧ���˺ţ�\n");
					}
					printf_s("����1��ѯ������Ϣ          ����2�޸�����          ����3�˳�\n");
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
							printf_s("����1�˳�\n");
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
			printf_s("�����ѯid\n");
			fflush(stdin);
			scanf_s("%d", &ch_id);
			queTableData1(ch_id);
			printf_s("\n");
			printf_s("5s�󷵻���һ��\n");
			Sleep(5000);
			continue;
		}
		if (user_choice == 3)
		{
			printf_s("��л����ʹ��\n");
			break;
		}
	}

	return 0;
}