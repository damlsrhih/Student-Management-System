#pragma once
// 插入数据
bool addTableData(char *name, char *password, char *classes, int en_score, int ch_score, int math_score, int age);
// 删除数据
bool delTableData(int id);  //删除一条
bool delTableData1(int ch_max, int ch_min); //范围删除
// 修改数据
bool altTableData(int id, int age); //没用的
bool altTableData1(int id, char *name, char *password, char *classes, int en_score, int ch_score, int math_score, int age); //多项修改
bool altTableData2(int id, char *input, int choice); //单项修改（非分数年龄项）
bool altTableData3(int id, int input, int choice);   //单项修改
// 查询数据
bool queTableData();//默认查询
char *queTableData1(int id);     
bool queTableData2(int id);
bool queTableData3(char *ch);    //按rank升序查询
bool queTableData4(char *ch);    //按科目成绩查询
void test();