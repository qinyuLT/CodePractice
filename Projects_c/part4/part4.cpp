#include<stdio.h>
#include<math.h>

#define M 100000;            // n = ���� / M


//���a��b��c��������
int Max(int a,int b,int c)   
{
	int max=a;
	if(a < b)
	{
		max = b;
	}
	if(c > max)
	{
		max = c;
	}
	return max;
}

//һ����������xֵ����y��ֵ
int Function(int x)       
{
	int y;

	if(x<1)
	{
		y=x;
	}

    if(x>=10)
	{
		y=3*x-11;
	}
	else
	{
		y=2*x-1;
	}
    //printf("y=%d\n",y);
	return y;
}

//�����ĸ���������С�����������
void Arrange(int a,int b,int c,int d)  
{
	int temp;

	if(a>b)
	{
		temp = a;
		a = b;
		b = temp;
	}
    if(a>c)
	{
		temp = a;
		a = c;
		c = temp;
	}
	if(a>d)
	{
		temp = a;
		a = d;
		d = temp;
	}
	if(b>c)
	{
		temp = b;
		b = c;
		c = temp;
	}
	if(b>d)
	{
		temp = b;
		b = d;
		d = temp;
	}
	if(c>d)
	{
		temp = c;
		c = d;
		d = temp;
	}
	//printf("%d<%d<%d<%d\n",a,b,c,d);
}


//����ȼ������������
void ScoreGrade1(char grade)    
{  
  switch(grade)
  {  
	case 'A': 
		printf(">=90\n");
		break;
	case 'B':
		printf("80��89\n");
		break;
	case 'C':
		printf("70��79\n");
		break;
	case 'D':
		printf("60��69\n");
		break;
	case 'E':
		printf("< 60\n");
		break;
	default:
		printf("enter error!\n");
		break;
	}	
}

//�������������ȼ�
void ScoreGrade2(int score)     
{
	if(score >= 90)
	{
		printf("A\n");
	}
	if(score>=80 && score<=89)
	{
		printf("B\n");
	}
	if(score>=70 && score<=79)
	{
		printf("C\n");
	}
	if(score>=60 && score<=69)
	{
		printf("D\n");
	}
	if(score <= 60)
	{
		printf("E\n");
	}
}

//��һ����������ƽ����������������� 
int Mysqrt(int n)
{
	int i;
	for(i=1;i*i<=n;++i)
	{
		;
	}
	return i-1;
}
/*
double Sqrt(double a)                
{
	if(a>0 && a<1000)
	{
		return (sqrt(a));
	}
	else 
	{
		return -1;
	}
}
*/

//���𷢷Ÿ����������,n=����/100000
double Profit(double n)             
{
	double money=0;                //����moneyΪ����
	if(n<=1)
	{
		money=(n+0.01)*M;
		return money;
	}
	if(n>1 && n<2)
	{
		money=(n+((n-1)*0.075+0.1))*M;
		return money;
	}	
	if(n>2 && n<4)
	{
		money=(n+((n-2)*0.05+0.075+0.1))*M;
		return money;
	}	
	if(n>4 && n<6)
	{
		money=(n+((n-4)*0.03+2*0.05+0.075+0.1))*M;
		return money;
	}
	if(n>6 && n<10)
	{
		money=(n+((n-6)*0.015+2*0.03+2*0.05+0.075+0.1))*M;
		return money;
	}	
	else
	{
		money=(n+((n-10)*0.01+4*0.015+2*0.03+2*0.05+0.075+0.1))*M;
		return money;
	}
}

//��һ������λ���������ÿλ�ϵ�����
int Figure(int a)              
{
	int tmp = a;  
	int digit[100];           //������ͳ��ÿλ�ϵ�����
	int digit_num = 0;          //��¼������ֵ�λ��

	if(0 == a )
	{
		digit_num = 1;
		//printf("0");
	}
	else if(a<0)
	{   
		printf("-");
		for(int i=0;tmp != 0;++i)
		{
			digit[i] = -tmp%10;
		    tmp = tmp/10;
		    digit_num++;
		    printf("%d ",digit[i]);
	    }
	}
	else 
	{
		for(int i=0;tmp!=0;++i)
		{
			digit[i] = tmp%10;
		    tmp = tmp/10;
		    digit_num ++;
		    printf("%d ",digit[i]);
	    }
	}
	printf("\n");
	return digit_num;
}


int main()
{
	printf("Max=%d\n",Max(3,9,6));
	Function(20);
	ScoreGrade1('A');
	ScoreGrade2(80);
	Arrange(13,11,9,51);
	//printf("%.0lf\n",Sqrt(50));
	Mysqrt(8);
	printf("����%f\n",Profit(4.5));   //n=����/100000
	Figure(0);
	printf("%d\n",Figure(-12345));
	
	return 0;
}