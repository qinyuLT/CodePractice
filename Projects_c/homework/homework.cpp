#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
void Rever(long long int m)
{
	long long int n = m;
	long long int rever_m = 0; //�������m����
	int tmp = 0;
	int i = 0;

	while(n!=0)
	{
		tmp = n%10;
		rever_m = tmp + rever_m*10;
		n /= 10;
	}

	if(rever_m == m)  //�ж�m��������m�Ƿ����
	{
		printf("%I64d\n", m);
	}
}

int main()
{
	long long int i,j;
	int n = 0;
	int tmp = 0;
	scanf("%d",&n);

	for(i=899997;i<1000000;++i)
	{
		j = i;
		tmp = 0;
		while(j != 0)
		{
			tmp = tmp + j%10;
			j = j/10;
		}
		if (tmp == n )
		{
			Rever(i);
		}
	}
	return 0;
}
*/

# if 0
//0x87654321 -> 0x00000021
int First(int a,int figure)
{
	return (a<<(figure-8))>>(figure-8);
}
//0x87654321 -> 0x789ABC21
int Second(int a,int figure)
{
	int b = (First(a,figure));

	return (((~a)>>8)<<8)|b ;
}
//0x87654321 -> 0x876543ff
int Third(int a,int figure)
{
	return (~((~0)<<8))|((a>>8)<<8);
}
int main()
{
	
	int a = 0x87654321;

	printf("%08x\n",First(a,32));
	printf("%08x\n",Second(a,32));
	printf("%08x\n",Third(a,32));
	/*
	int a = 0x876543;

	printf("%06x\n",First(a,32));
	printf("%06x\n",Second(a,32));
	printf("%06x\n",Third(a,32));
	*/
	return 0;
}
#endif

/*
//��λ������߼������ж�����ֵ�Ƿ����
int IsEqual(int a,int b)
{
	if(a^b)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

int main()
{
	IsEqual(55,98);
	return 0;
}
*/

#if 0

//1����д������1-3+5-7+��.-99+101ֵ֮��
int Add(int n)
{
	int add = 0;
	for(int i=1;i<=n;i+=4)
	{
		add += i;
	}
	for(int j=3;j<=n;j+=4)
	{
		add -= j;
	}

	return add;
}

//2����int arr[4][5]����ת��int brr[20]�� 
int Exchange(int a[][5],int row,int col,int b[])
{ 
	int k = 0;

	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			if(k<row*col)
			{
				b[k] = a[i][j];
				k++;
			}
		}
	}

	return b[row*col];
}

//3����̬����һ�����͵Ķ�ά���顣(���ַ���)
void Mymalloc() 
{
	int i;
	int j;
	int k;

	int (*p)[5] = (int (*)[5])malloc(4*sizeof(int[5]));
	assert(p != NULL);
    
	for(j=0;j<4;++j)
	{
		for(k=0;k<5;++k)
		{
			p[j][k] = j+k; 
		}
	}
	
	for(j=0;j<4;++j)
	{
		for(k=0;k<5;++k)
		{
			printf("%d ",p[j][k]); 
		}
		printf("\n");
	}
	free(p);

	/*
	int **p = (int **)malloc(4*sizeof(int *));
	assert(p != NULL); 
	for(i=0;i<4;++i)
	{
		p[i] = (int *)malloc(sizeof(int)*5);
	}

	for(i=0;i<4;++i)   //�ͷ�
	{
		free(p[i]);
	}
	free(p);*/
}


//4����һ����ά����ÿ��֮�ͣ��õ���ÿ�еĽ������Ҫ���أ�����ʹ�ô�ӡ��
int *SumCol(int a[][5],int row,int col,int b[])
{
	int sum = 0;  //ÿ��֮��
	int k = 0;

	for(int i=0;i<col;++i)
	{
		for(int j=0;j<row;++j)
		{
			sum += a[j][i];
		}

		b[k] = sum;
		k++;
		sum = 0;
	}

	return b;
}

void Show(int a[],int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%d ",a[i]);
	}

	printf("\n");
}

