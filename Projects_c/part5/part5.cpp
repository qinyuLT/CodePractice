#include<stdio.h>
#include<math.h>
#include<ctype.h>     //调用函数 isdigit()   isalpha()

#define E 0.00001     // 10^-5


//统计数字，字母，空格，其他字符
//用数组传递数字，字母，空格，其他字符
void Stastistics(char str[], int n)        
{
	int digit  = 0;   //数字个数
    int letter = 0;   //字母个数
	int space  = 0;   //空格个数
	int other  = 0;   //其他字符个数

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
	printf("数字个数；%d\n字母个数；%d\n空格个数；%d\n其他字符数；%d\n"
		                                ,digit, letter, space, other);
 
}

//计算 Sn = a+aa+aaa+...+a....a
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

//计算 1!+2!+3!+...+20!
int StageRide(int n)         
{
	int tn = 0;
	int sn = 1;   //保存每个数阶乘之和
	int bn = 1;   //保存每个数的阶乘
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

//计算 sum1 = 1+2+...+n 
int Sum1(int n)       
{
	int sum1 = 0;

	for(int i=0; i<=n; ++i)
	{
		sum1 += i;
	}

	return sum1;
}

//计算 sum2 = 1*1+2*2+...+n*n
int Sum2(int n)      
{
	int sum2 = 0;

	for(int i=0; i<=n; ++i)
	{
		sum2 += i*i;
	}

	return sum2;
}

//计算 sum3 = 1/1+1/2+...+1/n
double Sum3(int n)      
{
	double sum3 = 0;

	for(int i=1; i<=n; ++i)
	{
		sum3 += 1.0/i;
	}
	return sum3;
}

//输出所有的"水仙花数"
void WaterFlowers(int a,int b)
{
	int l = 0;    //保存个位数
	int m = 0;    //保存十位数
	int n = 0;    //保存百位数
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

//计算 2/1+3/2+5/3+13/8....a表示参与计算的个数
float Fibo(int a)  
{
	float   n = 2;   //n表示分子
	float   m = 1;   //m表示分母
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

//100m高度自由下落，落地反弹原高度的一半
//求第10落地共经过的路程，以及第10次反弹的高度

float FreeDown(int n)      //n表示第n次落地
{ 
	float high = 100;
	float x = 100;        //x表示经过的路程
	
	for(int i=2; i<=n; ++i)
	{
		high /= 2;
		x += 2 * high;
	}

	return (x,high/2);
}


//猴子吃桃，每天吃前一天剩下的一半多一个，第10天剩1个，求一共摘了多少个

int MonkeyPeach(int day, int n)        //n表示剩余桃子的数量
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

//找出1000之内的“完数”，如6=1+2+3
void PerfectFigure(int n)
{ 
	int add = 0;                  // 用 add 保存每个数的因子之和

	for(int i=1; i<=n; ++i)
	{
		for(int j=1;j<i;++j)        //j 表示每个数的因子
		{
			if(i%j == 0)
			{
				add += j;         //求每个数因子之和
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

// 输出显示下面的图形
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


//用牛顿迭代发出求方程在1.5附近的根
float F1(float x)                  //原方程
{
	return 2*x*x*x-4*x*x+3*x-6; 
}
float F2(float x)                 //原方程的一阶导函数
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

//用二分法求方程 F1 的根
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

	Stastistics(str,18);             //统计数字，字母，空格，其他字符
	Add(9, 8);                      //计算 Sn = a+aa+aaa+...+a....a
	StageRide(20);                  //计算 1!+2!+3!+...+20!
	Sum1(100);                      //计算 sum1 = 1+2+...+n 
    Sum2(50);                       //计算 sum2 = 1*1+2*2+...+n*n
	Sum3(10);                       //计算 sum3 = 1/1+1/2+...+1/n
	WaterFlowers(100,999);           //输出所有的"水仙花数"
	Fibo(20);                       //计算 2/1+3/2+5/3+13/8....(20个)
	FreeDown(10);                   //自由下落，折半反弹 
	MonkeyPeach(10, 1);             //求第一天一共摘了多少个桃子
	ShowChart();                    //显示图形
	PerfectFigure(1000);            //找出1000之内的“完数”
	Equation(1.5,E);                //求方程在1.5附近的根，2*x*x*x-4*x*x+3*x-6 = 0
	Iteration();                    //用二分法求方程 F1 的根

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