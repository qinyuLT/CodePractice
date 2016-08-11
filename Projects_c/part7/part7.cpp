#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>


//#if 0


//求两个数的最大公约数
int GreatestComPiv(int m,int n)
{
	int r = 0;     //定义r为这两个数的最大公约数

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

//求两个数的最小公倍数
int LeastComMul(int m,int n)
{
	int r = GreatestComPiv(m,n);

	return m*n/r;
}

/*

//求方程的根(调用三个函数)
//d=0;
double Equation1(double a,double b,double c)
{
	double x1 = -b/(2*a);

	return x1;
}
//d<0;
double Equation2(double a,double b,double c)
{
	return 0;
}
//d>0;
double Equation3(double a,double b,double c,double d)             
{
	double x1;
	double x2;

	x1 = (-b+sqrt(d))/(2*a);
	x2 = (-b-sqrt(d))/(2*a);

	printf("%f,%f\n",x1,x2);

	return 0;
}
*/

//求方程的根(调用1个函数)
int Equation(double a,double b,double c,double *x1,double *x2) 
{
	double d = b*b-4*a*c;
	if(a == 0)
	{
		*x1 = *x2 = -c/b;

		return 1;
	}
	else if(d < 0)
	{
		return 0;
	}
	else if(d < 0.000001 && d > -0.000001)
	{
		*x1 = *x2 = -b/(2*a);

		return 1;
	}
	else
	{
		*x1 = (-b+sqrt(d))/(2*a);
	    *x2 = (-b-sqrt(d))/(2*a);
		
		return 2;
	}
}

//判断一个数是否为素数
bool Isprimer(int n)
{
	for(int i=2;i<n;++i)
	{
		if(n%i == 0)
		{
			//printf("%d不是素数\n",n);
			return false;
		}
	}
	//printf("%d是素数\n",n);
	return true;
}


//一个3*3数组逆置
int	Oppsite(int an[][3],int row,int col,int bn[][3])
{
	for(int i=0;i<row;++i)
	{
	    for(int j=0;j<col;++j)
		{
			bn[j][i] = an[i][j];
		}
	}

	return bn[col][row];
}

//反序输出字符串
char *ReString(char *s1,int len)
{
	int n = len-1;
	char *s2 = s1;
	char tmp = 0;

	for(int i=0;i<n--;++i)
	{
		tmp = s1[i];
		s1[i] = s1[n];
		s1[n] = tmp;
	}

	return s2;
}


//给出年月日，计算该日是这年的第几天
int Days(int year,int month,int day)
{
	int an[]={31,28,31,30,31,30,31,31,30,31,30,31};
	int days = 0;
	int i;

	if(year%4==0 && year%100!=0 || year%400==0)  //判断该年是否为闰年
	{
		an[1] = 29;
	}

    for( i=0;i<month;++i)
	{
		days += an[i];
	}

	days += day-an[i-1];
    //printf("%d\n",days);

	return days;
}

//求字符串长度
int Mystrlen(const char *str)
{
	int strlen =0;
	assert(str!=NULL);
	while(*str++ != '\0')
	{
		strlen++;
	}

	return strlen;
}

//十六制转换为十进制
int Exchange(const char *s1)
{
	int a = 0;       //保存十进制的值
	int j = 0;       //16的j次方
	int strlen = Mystrlen(s1);
	assert(s1!=NULL);

	for(int i=strlen-1;i>=0;--i)
	{
		if(s1[i]>='0' && s1[i]<='9')
		{
			a += (s1[i]-'0')*(int)pow(16.0,j++);
		}

		else if( s1[i]>='a' && s1[i]<='f' )
		{
			a += (s1[i]-'a'+10)*(int)pow(16.0,j++);
		}

		else if( s1[i]>='A' && s1[i]<='F' )
		{
			a += (s1[i]-'A'+10)*(int)pow(16.0,j++);
		}
	}

	//printf("%d\n",a);
	return a;
}

/*
int Exchange(int n) 
{
	int tmp = 0; 
	int len = 0;
	int a = 0;

	for(int i=0;i<10;++i)
	{
		tmp = n%10;
		n = n/10;
		a += tmp*(int)pow(16.0,i);
	}
	//printf("%d\n",a);

	return a;
}
*/

//把字符串中的元音字母复制到另一个字符串上
char *Mystrcpy(char *s1,const char* s2)
{
	char *tmp = s1;
	assert(s1!=NULL && s2!=NULL);

	while(*s2 != '\0')
	{
		while( *s2 == 'a'|| *s2 == 'e'|| *s2 == 'i'|| *s2 == 'o'|| *s2 == 'u'
			|| *s2 == 'A'|| *s2 == 'E'|| *s2 == 'I'|| *s2 == 'O'|| *s2 == 'U') 
		{
			*s1++ = *s2++;
		}

		*s2++;
	}

	*s1 = '\0';

	return tmp;
}

//求字符串中字母，数字，空格，其他字符数
int Stastistics(char str[], int n,int *digit,int *letter,int *space,int *other)        
{
	int d = 0;   //数字个数
    int l = 0;   //字母个数
	int s = 0;   //空格个数
	int o = 0;   //其他字符个数

	for(int i=0; i<n; ++i)
	{
		//if( str[i]>='0' && str[i]<='9' )
		if( isdigit(str[i]) )
		{
			*digit = ++d;
		}

		//else if(str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z')
		else if( isalpha(str[i]) ) 
		{
			*letter = ++l;
		}
		
		else if(' ' == str[i])
		{
			*space = ++s;
		}

		else
		{
			*other = ++o;
		}
	}
	
	return 0;
}

//计算一个数的位数
int GetFigure(int n)
{
	int figure = 0;

	while(n !=0 )
	{
		n /= 10;
		figure++;
	}

	return figure;
}

//输入一个数字，输出字符每两个数字之间有一个空格
void SpaceDigit(int n)
{
	int figure = GetFigure(n); //调用求位数函数
	int tmp = 0;

	while(n!=0)
	{
		tmp = n/(int)pow(10.0,figure-1);
		n %= (int)pow(10.0,figure-1);
		figure--;
		printf("%d ",tmp);
	}

	printf("\n");
}

//字符排序，由小到大
char *SortCharacter(char *s1,int len)
{
	char *s2 = s1;
	char tmp = 0; 
	
	for(int i=0;i<len;++i)
	{
		for(int j=i+1;j<len;++j)
		{
			if(s1[i] > s1[j])
			{
				tmp = s1[j];
			    s1[j] = s1[i];
			    s1[i] = tmp;
			}
		}

	}

	return s2;
}

//递归方法求n阶勒让德多项式的值
int Recursion(int n)
{
	int x = 1;

	if(0 == n)
	{
		return 1;
	}

	if(1 == n)
	{
		return x;
	}

	else
	{
		return ((2*n-1)*x-Recursion(n-1)-(n-1)*Recursion(n-2))/n;
	}
}

//把数字变成字符串
char *DigitToChar(char *s1,int len,int digit)
{
	char *s2 = s1; 
	int figure = GetFigure(digit); //调用求位数函数
	int tmp = 0;
	int i;

	while( digit!=0 )
	{
		for(i=0;i<len-1;++i)
		{
			tmp = digit/(int)pow(10.0,figure-1);
	        digit %= (int)pow(10.0,figure-1);
		    figure--;
			s1[i] = tmp+'0';   //字符 = 数字+'0'(48)
		}
	}

	s1[len-1] = '\0';

	return s2;
}

//测试字符串
void Show(char *s1)
{
	printf("%s\n",s1);
}
//测试字符
void Show2(char s1[],int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%c",s1[i]);
	}

	printf("\n");
}