int main()
{
	int arr[][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20}};
	int brr[20];
	int crr[5];
	
	Add(101);
	Exchange(arr,4,5,brr);
	Show(brr,20);
	SumCol(arr,4,5,crr);
	Show(crr,5);
	Mymalloc(); 

	return 0;
}

#endif 


#if 1
//�� n!
int Factorial(int n)
{
	int product = 1;
	for(int i=1;i<=n;++i)
	{
		product *= i;
	}
	return product;
}

//��Ŀ����1��2��3��4�����֣�����ɶ��ٸ�������ͬ�����ظ����ֵ���λ�������Ƕ��٣�
int *Digit(int n)
{
	int a = 0;
	int number = Factorial(n);
	int *arr = (int*)malloc(sizeof(int)*number);//arr������λ��
	assert(arr!=NULL);

	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			for(int k=1;k<=n;++k)
			{
				if(i!=j && i!=k && j!=k)
				{
					arr[a++] = i*100+j*10+k;
				}
			}
		}
	}

	return arr;
}

//��Ŀ�����9*9�ھ���
void Show(int n)
{
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=i;++j)
		{
			printf("%d*%d=%d  ",j,i,j*i);
		}
		printf("\n");
	}
	printf("\n");
}

//��Ŀ����һ���������ֽ������������磺����90,��ӡ��90=2*3*3*5��
int Decompose(int n)
{
	int arr[10];
	int a = 0;
	printf("%d = ",n);

	for(int i=2;i<=n;++i)
	{
		while(n%i==0)
		{
			arr[a++] = i;
			n /= i;
		}
	}
	
	for(int j=0;j<a;++j)
	{
		printf("%d*",arr[j]);
	}
	printf("1");
	printf("\n");

	return arr[a];
}

//��Ŀ��һ�����������ж����ǲ��ǻ���������12321�ǻ���������λ����λ��ͬ��ʮλ��ǧ
bool IsHuidigit(int m)
{
	int n = m;
	int rever_m = 0; //�������m����
	int tmp = 0;
	int i = 0;

	while(n!=0)
	{
		tmp = n%10;
		rever_m = tmp + rever_m*10;
		n /= 10;
	}

	if(rever_m == m)  //�ж�m��������m�Ƿ����
	{
		return true;
	}
	
	return false;
}

//��Ŀ��һ���ַ������ж����ǲ��ǻ��ġ�����abcba���ǻ��ġ�(���ַ���)
bool IsHuiword(const char *str)
{
	int figure = strlen(str);
	int left = 0;
	int right = figure-1;
	while(left < right)
	{
		if(str[left] != str[right])
		{
			return false;
		}
		left++;
		right--;
	}
	return true;
}
bool IsHuiword2(const char *s)
{
	int i=0;
	int j=0; 

    while (s[j])
	{
		j++;
	} 
	for(j--; i<j  && s[i]==s[j]; i++,j--); 
	
	return (j>i?false:true);
}

//��Ŀ����дһ������������nΪż��ʱ�����ú�����1/2+1/4+...+1/n
       //������nΪ����ʱ�����ú���1/1+1/3+...+1/n(����ָ�뺯��)
double* Add(int n)
{
	double sum = 0;
	double *add = NULL;

	if(n/2==0)
	{
		for(int i=2;i<=n;i=i+2)
		{
			sum += 1.0/i;
		}
		add = &sum;
	}
	else
	{
		for(int j=1;j<=n;j=j+2)
		{
			sum += 1.0/j;
		}
		add = &sum;
	}
	
	return add;
}

int main()
{
	
	//printf("%d\n",Factorial(4));
	int *bn = Digit(4);
	for(int i=0;i<24;++i)
	{
		printf("%d ",bn[i]);
	}
	printf("\n");
	free(bn);
	
	Show(9);

	double *add = Add(101);
	//printf("%f\n",*add);

	Decompose(100000);

	Add(101);

	IsHuidigit(123321);

	//char str[]="abcfrcba";
	char str[]="abccba";
	IsHuiword(str);
	
	return 0;
}

#endif
