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

gl guanli = {"admin","benjo"};        //����Ա��Ϣ
char random[6] = { '\0' };            //������֤�루��֤��������ִ�СдӢ�ģ�


bool connectDB2(MYSQL &mysql) {        //��ֹ�ڴ�ռ��bug��Ȩ��֮��
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



char *randint()            //������֤��
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

int stu_login()                    //ѧ����¼
{
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[256];	// SQL���
	char *p1 = NULL;       //�������
	int user_id1 = 0;      //���id
	char user_password[11] = { '\0' };    //���������
	char user_epassword[6] = { '\0' };    //�������֤��
	int i = 0;
	printf_s("�����������û���:\n");
	fflush(stdin);
	scanf_s("%d", &user_id1);
	if (!connectDB2(mysql)) {
		return false;
	}

	// C��������ַ���

	snprintf(sql, 256, "SELECT password FROM students WHERE id = %d;", user_id1);
	//printf_s("��ѯsql��䣺%s\n", sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf_s("ִ�в�ѯ��䣬��ѯ���ؽ����%d\n", ret);

	if (ret) {
		printf("���ݲ�ѯʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}

	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	p1 = row[0];
	printf_s("��������������:\n");
	Getpwd(user_password);
	printf_s("%s\n", user_password);
	printf_s("��������֤��:\n");
	printf_s("��ע����֤�����ִ�Сд!\n");
	char *p = randint();
	fflush(stdin);
	scanf_s("%s", user_epassword, 6);
	clear();
	//scanf_s ����buf��ֵӦ�ô�����������ַ����ĳ��ȷ���д��ʧ��
	if (!ret)
	{
		if (strcmp(user_password, p1) == 0)
		{
			if (strcmp(user_epassword, p) == 0)//epassword ��֤��
			{
				printf_s("��¼�ɹ�\n");
				return user_id1;
			}
			else
			{
				printf_s("��¼ʧ��:��֤�����\n");
				return 2;
			}
		}
		else
		{
			printf_s("��¼ʧ��:�û������������\n");
			return 0;
		}
	}
	else
	{
		printf_s("��¼ʧ��:�û������������\n");
		return 0;
	}

}

int gl_login()          //�����¼
{
	char user_name[11] = { '\0' };    //�����û���
	char user_password[11] = { '\0' };  //��������
	printf_s("�����������û���\n");
	fflush(stdin);
	scanf_s("%s", user_name, 10);
	printf_s("��������������\n");
	Getpwd(user_password);
	clear();
	if (strcmp(user_name, guanli.name) == 0)
	{
		if (strcmp(user_password, guanli.password) == 0)
		{
			printf_s("��¼�ɹ�\n");
			return 1;
		}
		else
		{
			printf_s("��¼ʧ��:�û������������\n");
			return 0;
		}
	}
	else
	{
		printf_s("��¼ʧ��:�û������������\n");
		return 0;
	}
}
/*int con_log()
{

	ʵ���滻forѭ���ڵĶ���

}*/
int login()           //��¼����
{
	int user = 0;
	int login_over = 0; //�жϵ�¼״̬ 0�û���������� 1��¼�ɹ� 2��֤�����
	int yz = 0;     //�ж����µ�¼�����˳� 1���µ�¼ 2�˳�
	int i = 0;
	int out = 0;  //���ص�¼״̬
	printf_s("�������������\n");
	printf_s("\t����1Ϊѧ��");
	printf_s("\t����2Ϊ����Ա\n");
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
				printf_s("���������û���������\n");
				printf_s("\t����1���µ�¼     ����2�˳�\n");
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
					printf_s("��ӭ���´�ʹ��\n");
					return out = login_over;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("��������ȷָ��\n");
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
				printf_s("\t����1���µ�¼     ����2�˳�\n");
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
					printf_s("��ӭ���´�ʹ��\n");
					return out = 2;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("��������ȷָ��\n");
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
				printf_s("���������û���������\n");
				printf_s("\t����1���µ�¼     ����2�˳�\n");
				fflush(stdin);
				scanf_s("%d", &yz);
				if (yz == 1)
				{
					clear();
					continue;
				}
				if (yz == 2)
				{
					printf_s("��ӭ���´�ʹ��\n");
					return out = 3;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("��������ȷָ��\n");
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
				printf_s("\t����1���µ�¼     ����2�˳�\n");
				fflush(stdin);
				scanf_s("%d", &yz);
				if (yz == 1)
				{
					clear();
					continue;
				}
				if (yz == 2)
				{
					printf_s("��ӭ���´�ʹ��\n");
					return out = 4;
				}
				if (yz != 1 && yz != 2)
				{
					while (true)
					{
						printf_s("��������ȷָ��\n");
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