int main()
{
	int digit  = 0;   //数字个数
    int letter = 0;   //字母个数
	int space  = 0;   //空格个数
	int other  = 0;   //其他字符个数
	int an[][3] = {1,2,3,4,5,6,7,8,9};
	int bn[3][3];

	double x1 = 0;
	double x2 = 0;
	
	char str1[] = "hello world!";
	char str2[] = {'a','A','c','E','e','b','B','C','D','d'};
	char s1[30];
	char s2[30] = "ab Ef 4%^2Iu s co9h&*89b@he";
	char s3[7];
	char s4[] = "11abc";

	GreatestComPiv(30,45);              //求两个数的最大公约数
	LeastComMul(30,45);                 //求两个数的最小公倍数
	Oppsite(an,3,3,bn);                 //一个3*3数组逆置
	ReString(str1,13);                  //反序输出字符串
	//Show(str1);
	SortCharacter(str2,10);             //字符排序，由小到大
	//Show2(str2,10);
	Isprimer(91);                      //判断一个数是否为素数
	          
	int total = Equation(1,10,2,&x1,&x2);  //求方程的根
	if(total == 0)
	{
		printf("无实根\n");
	}
	else if(total == 1)
	{
		printf("x1=x2=%lf\n",x1);
	}
	else
	{
		printf("x1=%lf,x2=%lf\n",x1,x2);
	}
	
	Exchange(s4);                       //十六制转换为十进制
	Mystrcpy(s1,s2);                    //把字符串中的元音字母复制到另一个字符串上
	//Show(s1);
	Stastistics(s2, 30,&digit,&letter,&space,&other);
	//printf("%d,%d,%d,%d\n",digit,space,letter,other);

	SpaceDigit(37272434);              //输入一个数字，输出字符每两个数字之间有一个空格
	Recursion(2);                     //递归方法求n阶勒让德多项式的值
	DigitToChar(s3,7,123456);          //把数字变成字符串
	//Show(s3);
    Days(2014,7,28);                   //给出年月日，计算该日是这年的第几天

	/*
	double d = b*b-4*a*c; 

	if(d == 0 )
	{
		printf("x1=x2=%f\n",Equation1(a,b,c));
	}
	else if(d < 0)
	{
		Equation2(a,b,c);
	}
	else
	{
		Equation3(a,b,c,d);
	}
	*/

	return 0;
}
//#endif


