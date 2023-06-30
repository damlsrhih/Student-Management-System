#include <stdio.h>
#include <string.h>
//一个废弃的函数用于按名排序
char **name_pm(char *q, char *t)
{
	int i = 0;
	char *m[10] = {  };
	for (i = 0; i < 10; i++)
	{
		if (q[i] < t[i])
		{
			m[0] = q;
			m[1] = t;
			printf_s("%s\n%s", m[0], m[1]);
			return m;
		}
		if (q[i] == t[i])
		{
			continue;

		}
		if (q[i] > t[i])
		{
			m[0] = t;
			m[1] = q;
			printf_s("%s", *m);
			return m;
		}
	}

}