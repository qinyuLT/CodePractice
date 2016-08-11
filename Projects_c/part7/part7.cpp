#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>


//#if 0


//�������������Լ��
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

	return m*n/r;
}

/*

//�󷽳̵ĸ�(������������)
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

//�󷽳̵ĸ�(����1������)
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

//�ж�һ�����Ƿ�Ϊ����
bool Isprimer(int n)
{
	for(int i=2;i<n;++i)
	{
		if(n%i == 0)
		{
			//printf("%d��������\n",n);
			return false;
		}
	}
	//printf("%d������\n",n);
	return true;
}


//һ��3*3��������
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

//��������ַ���
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


//���������գ��������������ĵڼ���
int Days(int year,int month,int day)
{
	int an[]={31,28,31,30,31,30,31,31,30,31,30,31};
	int days = 0;
	int i;

	if(year%4==0 && year%100!=0 || year%400==0)  //�жϸ����Ƿ�Ϊ����
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

//���ַ�������
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

//ʮ����ת��Ϊʮ����
int Exchange(const char *s1)
{
	int a = 0;       //����ʮ���Ƶ�ֵ
	int j = 0;       //16��j�η�
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

//���ַ����е�Ԫ����ĸ���Ƶ���һ���ַ�����
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

//���ַ�������ĸ�����֣��ո������ַ���
int Stastistics(char str[], int n,int *digit,int *letter,int *space,int *other)        
{
	int d = 0;   //���ָ���
    int l = 0;   //��ĸ����
	int s = 0;   //�ո����
	int o = 0;   //�����ַ�����

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

//����һ������λ��
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

//����һ�����֣�����ַ�ÿ��������֮����һ���ո�
void SpaceDigit(int n)
{
	int figure = GetFigure(n); //������λ������
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

//�ַ�������С����
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

//�ݹ鷽����n�����õ¶���ʽ��ֵ
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

//�����ֱ���ַ���
char *DigitToChar(char *s1,int len,int digit)
{
	char *s2 = s1; 
	int figure = GetFigure(digit); //������λ������
	int tmp = 0;
	int i;

	while( digit!=0 )
	{
		for(i=0;i<len-1;++i)
		{
			tmp = digit/(int)pow(10.0,figure-1);
	        digit %= (int)pow(10.0,figure-1);
		    figure--;
			s1[i] = tmp+'0';   //�ַ� = ����+'0'(48)
		}
	}

	s1[len-1] = '\0';

	return s2;
}

//�����ַ���
void Show(char *s1)
{
	printf("%s\n",s1);
}
//�����ַ�
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
	int digit  = 0;   //���ָ���
    int letter = 0;   //��ĸ����
	int space  = 0;   //�ո����
	int other  = 0;   //�����ַ�����
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

	GreatestComPiv(30,45);              //�������������Լ��
	LeastComMul(30,45);                 //������������С������
	Oppsite(an,3,3,bn);                 //һ��3*3��������
	ReString(str1,13);                  //��������ַ���
	//Show(str1);
	SortCharacter(str2,10);             //�ַ�������С����
	//Show2(str2,10);
	Isprimer(91);                      //�ж�һ�����Ƿ�Ϊ����
	          
	int total = Equation(1,10,2,&x1,&x2);  //�󷽳̵ĸ�
	if(total == 0)
	{
		printf("��ʵ��\n");
	}
	else if(total == 1)
	{
		printf("x1=x2=%lf\n",x1);
	}
	else
	{
		printf("x1=%lf,x2=%lf\n",x1,x2);
	}
	
	Exchange(s4);                       //ʮ����ת��Ϊʮ����
	Mystrcpy(s1,s2);                    //���ַ����е�Ԫ����ĸ���Ƶ���һ���ַ�����
	//Show(s1);
	Stastistics(s2, 30,&digit,&letter,&space,&other);
	//printf("%d,%d,%d,%d\n",digit,space,letter,other);

	SpaceDigit(37272434);              //����һ�����֣�����ַ�ÿ��������֮����һ���ո�
	Recursion(2);                     //�ݹ鷽����n�����õ¶���ʽ��ֵ
	DigitToChar(s3,7,123456);          //�����ֱ���ַ���
	//Show(s3);
    Days(2014,7,28);                   //���������գ��������������ĵڼ���

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

//����ÿλѧ����ƽ����
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
//����ÿ�ſε�ƽ����
double AverageCour(int std1[],int std2[],int std3[],int len)
{
	double course_ave[5];

	for(int i=0;i<len;++i)
	{
		course_ave[i] = (std1[i]+std2[i]+std3[i])/3.0;
	}

	return course_ave[3];
}

//�ҳ�ÿλѧ����߷�����Ӧ�Ŀ�Ŀ
int FindMax(int std[],int len)
{
	int max = std[0];
	int i;             //�����Ŀ

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

//�ҳ����Է�������߷�
int Max(int std1[],int std2[],int std3[],int len)
{
	int max_grade;

	max_grade = FindMax(std1,len)>FindMax(std2,len)?FindMax(std1,len):FindMax(std2,len);
	max_grade = max_grade>FindMax(std3,len)?max_grade:FindMax(std3,len);

	return max_grade;
}
//��ƽ���ֵķ���
double Variance(int std1[],int std2[],int std3[],int len)
{
	double a;                     //ƽ���ֵķ���
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

	AverageStd(std1,5);                      //����ÿ��ѧ����ƽ����
	AverageCour(std1,std2,std3,5);            //����ÿ�ſε�ƽ����
	FindMax(std1,5);                         //�ҳ�ÿλѧ����߷�����Ӧ�Ŀ�Ŀ
	Max(std1,std2,std3,5);                   //�ҳ����Է�������߷�
	Variance(std1,std2,std3,5);               //��ƽ���ֵķ���

	return 0;
}

#endif
