#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
//�����ڸǺͶ�ȡ������������˼���Ȼ�����bug��
void gotoxy(int x, int y)
{
	//���¹��λ��
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//GetStdHandle��һ��Windows API������
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
}

int posx()
{
	CONSOLE_SCREEN_BUFFER_INFO ptr;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ptr);
	return (ptr.dwCursorPosition.X);
}

int posy()
{
	CONSOLE_SCREEN_BUFFER_INFO ptr;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ptr);
	return (ptr.dwCursorPosition.Y);
}


void Getpwd(char* pwd)
{
	int i = 0;
	int x, y;
	while (1)
	{
		pwd[i] = _getch() + 1;//��ȡ�������루�ַ���
		if (pwd[i] - 1 == VK_BACK  && i >= 0)//���������ǻ��˼���VK_BACK�Ǽ��̵ļ�ֵ��ASCII��ֵΪ8
		{
			if (i > 0)//i>0˵�������붫���ˣ������ǰһ��
			{
				i--;
				x = posx() - 1;//��λx������һ��
				y = posy();//��λy
				gotoxy(x, y);//��λ���
				printf_s("%d %d", x, y);
				printf(" ");//��*�ÿո��ڸ�
				x = posx() - 1;//�ٴλ��ˣ��´�����ʱ���Ż���ʾ����ȷ��λ��
				y = posy();//��λy
				gotoxy(x, y);
				continue;//Ȼ�������˴�ѭ��
			}
			else if (i == 0)//i==0˵��û���붫����ֱ�������˴�ѭ������
			{
				continue;
			}
		}
		if (i >= 0 && pwd[i] - 1 != VK_RETURN && pwd[i] - 1 != VK_BACK)//���붫����
		{
			x = posx();
			y = posy();
			gotoxy(x, y);
			printf("*");
		}
		if (i == 0 && pwd[i] - 1 == VK_RETURN)//���û���붫��ֱ�Ӱ��س���ֱ�������˴�ѭ�����������ѻس���������
		{
			continue;
		}
		if (pwd[i] - 1 == VK_RETURN)//����س��˻��ߵ�������
		{
			pwd[i]  = '\0';
			i++;
			break;
		}

		i++;
	}
}