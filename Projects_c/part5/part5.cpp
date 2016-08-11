#include<stdio.h>
#include<math.h>
#include<ctype.h>     //���ú��� isdigit()   isalpha()

#define E 0.00001     // 10^-5


//ͳ�����֣���ĸ���ո������ַ�
//�����鴫�����֣���ĸ���ո������ַ�
void Stastistics(char str[], int n)        
{
	int digit  = 0;   //���ָ���
    int letter = 0;   //��ĸ����
	int space  = 0;   //�ո����
	int other  = 0;   //�����ַ�����

	for(int i=0; i<=n; ++i)
	{
		if(str[i]>='0' && str[i]<='9')
		//if( isdigit( str[i]) )
		{
			digit++;
		}

		else if(str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z')
		//else if( isalpha( str[i]) )
		{
			letter++;
		}

		else if(' ' == str[i])
		{
			space++;
		}

		else
		{
			other++;
		}
	}
	printf("���ָ�����%d\n��ĸ������%d\n�ո������%d\n�����ַ�����%d\n"
		                                ,digit, letter, space, other);
 
}

//���� Sn = a+aa+aaa+...+a....a
int Add(int a, int n)   
{
	int i  = 1;
	int tn = 0;
	int sn = 0;

	while(i<=n)
	{
		tn += a;
		sn += tn;
		a  *= 10;
		++i;
	}

	return sn;
}

//���� 1!+2!+3!+...+20!
int StageRide(int n)         
{
	int tn = 0;
	int sn = 1;   //����ÿ�����׳�֮��
	int bn = 1;   //����ÿ�����Ľ׳�
	int i  = n;

	while(n>=2)
	{
		while(i>=2)
		{
			tn = i * (i-1);
		    bn *= tn;
		    i -= 2;
		}

		sn += bn;
		bn = 1;
		i = --n;
	}
	
	return sn;
}

//���� sum1 = 1+2+...+n 
int Sum1(int n)       
{
	int sum1 = 0;

	for(int i=0; i<=n; ++i)
	{
		sum1 += i;
	}

	return sum1;
}

//���� sum2 = 1*1+2*2+...+n*n
int Sum2(int n)      
{
	int sum2 = 0;

	for(int i=0; i<=n; ++i)
	{
		sum2 += i*i;
	}

	return sum2;
}

//���� sum3 = 1/1+1/2+...+1/n
double Sum3(int n)      
{
	double sum3 = 0;

	for(int i=1; i<=n; ++i)
	{
		sum3 += 1.0/i;
	}
	return sum3;
}

//������е�"ˮ�ɻ���"
void WaterFlowers(int a,int b)
{
	int l = 0;    //�����λ��
	int m = 0;    //����ʮλ��
	int n = 0;    //�����λ��
	int tmp;

	for(int i=a;i<=b;++i)
	{
		l = i%10;    
		m = i/10%10;
		n = i/100;
		tmp = l*l*l+m*m*m+n*n*n;

		if(tmp == i)
		{
			printf("%d ",i);
		}
	}
	printf("\n");
}

//���� 2/1+3/2+5/3+13/8....a��ʾ�������ĸ���
float Fibo(int a)  
{
	float   n = 2;   //n��ʾ����
	float   m = 1;   //m��ʾ��ĸ
	float tmp = n;
	float sum = 0;

	for(int i=1; i<=a; ++i)
	{
		sum += n/m;
		tmp = n;
		n += m;   
		m  = tmp;
	}

	return sum;
}

//100m�߶��������䣬��ط���ԭ�߶ȵ�һ��
//���10��ع�������·�̣��Լ���10�η����ĸ߶�

float FreeDown(int n)      //n��ʾ��n�����
{ 
	float high = 100;
	float x = 100;        //x��ʾ������·��
	
	for(int i=2; i<=n; ++i)
	{
		high /= 2;
		x += 2 * high;
	}

	return (x,high/2);
}


//���ӳ��ң�ÿ���ǰһ��ʣ�µ�һ���һ������10��ʣ1������һ��ժ�˶��ٸ�

int MonkeyPeach(int day, int n)        //n��ʾʣ�����ӵ�����
{
	int sum = 0;

	while(day!=1)
	{
		sum = 2 * (n+1);
		n = sum;            
		day--;
	}

	return sum;
}

//�ҳ�1000֮�ڵġ�����������6=1+2+3
void PerfectFigure(int n)
{ 
	int add = 0;                  // �� add ����ÿ����������֮��

	for(int i=1; i<=n; ++i)
	{
		for(int j=1;j<i;++j)        //j ��ʾÿ����������
		{
			if(i%j == 0)
			{
				add += j;         //��ÿ��������֮��
			}	
		}

		if(add==i)
	    {
			printf("%d ",add);
		}	
		
		add = 0;              
     }

	printf("\n ");
}

// �����ʾ�����ͼ��
//    *
//   ***
//  *****
// *******
//  *****
//   ***
//    *

void ShowChart()                                   
{                                             
	int i; 
	int j;  
	int k; 
                                     
	for(i = 0; i <= 3; ++i)                        
	{
		for(j = 0; j <= 2-i; ++j)
		{
			printf(" ");
		}
		for(k=0; k<=2*i; ++k)
		{
			printf("*");
		}
		printf("\n");
	}
	for(i=0; i<=2; ++i)
	{
		for(j = 0; j <= i; ++j)
		{
			printf(" ");
		}
		for(k =0; k <= 4-2*i; ++k)
		{
			printf("*");
		}
		printf("\n");
	}
	
}


//��ţ�ٵ��������󷽳���1.5�����ĸ�
float F1(float x)                  //ԭ����
{
	return 2*x*x*x-4*x*x+3*x-6; 
}
float F2(float x)                 //ԭ���̵�һ�׵�����
{
	return 6*x*x-8*x+3;
}
float Equation(float x0,float a) //x0=1.5  a=1e-5 
{
	float x1 = 0;

	while(fabs(x1-x0)>a)
	{
		x1 = x0;
		x0 = x1-F1(x1)/F2(x1);
	}

	return x0;
}

//�ö��ַ��󷽳� F1 �ĸ�
float Iteration()
{
	float a = -9.8;
	float b = 10.2;
	float c = (a+b)/2;

	while(fabs(F1(c))>E && fabs(F1(a-b))>E)
	{
		if(F1(c)*F1(b)<0)
		{
			a = c;
		}
		if(F1(a)*F1(c)<0)
		{
			b = c;
		}
		c = (a+b)/2;
	}
	return c;
}


int main()
{
	char str[]={"24aB5 o# $ %&@ fg"};

	Stastistics(str,18);             //ͳ�����֣���ĸ���ո������ַ�
	Add(9, 8);                      //���� Sn = a+aa+aaa+...+a....a
	StageRide(20);                  //���� 1!+2!+3!+...+20!
	Sum1(100);                      //���� sum1 = 1+2+...+n 
    Sum2(50);                       //���� sum2 = 1*1+2*2+...+n*n
	Sum3(10);                       //���� sum3 = 1/1+1/2+...+1/n
	WaterFlowers(100,999);           //������е�"ˮ�ɻ���"
	Fibo(20);                       //���� 2/1+3/2+5/3+13/8....(20��)
	FreeDown(10);                   //�������䣬�۰뷴�� 
	MonkeyPeach(10, 1);             //���һ��һ��ժ�˶��ٸ�����
	ShowChart();                    //��ʾͼ��
	PerfectFigure(1000);            //�ҳ�1000֮�ڵġ�������
	Equation(1.5,E);                //�󷽳���1.5�����ĸ���2*x*x*x-4*x*x+3*x-6 = 0
	Iteration();                    //�ö��ַ��󷽳� F1 �ĸ�

	//printf("%d\n",MonkeyPeach(10, 1));
	//printf("%lf\n",Equation(1.5,E));
	//printf("%lf\n",Iteration());
	//printf("%d\n",Add(9, 8));       
	//printf("%d\n",Sum1(100));        
	//printf("%d\n",StageRide(20));   
	//printf("%d\n",Sum2(50));         
	//printf("%.4f\n",Sum3(10)); 
	//printf("%lf\n",Fibo(20));        
	
	return 0;
}