#pragma once
// ��������
bool addTableData(char *name, char *password, char *classes, int en_score, int ch_score, int math_score, int age);
// ɾ������
bool delTableData(int id);  //ɾ��һ��
bool delTableData1(int ch_max, int ch_min); //��Χɾ��
// �޸�����
bool altTableData(int id, int age); //û�õ�
bool altTableData1(int id, char *name, char *password, char *classes, int en_score, int ch_score, int math_score, int age); //�����޸�
bool altTableData2(int id, char *input, int choice); //�����޸ģ��Ƿ��������
bool altTableData3(int id, int input, int choice);   //�����޸�
// ��ѯ����
bool queTableData();//Ĭ�ϲ�ѯ
char *queTableData1(int id);     
bool queTableData2(int id);
bool queTableData3(char *ch);    //��rank�����ѯ
bool queTableData4(char *ch);    //����Ŀ�ɼ���ѯ
void test();