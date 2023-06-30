#include <stdio.h>
#include <mysql.h> // mysql�ļ�
#include "main.h"
#include <string.h>
#define SQL_MAX 256		// sql����ַ��������ֵ

// �������ݿ�
static bool connectDB(MYSQL &mysql);
// ��������
bool addTableData(int id, char *name, int age, char *sex);
// ɾ������
bool delTableData(int id);
// �޸�����
bool altTableData(int id, int age);
// ��ѯ����
bool queTableData();

typedef struct student2          //��ʼ������ʱ�õ���
{
	int ID;
	char name[6];
	char classes[10];
	int en_score;
	int ch_score;
	int math_score;
	int all_score;
	int age;
	int mingci;
	struct student2 *p;
}s3;
/*****************************************************
 * ���ܣ�����connect_c_cpp_text���ݿ⣬��ѡ�����ݿ�
 *
 * ������
 *			mysql - ���ݿ���
 *
 * ����ֵ��
 *			���ӳɹ�����true������ʧ�ܷ���false
 *****************************************************/
bool connectDB(MYSQL &mysql) {
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


/****************************************************
 * ���ܣ���student���в���һ����¼
 *
 *
 * ����ֵ��
 *			����ɹ�����true������ʧ�ܷ���false
 ****************************************************/
bool addTableData(char *name, char *password, char *classes, int en_score, int ch_score, int math_score,  int age ) {
	MYSQL mysql;			// ���ݿ���
	char sql[SQL_MAX];		// �洢sql���
	char sql1[SQL_MAX];
	char sql2[SQL_MAX];
	int i = 0;
		// �������ݿ�

	while (password[i] != '\0')
	{
		password[i]++;
		i++;
	}
	if (!connectDB(mysql)) {
		return false;
	}

	// C�����ַ������
	int all_sc = 0;
	int rank = 0;
	snprintf(sql, SQL_MAX, "INSERT INTO students(name, password, class, en_score, ch_score, math_score, all_score, age, `rank`) VALUES( '%s', '%s', '%s', %d, %d, %d, %d, %d, %d)",
		name, password, classes, en_score, ch_score, math_score, all_sc, age, rank);
	printf("����sql��䣺%s\n", sql);
		
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("ִ�в�����䣬���뷵�ؽ����%d\n", ret);

	if (ret) {
		printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql1, SQL_MAX, "UPDATE students SET all_score =  en_score + ch_score + math_score  WHERE name = '%s'", name);
	int ret1 = mysql_real_query(&mysql, sql1, (unsigned long)strlen(sql1));
	printf("�����ܷ֣����뷵�ؽ����%d\n", ret1);

	if (ret1) {
		printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}
	
	snprintf(sql2, SQL_MAX,"UPDATE students s JOIN(SELECT id, RANK() OVER(ORDER BY all_score DESC) AS `rank` FROM students) r ON s.id = r.id SET s.`rank` = r.`rank`" );
	int ret2 = mysql_real_query(&mysql, sql2, (unsigned long)strlen(sql2));
	printf("�������������뷵�ؽ����%d\n", ret2);

	if (ret2) {
		printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}
	printf("��������ݳɹ���\n");

	// �ر����ݿ�
	mysql_close(&mysql);

	return true;
}

/*****************************************************
 * ���ܣ�ɾ��student����id�ֶε��ڲ���id�ļ�¼
 *
 * ������
 *			id - ��Ӧ���ֶ�id�����
 *
 * ����ֵ��
 *			ɾ���ɹ�����true��ɾ��ʧ�ܷ���false
 *****************************************************/
bool delTableData(int id) {
	MYSQL mysql;			// ���ݿ���
	char sql[SQL_MAX];		// �洢sql���

		// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C�����ַ������
	snprintf(sql, SQL_MAX, "DELETE FROM students WHERE id = %d;", id);
	printf("ɾ��sql��䣺%s\n", sql);

	// ִ��sql��䣬�ɹ�����0
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("ִ��ɾ����䣬���뷵�ؽ����%d\n", ret);

	if (ret) {
		printf("ɾ��������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;

	}
	printf("ɾ�������ݳɹ���\n");

	// �ر����ݿ�
	mysql_close(&mysql);

	return true;
}

bool delTableData1(int ch_max, int ch_min) {
	MYSQL mysql;			// ���ݿ���
	char sql[SQL_MAX];		// �洢sql���

		// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C�����ַ������
	snprintf(sql, SQL_MAX, "DELETE FROM students WHERE all_score <= %d && all_score >= %d;", ch_max, ch_min);
	printf("ɾ��sql��䣺%s\n", sql);

	// ִ��sql��䣬�ɹ�����0
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("ִ��ɾ����䣬���뷵�ؽ����%d\n", ret);

	if (ret) {
		printf("ɾ��������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;

	}
	printf("ɾ�������ݳɹ���\n");

	// �ر����ݿ�
	mysql_close(&mysql);

	return true;
}

/******************************************************
 * ���ܣ����ݲ���id���޸Ķ�Ӧ���¼������Ϊ����age
 *
 * ������
 *			id	- ��Ӧ���ֶ�id�����
 *			age - ��Ӧ���ֶ�age������
 *
 * ����ֵ��
 *			�޸ĳɹ�����true���޸�ʧ�ܷ���false
 *******************************************************/
bool altTableData(int id, int age) {
	MYSQL mysql;		// ���ݿ���
	char sql[SQL_MAX];	// sql���

	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	snprintf(sql, SQL_MAX, "UPDATE students SET age = %d WHERE id = %d;", age, id);
	printf("�޸�sql��䣺%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("ִ���޸���䣬�޸ķ��ؽ����%d\n", ret);

	if (ret) {
		printf("�����޸�ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}

	printf("�޸ı����ݳɹ���\n");

	// �ر����ݿ�
	mysql_close(&mysql);

	return true;
}


bool altTableData1(int id, char *name, char *password, char *classes, int en_score, int ch_score, int math_score, int age) {
	MYSQL mysql;		// ���ݿ���
	char sql[SQL_MAX];
	char sql1[SQL_MAX];
	char sql2[SQL_MAX];	// sql���

	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	snprintf(sql, SQL_MAX, "UPDATE students SET name = '%s', password = '%s', class = '%s', en_score = %d, ch_score = %d, math_score = %d, age = %d WHERE id = %d;",
		name, password, classes, en_score, ch_score, math_score, age, id);
	printf("�޸�sql��䣺%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("ִ���޸���䣬�޸ķ��ؽ����%d\n", ret);

	if (ret) {
		printf("�����޸�ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}

	printf("�޸ı����ݳɹ���\n");

	// �ر����ݿ�
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql1, SQL_MAX, "UPDATE students SET all_score =  en_score + ch_score + math_score  WHERE id = '%d'", id);
	int ret1 = mysql_real_query(&mysql, sql1, (unsigned long)strlen(sql1));
	printf("�����ܷ֣����뷵�ؽ����%d\n", ret1);

	if (ret1) {
		printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}

	snprintf(sql2, SQL_MAX, "UPDATE students s JOIN(SELECT id, RANK() OVER(ORDER BY all_score DESC) AS `rank` FROM students) r ON s.id = r.id SET s.`rank` = r.`rank`");
	int ret2 = mysql_real_query(&mysql, sql2, (unsigned long)strlen(sql2));
	printf("�������������뷵�ؽ����%d\n", ret2);

	if (ret2) {
		printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}
	return true;
}

bool altTableData2(int id, char *input, int choice) {
	MYSQL mysql;		// ���ݿ���
	char sql[SQL_MAX];	// sql���
	int i = 0;
	char cho[8][20] = { {}, {"name"},{"password"},{"class"},{"en_score"},{"ch_score"},{"math_score"},{"age"} };
	if (choice == 2)
	{
		while (input[i] != '\0')
		{
			input[i]++;
			i++;
		}
	}
	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	snprintf(sql, SQL_MAX, "UPDATE students SET %s = '%s' WHERE id = %d;",cho[choice], input, id);
	//printf("�޸�sql��䣺%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf("ִ���޸���䣬�޸ķ��ؽ����%d\n", ret);

	if (ret) {
		printf("�����޸�ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}

	//printf("�޸ı����ݳɹ���\n");

	// �ر����ݿ�
	mysql_close(&mysql);

	return true;
}

bool altTableData3(int id, int input, int choice) {
	MYSQL mysql;		// ���ݿ���
	char sql[SQL_MAX];
	char sql1[SQL_MAX];
	char sql2[SQL_MAX];	// sql���
	char cho[8][20] = { {}, {"name"},{"password"},{"class"},{"en_score"},{"ch_score"},{"math_score"},{"age"} };
	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	snprintf(sql, SQL_MAX, "UPDATE students SET %s = '%d' WHERE id = %d;", cho[choice], input, id);
	//printf("�޸�sql��䣺%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf("ִ���޸���䣬�޸ķ��ؽ����%d\n", ret);

	if (ret) {
		printf("�����޸�ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}

	//printf("�޸ı����ݳɹ���\n");

	// �ر����ݿ�
	mysql_close(&mysql);
	if (choice != 7)
	{
		if (!connectDB(mysql)) {
			return false;
		}
		snprintf(sql1, SQL_MAX, "UPDATE students SET all_score =  en_score + ch_score + math_score  WHERE id = '%d'", id);
		int ret1 = mysql_real_query(&mysql, sql1, (unsigned long)strlen(sql1));
		printf("�����ܷ֣����뷵�ؽ����%d\n", ret1);

		if (ret1) {
			printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
			return false;
		}
		mysql_close(&mysql);
		if (!connectDB(mysql)) {
			return false;
		}

		snprintf(sql2, SQL_MAX, "UPDATE students s JOIN(SELECT id, RANK() OVER(ORDER BY all_score DESC) AS `rank` FROM students) r ON s.id = r.id SET s.`rank` = r.`rank`");
		int ret2 = mysql_real_query(&mysql, sql2, (unsigned long)strlen(sql2));
		printf("�������������뷵�ؽ����%d\n", ret2);

		if (ret2) {
			printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
			return false;
		}
	}
	return true;
}
/********************************************************
 * ���ܣ���ѯstudent�����������ݼ�¼�������������̨
 *
 * ������
 *			��
 *
 * ����ֵ��
 *			��ѯ�ɹ�����true����ѯʧ�ܷ���false
 ********************************************************/
bool queTableData() {
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[SQL_MAX];	// SQL���

	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	snprintf(sql, SQL_MAX, "SELECT id, name, class, en_score, ch_score, math_score, all_score, age, `rank` FROM students;");
	printf("��ѯsql��䣺%s\n", sql);

	// ��ѯ����
	//int ret = mysql_query(&mysql, "select * from student;");		// ��Ч������һ�д���
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("ִ�в�ѯ��䣬��ѯ���ؽ����%d\n", ret);

	if (ret) {
		printf("���ݲ�ѯʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}
	printf("���ݲ�ѯ�ɹ���\n");



	// ��ȡ�����
	res = mysql_store_result(&mysql);

	// ��ȡ��ѯ����һ������
	// ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res)) {
		printf("%d  ", atoi(row[0]));	// ת��Ϊint���ͣ���ӡid
		printf("%s  ", row[1]);			// ��ӡ����
		printf("%s  ", row[2]);	//��ӡ�༶
		printf("%d  ", atoi(row[3])); //��ӡӢ��ɼ�
		printf("%d  ", atoi(row[4]));//��ӡ���ĳɼ�
		printf("%d  ", atoi(row[5]));//��ӡ��ѧ�ɼ�
		printf("%d  ", atoi(row[6]));//��ӡ�ܳɼ�
		printf("%d  ", atoi(row[7]));		//��ӡ����
		printf("%d  \n", atoi(row[8]));     //��ӡ����
	}

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�
	mysql_close(&mysql);

	return true;
}

char *queTableData1(int id) 
{
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[SQL_MAX];	// SQL���
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}
	
	// C��������ַ���
	
	snprintf(sql, SQL_MAX, "SELECT id, name, class, en_score, ch_score, math_score, all_score, age ,`rank` FROM students WHERE id = %d;", id);
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
	printf_s("���ݲ�ѯ�ɹ���\n");
	printf_s("ѧ��      ���� �༶ Ӣ��ɼ� ���ĳɼ� ��ѧ�ɼ� �ܳɼ� ���� ����\n");


	// ��ȡ�����
	res = mysql_store_result(&mysql);
	// ��ȡ��ѯ����һ������
	// ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res)) {
		printf("%d  ", atoi(row[0]));	// ת��Ϊint���ͣ���ӡid
		printf("%s   ", row[1]);			// ��ӡ����
		printf("%s   ", row[2]);	//��ӡ�༶
		printf("  %d     ", atoi(row[3])); //��ӡӢ��ɼ�
		printf("  %d     ", atoi(row[4]));//��ӡ���ĳɼ�
		printf("  %d    ", atoi(row[5]));//��ӡ��ѧ�ɼ�
		printf("  %d    ", atoi(row[6]));//��ӡ�ܳɼ�
		printf("%d  ", atoi(row[7]));		//��ӡ����	
		printf("%d  \n", atoi(row[8]));     //��ӡ����
		
	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�
	mysql_close(&mysql);

	return re;
}

bool queTableData2(int id)
{
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[SQL_MAX];	// SQL���
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���

	snprintf(sql, SQL_MAX, "SELECT name FROM students WHERE id = %d;", id);
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
	//printf_s("ѧ��      ���� �༶ Ӣ��ɼ� ���ĳɼ� ��ѧ�ɼ� �ܳɼ� ���� ����\n");


	// ��ȡ�����
	res = mysql_store_result(&mysql);
	// ��ȡ��ѯ����һ������
	// ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res)) {
		//printf("%d  ", atoi(row[0]));	// ת��Ϊint���ͣ���ӡid
		printf("��ӭ%s��ʹ��ѧ������ϵͳ\n", row[0]);			// ��ӡ����
		/*printf("%s   ", row[2]);	//��ӡ�༶
		printf("  %d     ", atoi(row[3])); //��ӡӢ��ɼ�
		printf("  %d     ", atoi(row[4]));//��ӡ���ĳɼ�
		printf("  %d    ", atoi(row[5]));//��ӡ��ѧ�ɼ�
		printf("  %d    ", atoi(row[6]));//��ӡ�ܳɼ�
		printf("%d  ", atoi(row[7]));		//��ӡ����	
		printf("%d  \n", atoi(row[8]));     //��ӡ����*/

	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�
	mysql_close(&mysql);
	return true;
}


bool queTableData3(char *ch)
{
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[SQL_MAX];	// SQL���
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	//printf_s("%s", ch);
	
	snprintf(sql, SQL_MAX, "SELECT * FROM students ORDER BY `%s` ASC;", ch);
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
	//printf_s("ѧ��      ���� �༶ Ӣ��ɼ� ���ĳɼ� ��ѧ�ɼ� �ܳɼ� ���� ����\n");


	// ��ȡ�����
	res = mysql_store_result(&mysql);
	// ��ȡ��ѯ����һ������
	// ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res)) {
		
		printf("%d  ", atoi(row[0]));	// ת��Ϊint���ͣ���ӡid
		printf("%s  ", row[1]);			// ��ӡ����
		printf("%s  ", row[3]);	//��ӡ�༶
		printf("%d  ", atoi(row[4])); //��ӡӢ��ɼ�
		printf("%d  ", atoi(row[5]));//��ӡ���ĳɼ�
		printf("%d  ", atoi(row[6]));//��ӡ��ѧ�ɼ�
		printf("%d  ", atoi(row[7]));//��ӡ�ܳɼ�
		printf("%d  ", atoi(row[8]));		//��ӡ����
		printf("%d  \n", atoi(row[9]));     //��ӡ����
	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�
	mysql_close(&mysql);
	return true;
}

bool queTableData4(char *ch)
{
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[SQL_MAX];	// SQL���
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	//printf_s("%s", ch);

	snprintf(sql, SQL_MAX, "SELECT * FROM students ORDER BY %s ASC;", ch);
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
	//printf_s("ѧ��      ���� �༶ Ӣ��ɼ� ���ĳɼ� ��ѧ�ɼ� �ܳɼ� ���� ����\n");


	// ��ȡ�����
	res = mysql_store_result(&mysql);
	// ��ȡ��ѯ����һ������
	// ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res)) {

		printf("%d  ", atoi(row[0]));	// ת��Ϊint���ͣ���ӡid
		printf("%s  ", row[1]);			// ��ӡ����
		printf("%s  ", row[3]);	//��ӡ�༶
		printf("%d  ", atoi(row[4])); //��ӡӢ��ɼ�
		printf("%d  ", atoi(row[5]));//��ӡ���ĳɼ�
		printf("%d  ", atoi(row[6]));//��ӡ��ѧ�ɼ�
		printf("%d  ", atoi(row[7]));//��ӡ�ܳɼ�
		printf("%d  ", atoi(row[8]));		//��ӡ����
		printf("%d  \n", atoi(row[9]));     //��ӡ����
	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�
	mysql_close(&mysql);
	return true;
}




s3 *queTableData5()
{
	s3 *head = NULL;
	s3 *node = NULL;
	s3 *end = NULL;
	MYSQL mysql;		// ���ݿ���
	MYSQL_RES* res;		// ��ѯ�����
	MYSQL_ROW row;		// ��¼�ṹ��
	char sql[SQL_MAX];	// SQL���
	head = (s3*)malloc(sizeof(s3));
	end = head;
	// �������ݿ�
	if (!connectDB(mysql)) {
		return false;
	}

	// C��������ַ���
	snprintf(sql, SQL_MAX, "SELECT * FROM students;");

	// ��ѯ����

	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf_s("ִ�в�ѯ��䣬��ѯ���ؽ����%d\n", ret);

	if (ret) {
		printf("���ݲ�ѯʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
		return false;
	}


	// ��ȡ�����
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res)) {
		node = (s3*)malloc(sizeof(s3));
		node->age = atoi(row[8]);
		strcpy_s(node->name,20, row[1]);
		strcpy_s(node->classes,20, row[3]);
		node->ch_score = atoi(row[5]);
		node->en_score = atoi(row[4]);
		node->math_score = atoi(row[6]);
		node->all_score = atoi(row[7]);
		node->mingci = atoi(row[9]);
		end->p = node;
		end = node;
	}
	end->p = NULL;
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/
	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�
	mysql_close(&mysql);
	return head;
}


void test()
{
	s3 *p = NULL;
	p = queTableData5();
	printf_s("%d", *p);
	free(p);
}