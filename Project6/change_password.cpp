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

//�ṹ���ض�������
//getpwd ������ʾ����
//�޸�����
bool connectDB1(MYSQL &mysql) {
	// 1.��ʼ�����ݿ���
	mysql_init(&mysql);

	// 2.�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "UTF8");

	// 3.�������ݿ�

	MYSQL *ret = mysql_real_connect(&mysql, "127.0.0.1", "root", "7895123460", "stu_data", 3306, NULL, 0);
	if (ret == NULL) {
		printf("���ݿ�����ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}

	//printf("�������ӳɹ���\n");

	// ѡ�����ݿ�
	int res = mysql_select_db(&mysql, "stu_data");
	if (res) {
		printf("ѡ�����ݿ�ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}

	//printf("���ݿ�ѡ��ɹ���\n");

	return true;
}


int change_ps(int uc)
{
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[256];	// SQL���
	char *p = NULL;
	s1 student1 = {};        //�ݴ�����
	int user = 0;			//����û�����
	int user1 = 0;           //����û�����
	int i = 0;              
	char user_name[20] = { '\0' };         //����û������Ѿ�������  
	char user_password[11] = { '\0' };       //����û����������
	char newuser_password[11] = { '\0' };       //����û������������
	char newuser_password1[11] = { '\0' };		//����ͬ�û������������Ƚ�
	if (!connectDB1(mysql)) {
		return false;
	}

	// C��������ַ���

	snprintf(sql, 256, "SELECT password FROM students WHERE id = %d;", uc);
	//printf_s("��ѯsql��䣺%s\n", sql);

	// ��ѯ����
	//int ret = mysql_query(&mysql, "select * from student;");		// ��Ч������һ�д���
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf_s("ִ�в�ѯ��䣬��ѯ���ؽ����%d\n", ret);

	if (ret) {
		printf("���ݲ�ѯʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}
	//printf_s("���ݲ�ѯ�ɹ���\n");
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	p = row[0];
	if (1)
	{
		printf_s("����������ԭ����\n");
		Getpwd(student1.password);
		if (strcmp(student1.password, p) == 0)
		{
			clear();
			printf_s("����������������\n");
			Getpwd(newuser_password);
			while (true)
			{
				if (strcmp(newuser_password, p) == 0)
				{
					clear();
					printf_s("�¾����벻��һ��,����������\n");//�˳�ʶ���������
					Getpwd(newuser_password);
					printf_s("\n");

				}
				else
				{
					break;
				}
			}

			printf_s("\n");
			printf_s("��ȷ������������\n");
			Getpwd(newuser_password1);
			printf_s("\n");
			if (strcmp(newuser_password, newuser_password1) == 0)
			{
				printf_s("��ȷ���޸�������\n");
				printf_s("����1ȷ��      ����2�˳�\n");
				scanf_s("%d", &user1);
				if (user1 == 1)
				{
					for (int i = 0; i < 6; i++)//6�����볤��
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
					printf_s("��������ȷָ��");
				}
			}
			else
			{
				while (true)
				{
					printf_s("������������벻һ��\n");
					printf_s("����1����ȷ������         ����2�˳������޸�\n");
					scanf_s("%d", &user);
					if (user == 1)
					{
						clear();
						printf_s("��ȷ������������\n");
						Getpwd(newuser_password1);
						printf_s("\n");
						if (strcmp(newuser_password, newuser_password1) == 0)
						{
							printf_s("��ȷ���޸�������\n");
							printf_s("����1ȷ��      ����2�˳�\n");
							scanf_s("%d", &user1);
							if (user1 == 1)
							{
								for (int i = 0; i < 6; i++)//6�����볤��
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
								printf_s("��������ȷָ��");
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
						printf_s("��������ȷָ��\n");
					}
				}

			}
		}
		else
		{
			printf_s("\n");
			printf_s("�����������\n");
			Sleep(5000);
			return 0;
		}
		if (newuser_password != NULL)
		{
			printf_s("�����޸ĳɹ�\n");
			printf_s("5s�󷵻���һ��\n");
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
		printf_s("��¼ʧ��\n");
		return 0;
	}
	if (uc == 3)
	{
		printf_s("�ܱ�Ǹ����Ա�����޷�����\n");
		return 0;
	}
	// �ͷŽ����
	mysql_free_result(res);
	snprintf(sql, 256, "SELECT password FROM students WHERE id = %d;", uc);
	snprintf(sql, 256, "UPDATE ");
	// �ر����ݿ�
	mysql_close(&mysql);
	return 0;
}


