#include <stdio.h>
#include <stdarg.h>  
#include <string.h>

int Hermite(int n,int x)
{
	if(n<0 && 0==n)
	{
		return 0;
	}
	if(1 == n)
	{
		return 2*x;
	}

	return (2*x*Hermite(n-1,x)-2*(n-1)*Hermite(n-2,x));
}

//求两个数的最小公倍数
int Gcd(int m,int n)
{
	int r = m%n;

	if(0 == r)
	{
		return n;
	}

	return Gcd(n,r);
}

//求任意以-1结尾的整数数列的最大值
int Max(int first,...)
{
	int max = first; 
	va_list list;

	if(first > 0)
	{
		int digit;

		va_start(list,first);
		while((digit = va_arg(list,int))>0)
		{
			if( digit > max )
			{
				max = digit;
			}
		}
		va_end( list );
	}

	return max;
}

void Print(const char *str,...)
{
	va_list list;
	va_start(list,str);
	int tmp_d;
	char buff[20];
	char *pstr;
	char *p = (char *)str;
	while(*p != '\0')
	{
		if(*p == '%')
		{
			switch(*(p+1))
			{
			case 'c':
				putchar(va_arg(list,char));
				p++;
				break;
			case 'd':
				tmp_d = va_arg(list,int);
				sprintf(buff,"%d",tmp_d);
				fwrite(buff,sizeof(char),strlen(buff),stdout);
				p++;
				break;
			case 's':
				pstr  = va_arg(list,char*);
				fwrite(pstr,sizeof(char),strlen(pstr),stdout);
				p++;
				break;
			case 'f':
				//print_float( va_arg(list, float ) );
				break;
			default:
				putchar('%');
				break;
			}
		}
		else
		{
			printf("%c",*p);
		}
		p++;
	}
}

int main()
{
	//Print("abc");

	//Hermite(3,2);

	//Gcd(10,26);

	//Max(23,45,65,43,2,3,-1)；

	Print("%d\n",Max(-1));
	Print("%d\n",Max(23,45,65,43,2,3,-1));

	return 0;
}