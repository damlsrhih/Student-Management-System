#include <mysql.h>
#include <stdio.h>

bool connectDB3(MYSQL &mysql) {     
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

	printf("���ݿ�ѡ��ɹ���\n");

	return true;
}

int main()                    //ѧ����¼
{
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��

	if (!connectDB3(mysql)) {
		return false;
	}
}