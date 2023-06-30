#include <stdio.h>
#include <mysql.h> // mysql文件
#include "main.h"
#include <string.h>
#define SQL_MAX 256		// sql语句字符数组最大值

// 连接数据库
static bool connectDB(MYSQL &mysql);
// 插入数据
bool addTableData(int id, char *name, int age, char *sex);
// 删除数据
bool delTableData(int id);
// 修改数据
bool altTableData(int id, int age);
// 查询数据
bool queTableData();

typedef struct student2          //初始化链表时用到的
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
 * 功能：连接connect_c_cpp_text数据库，并选择数据库
 *
 * 参数：
 *			mysql - 数据库句柄
 *
 * 返回值：
 *			连接成功返回true，连接失败返回false
 *****************************************************/
bool connectDB(MYSQL &mysql) {
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


/****************************************************
 * 功能：向student表中插入一条记录
 *
 *
 * 返回值：
 *			插入成功返回true，插入失败返回false
 ****************************************************/
bool addTableData(char *name, char *password, char *classes, int en_score, int ch_score, int math_score,  int age ) {
	MYSQL mysql;			// 数据库句柄
	char sql[SQL_MAX];		// 存储sql语句
	char sql1[SQL_MAX];
	char sql2[SQL_MAX];
	int i = 0;
		// 连接数据库

	while (password[i] != '\0')
	{
		password[i]++;
		i++;
	}
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言字符串组合
	int all_sc = 0;
	int rank = 0;
	snprintf(sql, SQL_MAX, "INSERT INTO students(name, password, class, en_score, ch_score, math_score, all_score, age, `rank`) VALUES( '%s', '%s', '%s', %d, %d, %d, %d, %d, %d)",
		name, password, classes, en_score, ch_score, math_score, all_sc, age, rank);
	printf("插入sql语句：%s\n", sql);
		
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("执行插入语句，插入返回结果：%d\n", ret);

	if (ret) {
		printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql1, SQL_MAX, "UPDATE students SET all_score =  en_score + ch_score + math_score  WHERE name = '%s'", name);
	int ret1 = mysql_real_query(&mysql, sql1, (unsigned long)strlen(sql1));
	printf("计算总分，插入返回结果：%d\n", ret1);

	if (ret1) {
		printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}
	
	snprintf(sql2, SQL_MAX,"UPDATE students s JOIN(SELECT id, RANK() OVER(ORDER BY all_score DESC) AS `rank` FROM students) r ON s.id = r.id SET s.`rank` = r.`rank`" );
	int ret2 = mysql_real_query(&mysql, sql2, (unsigned long)strlen(sql2));
	printf("计算排名，插入返回结果：%d\n", ret2);

	if (ret2) {
		printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}
	printf("插入表数据成功！\n");

	// 关闭数据库
	mysql_close(&mysql);

	return true;
}

/*****************************************************
 * 功能：删除student表中id字段等于参数id的记录
 *
 * 参数：
 *			id - 对应表字段id，编号
 *
 * 返回值：
 *			删除成功返回true，删除失败返回false
 *****************************************************/
bool delTableData(int id) {
	MYSQL mysql;			// 数据库句柄
	char sql[SQL_MAX];		// 存储sql语句

		// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言字符串组合
	snprintf(sql, SQL_MAX, "DELETE FROM students WHERE id = %d;", id);
	printf("删除sql语句：%s\n", sql);

	// 执行sql语句，成功返回0
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("执行删除语句，插入返回结果：%d\n", ret);

	if (ret) {
		printf("删除表数据失败！失败原因：%s\n", mysql_error(&mysql));
		return false;

	}
	printf("删除表数据成功！\n");

	// 关闭数据库
	mysql_close(&mysql);

	return true;
}

bool delTableData1(int ch_max, int ch_min) {
	MYSQL mysql;			// 数据库句柄
	char sql[SQL_MAX];		// 存储sql语句

		// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言字符串组合
	snprintf(sql, SQL_MAX, "DELETE FROM students WHERE all_score <= %d && all_score >= %d;", ch_max, ch_min);
	printf("删除sql语句：%s\n", sql);

	// 执行sql语句，成功返回0
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("执行删除语句，插入返回结果：%d\n", ret);

	if (ret) {
		printf("删除表数据失败！失败原因：%s\n", mysql_error(&mysql));
		return false;

	}
	printf("删除表数据成功！\n");

	// 关闭数据库
	mysql_close(&mysql);

	return true;
}

/******************************************************
 * 功能：根据参数id，修改对应表记录的年龄为参数age
 *
 * 参数：
 *			id	- 对应表字段id，编号
 *			age - 对应表字段age，年龄
 *
 * 返回值：
 *			修改成功返回true，修改失败返回false
 *******************************************************/
bool altTableData(int id, int age) {
	MYSQL mysql;		// 数据库句柄
	char sql[SQL_MAX];	// sql语句

	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "UPDATE students SET age = %d WHERE id = %d;", age, id);
	printf("修改sql语句：%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("执行修改语句，修改返回结果：%d\n", ret);

	if (ret) {
		printf("数据修改失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}

	printf("修改表数据成功！\n");

	// 关闭数据库
	mysql_close(&mysql);

	return true;
}


bool altTableData1(int id, char *name, char *password, char *classes, int en_score, int ch_score, int math_score, int age) {
	MYSQL mysql;		// 数据库句柄
	char sql[SQL_MAX];
	char sql1[SQL_MAX];
	char sql2[SQL_MAX];	// sql语句

	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "UPDATE students SET name = '%s', password = '%s', class = '%s', en_score = %d, ch_score = %d, math_score = %d, age = %d WHERE id = %d;",
		name, password, classes, en_score, ch_score, math_score, age, id);
	printf("修改sql语句：%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("执行修改语句，修改返回结果：%d\n", ret);

	if (ret) {
		printf("数据修改失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}

	printf("修改表数据成功！\n");

	// 关闭数据库
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql1, SQL_MAX, "UPDATE students SET all_score =  en_score + ch_score + math_score  WHERE id = '%d'", id);
	int ret1 = mysql_real_query(&mysql, sql1, (unsigned long)strlen(sql1));
	printf("计算总分，插入返回结果：%d\n", ret1);

	if (ret1) {
		printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}
	mysql_close(&mysql);
	if (!connectDB(mysql)) {
		return false;
	}

	snprintf(sql2, SQL_MAX, "UPDATE students s JOIN(SELECT id, RANK() OVER(ORDER BY all_score DESC) AS `rank` FROM students) r ON s.id = r.id SET s.`rank` = r.`rank`");
	int ret2 = mysql_real_query(&mysql, sql2, (unsigned long)strlen(sql2));
	printf("计算排名，插入返回结果：%d\n", ret2);

	if (ret2) {
		printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}
	return true;
}

bool altTableData2(int id, char *input, int choice) {
	MYSQL mysql;		// 数据库句柄
	char sql[SQL_MAX];	// sql语句
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
	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "UPDATE students SET %s = '%s' WHERE id = %d;",cho[choice], input, id);
	//printf("修改sql语句：%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf("执行修改语句，修改返回结果：%d\n", ret);

	if (ret) {
		printf("数据修改失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}

	//printf("修改表数据成功！\n");

	// 关闭数据库
	mysql_close(&mysql);

	return true;
}

bool altTableData3(int id, int input, int choice) {
	MYSQL mysql;		// 数据库句柄
	char sql[SQL_MAX];
	char sql1[SQL_MAX];
	char sql2[SQL_MAX];	// sql语句
	char cho[8][20] = { {}, {"name"},{"password"},{"class"},{"en_score"},{"ch_score"},{"math_score"},{"age"} };
	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "UPDATE students SET %s = '%d' WHERE id = %d;", cho[choice], input, id);
	//printf("修改sql语句：%s\n", sql);

	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf("执行修改语句，修改返回结果：%d\n", ret);

	if (ret) {
		printf("数据修改失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}

	//printf("修改表数据成功！\n");

	// 关闭数据库
	mysql_close(&mysql);
	if (choice != 7)
	{
		if (!connectDB(mysql)) {
			return false;
		}
		snprintf(sql1, SQL_MAX, "UPDATE students SET all_score =  en_score + ch_score + math_score  WHERE id = '%d'", id);
		int ret1 = mysql_real_query(&mysql, sql1, (unsigned long)strlen(sql1));
		printf("计算总分，插入返回结果：%d\n", ret1);

		if (ret1) {
			printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
			return false;
		}
		mysql_close(&mysql);
		if (!connectDB(mysql)) {
			return false;
		}

		snprintf(sql2, SQL_MAX, "UPDATE students s JOIN(SELECT id, RANK() OVER(ORDER BY all_score DESC) AS `rank` FROM students) r ON s.id = r.id SET s.`rank` = r.`rank`");
		int ret2 = mysql_real_query(&mysql, sql2, (unsigned long)strlen(sql2));
		printf("计算排名，插入返回结果：%d\n", ret2);

		if (ret2) {
			printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
			return false;
		}
	}
	return true;
}
/********************************************************
 * 功能：查询student表中所有数据记录，并输出至控制台
 *
 * 参数：
 *			无
 *
 * 返回值：
 *			查询成功返回true，查询失败返回false
 ********************************************************/
bool queTableData() {
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[SQL_MAX];	// SQL语句

	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT id, name, class, en_score, ch_score, math_score, all_score, age, `rank` FROM students;");
	printf("查询sql语句：%s\n", sql);

	// 查询数据
	//int ret = mysql_query(&mysql, "select * from student;");		// 等效于下面一行代码
	//int ret = mysql_query(&mysql, sql);
	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	printf("执行查询语句，查询返回结果：%d\n", ret);

	if (ret) {
		printf("数据查询失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}
	printf("数据查询成功！\n");



	// 获取结果集
	res = mysql_store_result(&mysql);

	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		printf("%d  ", atoi(row[0]));	// 转换为int类型，打印id
		printf("%s  ", row[1]);			// 打印姓名
		printf("%s  ", row[2]);	//打印班级
		printf("%d  ", atoi(row[3])); //打印英语成绩
		printf("%d  ", atoi(row[4]));//打印语文成绩
		printf("%d  ", atoi(row[5]));//打印数学成绩
		printf("%d  ", atoi(row[6]));//打印总成绩
		printf("%d  ", atoi(row[7]));		//打印年龄
		printf("%d  \n", atoi(row[8]));     //打印名次
	}

	// 释放结果集
	mysql_free_result(res);

	// 关闭数据库
	mysql_close(&mysql);

	return true;
}

char *queTableData1(int id) 
{
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[SQL_MAX];	// SQL语句
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}
	
	// C语言组合字符串
	
	snprintf(sql, SQL_MAX, "SELECT id, name, class, en_score, ch_score, math_score, all_score, age ,`rank` FROM students WHERE id = %d;", id);
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
	printf_s("数据查询成功！\n");
	printf_s("学号      姓名 班级 英语成绩 语文成绩 数学成绩 总成绩 年龄 名次\n");


	// 获取结果集
	res = mysql_store_result(&mysql);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		printf("%d  ", atoi(row[0]));	// 转换为int类型，打印id
		printf("%s   ", row[1]);			// 打印姓名
		printf("%s   ", row[2]);	//打印班级
		printf("  %d     ", atoi(row[3])); //打印英语成绩
		printf("  %d     ", atoi(row[4]));//打印语文成绩
		printf("  %d    ", atoi(row[5]));//打印数学成绩
		printf("  %d    ", atoi(row[6]));//打印总成绩
		printf("%d  ", atoi(row[7]));		//打印年龄	
		printf("%d  \n", atoi(row[8]));     //打印名次
		
	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// 释放结果集
	mysql_free_result(res);

	// 关闭数据库
	mysql_close(&mysql);

	return re;
}

bool queTableData2(int id)
{
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[SQL_MAX];	// SQL语句
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串

	snprintf(sql, SQL_MAX, "SELECT name FROM students WHERE id = %d;", id);
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
	//printf_s("学号      姓名 班级 英语成绩 语文成绩 数学成绩 总成绩 年龄 名次\n");


	// 获取结果集
	res = mysql_store_result(&mysql);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		//printf("%d  ", atoi(row[0]));	// 转换为int类型，打印id
		printf("欢迎%s您使用学生管理系统\n", row[0]);			// 打印姓名
		/*printf("%s   ", row[2]);	//打印班级
		printf("  %d     ", atoi(row[3])); //打印英语成绩
		printf("  %d     ", atoi(row[4]));//打印语文成绩
		printf("  %d    ", atoi(row[5]));//打印数学成绩
		printf("  %d    ", atoi(row[6]));//打印总成绩
		printf("%d  ", atoi(row[7]));		//打印年龄	
		printf("%d  \n", atoi(row[8]));     //打印名次*/

	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// 释放结果集
	mysql_free_result(res);

	// 关闭数据库
	mysql_close(&mysql);
	return true;
}


bool queTableData3(char *ch)
{
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[SQL_MAX];	// SQL语句
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	//printf_s("%s", ch);
	
	snprintf(sql, SQL_MAX, "SELECT * FROM students ORDER BY `%s` ASC;", ch);
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
	//printf_s("学号      姓名 班级 英语成绩 语文成绩 数学成绩 总成绩 年龄 名次\n");


	// 获取结果集
	res = mysql_store_result(&mysql);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {
		
		printf("%d  ", atoi(row[0]));	// 转换为int类型，打印id
		printf("%s  ", row[1]);			// 打印姓名
		printf("%s  ", row[3]);	//打印班级
		printf("%d  ", atoi(row[4])); //打印英语成绩
		printf("%d  ", atoi(row[5]));//打印语文成绩
		printf("%d  ", atoi(row[6]));//打印数学成绩
		printf("%d  ", atoi(row[7]));//打印总成绩
		printf("%d  ", atoi(row[8]));		//打印年龄
		printf("%d  \n", atoi(row[9]));     //打印名次
	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// 释放结果集
	mysql_free_result(res);

	// 关闭数据库
	mysql_close(&mysql);
	return true;
}

bool queTableData4(char *ch)
{
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[SQL_MAX];	// SQL语句
	char re[20] = { '\0' };
	int i = 0;
	char *p = NULL;
	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	//printf_s("%s", ch);

	snprintf(sql, SQL_MAX, "SELECT * FROM students ORDER BY %s ASC;", ch);
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
	//printf_s("学号      姓名 班级 英语成绩 语文成绩 数学成绩 总成绩 年龄 名次\n");


	// 获取结果集
	res = mysql_store_result(&mysql);
	// 获取查询到的一行数据
	// 给row赋值，判断row是否为空，不为空就打印数据。
	while (row = mysql_fetch_row(res)) {

		printf("%d  ", atoi(row[0]));	// 转换为int类型，打印id
		printf("%s  ", row[1]);			// 打印姓名
		printf("%s  ", row[3]);	//打印班级
		printf("%d  ", atoi(row[4])); //打印英语成绩
		printf("%d  ", atoi(row[5]));//打印语文成绩
		printf("%d  ", atoi(row[6]));//打印数学成绩
		printf("%d  ", atoi(row[7]));//打印总成绩
		printf("%d  ", atoi(row[8]));		//打印年龄
		printf("%d  \n", atoi(row[9]));     //打印名次
	}
	/*while (row[0][i] != '\0')
	{
		re[i] = row[0][i];
		i++;
	}*/

	// 释放结果集
	mysql_free_result(res);

	// 关闭数据库
	mysql_close(&mysql);
	return true;
}




s3 *queTableData5()
{
	s3 *head = NULL;
	s3 *node = NULL;
	s3 *end = NULL;
	MYSQL mysql;		// 数据库句柄
	MYSQL_RES* res;		// 查询结果集
	MYSQL_ROW row;		// 记录结构体
	char sql[SQL_MAX];	// SQL语句
	head = (s3*)malloc(sizeof(s3));
	end = head;
	// 连接数据库
	if (!connectDB(mysql)) {
		return false;
	}

	// C语言组合字符串
	snprintf(sql, SQL_MAX, "SELECT * FROM students;");

	// 查询数据

	int ret = mysql_real_query(&mysql, sql, (unsigned long)strlen(sql));
	//printf_s("执行查询语句，查询返回结果：%d\n", ret);

	if (ret) {
		printf("数据查询失败！失败原因：%s\n", mysql_error(&mysql));
		return false;
	}


	// 获取结果集
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
	// 释放结果集
	mysql_free_result(res);

	// 关闭数据库
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