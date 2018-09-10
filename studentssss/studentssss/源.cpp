#include<stdio.h>
#include <string.h>
struct students {
	int num;
	char name[10];
	int sc1;
	int sc2;
	int sc3;
};
int main()
{
	int n, m, s = 0, s1 = 0, s2 = 0, s3 = 0;
	scanf_s("%d", &n);
	students *stu = new students[n];
	for (int i = 0; i < n; i++)
	{
		char sNmae[10];
		scanf_s("%d", &stu[i].num);
		scanf_s("%s\n", sNmae);
		strcpy_s(stu->name, sNmae);
		scanf_s("%d", &stu[i].sc1);
		scanf_s("%d", &stu[i].sc2);
		scanf_s("%d", &stu[i].sc3);
	}
	for (int i = 0; i < n; i++)
	{
		if (s < stu[i].sc1 + stu[i].sc2 + stu[i].sc3)
		{
			s = stu[i].sc1 + stu[i].sc2 + stu[i].sc3;
			m = i;
		}
		s1 += stu[1].sc1;
		s2 += stu[2].sc2;
		s3 += stu[3].sc3;
	}
	printf_s("%d %d %d\n", s1 / n, s2 / n, s3 / n);
	printf_s("%d %s %d %d %d", stu[m].num, stu[m].name, stu[m].sc1, stu[m].sc2, stu[m].sc3);
	return 0;
}