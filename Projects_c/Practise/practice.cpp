#include<stdio.h> 


//��һ������������η���ĺ���λ
int Mypow(int x,int y)
{
	int tmp = x;
	for(int i=1;i<y;i++)
	{
		x *= tmp;
	}

	//printf("%d\n",x);
	return x%1000;	
}

//�ж�Īһ��������ĵڼ���
//3�����2��ɹ�������ж���һ���ǡ����㡱���ǡ�ɹ����
int Days(int year,int month,int day)
{
	int an[]={31,28,31,30,31,30,31,31,30,31,30,31};
	int days = 0;
	int i = 0;
	if(year%4==0 && year%100!=0 || year%400==0)
	{
		an[2] = 29;
	}
    for(i=0;i<month;++i)
	{
		days += an[i];
	}
	days += day - an[i-1];

	if(day%5>=1 && day%5<=3)
	{
		printf("����\n");
	}
	else
	{
		printf("ɹ��\n");
	}
	return days;
}
//����abcd=(ab+cd)^2����λ��
int IsContent(int m,int n)
{
	int tmp1;
	int tmp2;
	int tmp3;
	for(int i=m;i<n;++i)
	{
		tmp1 = i%100;
	    tmp2 = i/100;
	    tmp3 = (tmp1+tmp2)*(tmp1+tmp2);
		if(tmp3 == i)
		{
			printf("%d ",i);
		}
	}
	printf("\n");
	return 0;
	
}

//10����ת2����
//�ɷ�ƻ��
/*
void Apple(int total)
{
	int x1;
	int x2 =(x1/8+x2)*6/7;
	int x3 =((x1/8+x2)/7+x3)*5/6;
	int x4 =(((x1/8+x2)/7+x3)/6+x4)*4/5;
	int x5 =((((x1/8+x2)/7+x3)/6+x4)/5+x5)*3/4;
	int x6 =((((((x1/8+x2)/7+x3)/6+x4)/5+x5)/4+x6)*2/3);
	x1 = ((((((x1/8+x2)/7+x3)/6+x4)/5+x5)/4+x6)/3+x1*7/8); 
    while(total == x1+x2+x3+x4+x5+x6)
	{
		printf("%d,%d,%d,%d,%d,%d\n",x1,x2,x3,x4,x5,x6);
	}
}
*/

int main()
{
	printf("%d\n",Days(2011,1,6));
	printf("%d\n",Mypow(8,5));
	IsContent(1000,10000);
	//Apple(2520);
	return 0;
}
