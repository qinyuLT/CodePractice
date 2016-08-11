#include <stdio.h>
#include <math.h>

void SuShu(int n)
{
	int count = 0;
	int k = 0;
	int j = 0;
	printf("0--%d的中素数：\n",n);
	for(int i=2;i<n;i++)
	{
		if(i%2 == 0 || i%3 == 0 || i%5 ==0)
		{
			break;
		}
	}
	printf("\n%d\n",count);
}


void SuShu2(int n)
{
	int count = 0;
	int k = 0;
	int j = 0;
	printf("0--%d的中素数：\n",n);
	for(int i=2;i<n;i++)
	{
		k = (int)sqrt((double)i);
		for(j=2;j<=k;j++)
		{
			if(i%j == 0)
			{
				break;
			}
		}
		if(j > k)
		{
			printf("%d ",i);
			count++;
		}
	}
	printf("\n%d\n",count);
}


void SuShu1(int n)
{
	int count = 0;
	printf("0--%d的中素数：\n",n);
	for(int i=2;i<n;i++)
	{
		for(int j=2;j<i;j++)
		{
			if(i%j == 0)
			{
				break;
			}

			if(j == i-1)
			{
				printf("%d ",i);
				count++;
			}
		}
	}
	printf("\n共计：%d个素数\n",count);
}

int main()
{
	SuShu1(100);
	return 0;
}



#if 0

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

void fun(char a[])
{
	printf("%d\n",sizeof(a));
}

struct sa
{
	unsigned char a:4;
	unsigned char b:2;
	unsigned char c;
	unsigned char d:1;
}*sp;

int main()
{
	//sa *p = (sa *)malloc(sizeof(sa));
	printf("%d\n",sizeof(sa));
	/*
	unsigned char a = 0;
	unsigned char b = 257;
	unsigned char c = 0;

	c = a+b;

	printf("%d,%d\n",a+b,c);

	
	char a[] = "abcd";
	char b[] = {'a','b','c','d'};//无 '\0'，长度随机 
	char c[20];
	for(int i=0;i<6;++i)
	{
		c[i] = '0';
	}
	c[6]  = '\0';
	//fun(a);

	printf("%d\n",strlen(c));
	//printf("%d,%d,%d\n",strlen(a),strlen(b),sizeof(a));
	*/
	return 0;
}

#endif

/*
void main()
{
	int a[10] = {3,5,7,1,4,9,0,61,2,15};
	int max;
	max = a[0];

	for(int i=0;i<10;++i)
	{
		if(max<a[i])
		{
			max=a[i];
		}
	}
	printf("%d\n",max);
}
*/

/*
//5.
void Show()
{
	printf("*************************\n");
	printf("V e r y  g o o d !\n");
	printf("*************************\n");
}
//6.输出三个数中最大的数
int Max(int a,int b,int c)
{
	
	if(a < b)
	{
         a = b;
	}
		
	if(a < c)
	{
		a = c;
	}
		
	return a;
}


int main()
{
	printf("Max=%d\n",Max(140,90,1111));
	Show();

	return 0;
}
*/