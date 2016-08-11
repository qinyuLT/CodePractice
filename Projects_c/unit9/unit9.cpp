#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PRINT(FORMAT,VALUE)    \
	   printf("The value is "FORMAT"\n",VALUE)
#define MAX(a,b)   ((a)>(b) ?(a):(b))

int Max_(int a ,int b)
{
	return a>b?a:b;
}

int main()
{
	int x = 5;
	int y = 8;
	//int z = MAX(x++,y++);
	//PRINT("%d",3+5);
	int z = Max_(x++,y++);
	printf("x=%d\ny=%d\nz=%d\n",x,y,z);
	return 0;
}

#if 0
//9.7
char *MyStrrchr(char const *str,int ch)
{
	char *tmp = NULL;
	while(*str != '\0')
	{
		if(*str == ch)
		{
			tmp = (char*)str;
		}
		str++;
	}
	return tmp;
}

//9.8
char *MyStrnchr(char const *str,int ch,int which)
{
	char *tmp = NULL;
	int number = 0;

	while(*str != '\0')
	{
		if(*str == ch)
		{
			tmp = (char*)str;
			number++;
		}
		if(number == which)
		{
			return tmp;
		}
		str++;
	}

	return NULL;
}

char *Mystrncpy(char *dst,char const *str,int len)
{
	int tmp = 0;
	assert(dst != NULL && str != NULL);
	while (tmp < len)
	{
		*dst++ = *str++;
		tmp++;
	}
	*dst = '\0';

	return dst;
}

char *Mystrncat(char *dst,char const *str,int len)
{
	int tmp = 0;
	assert(dst != NULL && str != NULL);
	while(*dst != '\0')
	{
		dst++;
	}
	
	while(tmp < len)
	{
		*dst++ = *str++;
		tmp++;
	}
	*dst = '\0';

	return dst;
}

int Mystrncmp(char const *s1,char const *s2,int len )
{
	int tmp = 0;
	assert(s1 != NULL && s2 != NULL);

	while(tmp < len)
	{
		if(*s1 != *s2)
		{
			return *s2-*s1;
		}
		s1++;
		s2++;
		tmp++;
	}
	return 0;
}

//数字转成（2-36）进制字符串
void ReverseStr(char *str);
char *Myitoa(int digit,char *str,int radix)
{
	int i = 0;
	int tmp = 0;

	while(digit != 0)
	{
		tmp = digit%radix;

		if(tmp > 9)
		{
			str[i++] = tmp -10 + 'a';
		}
		else
		{
			str[i++] = tmp + '0';
		}
		digit /= radix;
	}
	str[i++] = '\0';

	ReverseStr(str);

	return str;
}
void ReverseStr(char *str)
{
	char *last = str;
	char tmp;
	while(*last != '\0')
	{
		last++;
	}
	last--;

	while(last > str)
	{
		tmp = *str;
		*str++ = *last; 
		*last-- = tmp;
	}
}

int main()
{
	//char str[40] = "hello word!";
    //char s1[20];
	//char s2[] = "abcdefgh";
	//char *p = MyStrrchr(str,'o');
	//char *p = MyStrnchr(str,'o',3);
	//Mystrncpy(s1,s2,1);
	//Mystrncat(str,s2,7);
	//puts(str);
	//printf("%d\n",Mystrncmp(str,s2,7));

	char str[20];
	Myitoa(750,str,30);
	//Myitoa(750,str,2);
	//Myitoa(750,str,16);
	printf("%s\n",str);

	return 0;
}

#endif