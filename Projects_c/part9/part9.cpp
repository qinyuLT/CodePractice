#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>




//���������սṹ���������ʾ�����Ǹ���ڼ���
typedef struct Date
{
	int year;
	int month;
	int day;
}Date;

bool IsLeapyear(int year)  //�ж��Ƿ�Ϊ����
{
	if(year%4 == 0 && year%100 !=0 ||year%400 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Find_days(Date *date)
{
	int days = 0;
	int i = 0;
	int an[] = {31,28,31,30,31,30,31,31,30,31,30,31};

	if( IsLeapyear(date->year) )
	{
		an[1] = 29;
	}

	for(i=0;i<date->month;++i)
	{
		days += an[i];
	}
	days = days-an[i-1]+date->day;

	return days;
}

int main()
{
	Date date = {2014,8,2};
	printf("2014-8-2 �Ǹ���ĵ� %d ��\n",Find_days(&date));

	return 0;
}


/*
//
typedef struct Student
{
	char num[20];
	char name[20];
	float score[4];    //3�ųɼ�+ƽ���ɼ�
}Student;

void Average(Student *p,int row )//��ÿ��ѧ����ƽ���ɼ�
{
	for(int i=0;i<row;++i)
	{
		p[i].score[3] = (p[i].score[0]+p[i].score[1]+p[i].score[2])/3;
	}
}

void Show(Student *p,int row )
{
	for(int i=0;i<row;++i)
	{
		printf("%s,%s,%.2f,%.2f,%.2f,%.2f\n",p[i].num,p[i].name,
		p[i].score[0],p[i].score[1],p[i].score[2],p[i].score[3]);	
	}
	printf("\n");
}

float Find_max(Student *p,int row)  //����߷�
{
	float max = 0; 
	int m;  //��¼��߷ֵ�ͬѧ
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<4;++j)
		{
			if(max < p[i].score[j])
			{
				max = p[i].score[j];
				m = i;
			}
		}
	}

	printf("%s,%s,%.2f,%.2f,%.2f,%.2f\n",p[m].num,p[m].name,
		 p[m].score[0],p[m].score[1],p[m].score[2],p[m].score[3]);

	return max;
}

int main()
{
	Student std[3] = {{"000001","zhangfei",48,46,55},
	                 {"000002","cao cao ",98,96,95},
	                 {"000003","liu bei" ,89,69,59}};
	Average(std,3);
	Show(std,3);
	Find_max(std,3);

	return 0;
}
*/

/*
//������3�����ߵ�
int *Reject(int n)  //������3�����ߵ�
{
	int *q =(int *)malloc(sizeof(int)*n);
	assert(q != NULL);
	
	int i = 0;
	int m = 0;    //�����޳����˵ĸ���
	int k = 0;
	int num = 0;
	for(i=0;i<n;++i)
	{
		q[i] = i+1;
	}
	while (m < n-1)//���ֻʣһ����
	{
		if (*(q+(i+n)%n) != 0)
		{
			k++;      //��¼����1,2,3	
		}
		if (k ==3)
		{
			*(q+(i+n)%n) = 0;
			k = 0;   //���¼���
			m++;     //����Ϊ0���˵ĸ���
		}
		i++;
	}
	return q;
}
int main()
{
	int n = 10;    //������

	int *an = Reject(n);
	for(int i=0;i<n;++i)
	{
		if(an[i] != 0)
		{
			printf("%d�����ʣ�µ��ǵ� %d ����\n",n,i+1);
		}
	}
	free(an);
	return 0;
}

*/
