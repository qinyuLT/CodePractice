#include<stdio.h>
#include<math.h>


//4.(1) ����������ֵ
void Exchange( int a,int b )                       
{
	int temp = a;
	a = b;
	b = temp;

	printf("a=%d,b=%d\n",a,b );
}

 //4.(2) ��ʮ���������ֵ
int Max( int a[],int n )                        
{
	int max = a[0];

	for( int i=0;i<10;++i )
	{
		if(max < a[i])
		{
			max = a[i];
		}	
	}

	printf("Max=%d\n",max);
	return max;
}

//4.(3)�������Ӵ�С����
void Arrange( int a,int b,int c )               
{
	int tmp;

	if(a < b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
    if(a < c)
	{
		tmp = a;
		a = c;
		c = tmp;
	}
	if(b < c)
	{
		tmp = b;
		b = c;
		c = tmp;
	}
	
	printf("%d > %d > %d\n",a,b,c);
}


//4.(4)��1��100�ĺ�
int Add()                                          
{
	int add = 0;
	for( int i=1;i<=100;++i)
	{
		add += i;
	}
	return add;
}

//4.(5)�ж�a�ܷ�ͬʱ��3��5����
int Divided( int a )                              
{
	if(  a%3 == 0 && a%5 == 0 )
	{
		printf("%d��ͬʱ��3��5����\n",a);
	}
	else
	{
		printf("%d����ͬʱ��3��5����\n",a );
	}
	return 0;	
}
//4.(6)���100-200֮�������
void Primer(int a)
{
	int j;
	for(int i=100;i<=a;++i)
	{
		for(j=2;j<a;++j)
		{
			if(i%j == 0)
			{
				break;
			}	
		}
		if(j >= i)
		{
			printf("%d\n",i);
		}
	}
	
}
//4.(7)�������������Լ��
int GreatestComPiv(int m,int n)
{
	int r = 0;     //����rΪ�������������Լ��
	if(0 == m*n)
	{
		return 0;
	}
	else
	{
		while(m%n != 0)
		{
			r = m%n;
			m = n;
			n = r;
		}
	}
	return r;
}
//������������С������
int LeastComMul(int m,int n)
{
	int r = GreatestComPiv(m,n);
	 //int a = m*n/r;
	//return  a;
	return m*n/r;
}

//4.(8)�󷽳̵ĸ�
void Equation( float a,float b,float c)             
{
	float x1;
	float x2;
	float d;
	d= b*b-4*a*c;
	if(a == 0)
	{
		printf("%f\n",x1=-c/b);
	}
	else 
	{  
		if( d<0 )
		{
		    printf("�����޸���\n");
	    }
	    if( d==0 )
		{    
			printf("x1=x2=%f\n",x1=x2=-b/(2*a) );
	    }
		else
		{
			x1=(-b+sqrt(d))/(2*a);
			x2=(-b-sqrt(d))/(2*a);
			printf("x1=%f,x2=%f\n",x1,x2 );
		}
	}
}

//8.(1)1900-2000������������
int LeapYear(int y1,int y2)                            
{
	for( int i=y1;i<=y2;++i )
	{
		if( i%4==0 && i%100!=0|| i%400==0 )
		{
			//printf("%d\n",i);
			return i;
		}
	}	
	return 0;
}

int main()
{
	int a[10]={4,5,9,7,1,81,3,6,2,10};

	Exchange(10,9);
	Max(a,10); 
	printf("%d\n",Add());
	Divided(25);
	Equation(1,-3,2);
	Arrange(4,9,10);
	LeapYear(1900,2000);
    GreatestComPiv(30,45);
	LeastComMul(30,45);
	Primer(200);

	return 0;
} 