#if 0

//计算每位学生的平均分
double AverageStd(int std[],int len)
{
	double grade_ave = 0;

	for(int i=0;i<len;++i)
	{
		grade_ave += std[i];
	}

	grade_ave /= len; 
	//printf("%f\n",grade_ave);

	return grade_ave;
	
}
//计算每门课的平均分
double AverageCour(int std1[],int std2[],int std3[],int len)
{
	double course_ave[5];

	for(int i=0;i<len;++i)
	{
		course_ave[i] = (std1[i]+std2[i]+std3[i])/3.0;
	}

	return course_ave[3];
}

//找出每位学生最高分所对应的科目
int FindMax(int std[],int len)
{
	int max = std[0];
	int i;             //代表科目

	for(i=0;i<len;++i)
	{
		while(max < std[i])
		{
			max = std[i];
		}
	}

	//printf("%d\n",i);

	return max;
}

//找出所以分数中最高分
int Max(int std1[],int std2[],int std3[],int len)
{
	int max_grade;

	max_grade = FindMax(std1,len)>FindMax(std2,len)?FindMax(std1,len):FindMax(std2,len);
	max_grade = max_grade>FindMax(std3,len)?max_grade:FindMax(std3,len);

	return max_grade;
}
//求平均分的方差
double Variance(int std1[],int std2[],int std3[],int len)
{
	double a;                     //平均分的方差
	double s1 = AverageStd(std1,5);
	double s2 = AverageStd(std2,5);
	double s3 = AverageStd(std3,5);

	a =  (s1*s1+s2*s2+s3*s3)/len-((s1+s2+s3)/len)*((s1+s2+s3)/len);

	//printf("%f\n",a);
	return a;
}

int main()
{
	int std1[] = {80,76,98,76,85};
	int std2[] = {91,98,93,96,97};
	int std3[] = {60,59,64,69,54};

	AverageStd(std1,5);                      //计算每个学生的平均分
	AverageCour(std1,std2,std3,5);            //计算每门课的平均分
	FindMax(std1,5);                         //找出每位学生最高分所对应的科目
	Max(std1,std2,std3,5);                   //找出所以分数中最高分
	Variance(std1,std2,std3,5);               //求平均分的方差

	return 0;
}

#endif
