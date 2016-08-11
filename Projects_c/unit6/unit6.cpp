#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


# if 1
//6.1查找字符
char *FindChar(char const *source,char const *chars)
{
	char *tmp_source = (char *)source;//保存source的首位置
	char *tmp_chars = (char *)chars;  //保存chars的首位置
	//char const *tmp_source = source;
	//char const *tmp_chars = chars;
	assert(source != NULL && chars != NULL);

	while(*source != '\0')
	{
		while(*chars != '\0')
		{
			if(*source == *chars)
			{
				return tmp_source;
			}
			chars++;
		}

		chars = tmp_chars;  //指针从新指向chars的首位置
		source++;
		tmp_source++;
	}

	return NULL;
}

//6.2删除相同字符
int DelSubstr(char *str,char const *substr)
{
	char *start;     //start标记相同字符的开头
	char *s1 = str;  //用s1代替str
	while(*s1 != '\0' && *substr != '\0')
	{
		start = s1;
		while(*s1 == *substr)
		{
			s1++;
			substr++;
		}
		if(*substr == '\0')
		{
			while(*s1)
			{
				*start = *s1;
				start++;
				s1++;
			}
			*start++ = '\0';

			return 1;
		}
		s1++;
	}
	return 0;
}

//字符串逆置
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

//6.5寻找质数
int *Erotosthenes(int n)
{
	int *an = (int *)malloc(sizeof(int)*n);
	assert(an != NULL);

	for(int i=0;i<n;++i)
	{
		an[i] = i+1;
	}
	
	for(int i=0;i<n;++i)
	{
		for(int j=2;j<i;++j)
		{
			if(an[i]%j == 0)
			{
				an[i] = 0;
			}
		}
	}
	
	return an;
}


int main()
{
	char str[] = "abcde";
	char s1[] = "BCDEFG";
	char const s2[] = "CDE";
	//FindChar( "ABCD","BEC");
	//FindChar( "CD","AEDFG");
	FindChar( "ABCD","EFG");
	//printf("%c\n",*FindChar( "ABC","FGHB"));

	DelSubstr(s1,s2);
	puts(s1);
	//ReverseStr(str);
	//puts(str);
	          
	int n = 100;
	int *an = Erotosthenes(n);
	for(int i=0;i<n;++i)
	{
		if(an[i] != 0)
		{
			printf("%d ",an[i]);
		}	
	}
	printf("\n");

	free(an);
	return 0;
}
# endif