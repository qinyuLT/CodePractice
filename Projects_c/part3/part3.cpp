#include<stdio.h>
#include<math.h>
#define N 3.14                          

double NationalIncome(double r,int n)      //计算p=（1+r）^n
{
	//double p=pow((1+r),n);    
	//printf("%lf\n",p);
	return pow((1+r),n);
}

float Loan(float d,float p,float r)      //计算多少月还清贷款
{
	float m;                          
	m=log(p/(p-d*r))/log(1+r);
	//printf("%.2f\n",m);
	return m;
}

double Circle(double r)               
{
	double s;
	double l;
	s=N*r*r;                         //圆面积计算公式
	l=2*N*r;                         //圆周长计算公式
	//printf("圆的面积：%.2f,圆的周长：%.2f\n",s,l);
	return (s,l);
}
double Cylinder(double r,double h)
{
	double s;
	double v;
	s=2*N*r*(r+h);                    //圆柱表面积计算公式
	v=N*r*r*h;                       // 圆柱体积计算公式
	//printf("圆柱的表面积：%.2f,圆柱的体积：%.2f\n",s,v);
	return (s,v);
}
double Globe(double r)
{
	double s;
	double v;
	s=4*N*r*r;                       //圆球表面积计算公式
	v=4*N*r*r*r/3;                   //圆球体积计算公式
	//printf("圆球的表面积：%.2f,圆球的体积：%.2f\n",s,v);
	return (s,v);
}

char Password(char an[],int n)
{
	for(int i=0;i<n;++i)
	{
		an[i]+=4;
		printf("%c\n",an[i]);
		//return (an[i]);
	}
	return 0;
}

double Deposit(int a,int n)
{
	double r1=0.0414;
	double r2=0.0468;
	double r3=0.054;
	double r5=0.0585;
	double r0=0.0072;
	double p1,p2,p3,p4,p5;

	p1=a*(1+5*r5);                   //一次存5年
	p2=a*(1+2*r2)*(1+3*r3);          //先存2年，再存3年
	p3=a*(1+3*r3)*(1+2*r2);          //先存3年，再存2年
	p4=a*pow((1+r1),n);              //存5次一年
	p5=a*pow((1+r0/4),4*n);           //活期存款

	//printf("%.3f, %.3f, %.3f, %.3f, %.3f\n",p1,p2,p3,p4,p5);
	return (p1,p2,p3,p4,p5);
}



int main()
{
	char an[5]={'C','h','i','n','a'};
    NationalIncome(0.09,10);
	Loan(30000,6000,0.01);
	Circle(2.0);
	Cylinder(2.0,4.0);
	Globe(2.0);
	Password(&an[0],5);
	Deposit(1000,5);

	/* 

	//运行时会输出什么信息
	//char c1=97,c2=98;
	//char c1=197,c2=198;
	int c1=97,c2=98;
	printf("c1=%c,c2=%c\n",c1,c2);  //c1=a,c2=b      c1=?,c2=?        c1=a,c2=b
	printf("c1=%d,c2=%d\n",c1,c2);  //c1=97,c2=98    c1=-59,c2=-58    c1=97,c2=98
	
	int a,b;
	float x,y;
	char c1,c2;
	scanf("a=%db=%d",&a,&b);
	scanf("x=%fy=%f",&a,&b);
	scanf("c1=%cc2=%c",&a,&b);
	
	*/

	return 0;
	
} 
