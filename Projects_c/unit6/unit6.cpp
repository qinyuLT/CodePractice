#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


# if 1
//6.1�����ַ�
char *FindChar(char const *source,char const *chars)
{
	char *tmp_source = (char *)source;//����source����λ��
	char *tmp_chars = (char *)chars;  //����chars����λ��
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

		chars = tmp_chars;  //ָ�����ָ��chars����λ��
		source++;
		tmp_source++;
	}

	return NULL;
}

//6.2ɾ����ͬ�ַ�
int DelSubstr(char *str,char const *substr)
{
	char *start;     //start�����ͬ�ַ��Ŀ�ͷ
	char *s1 = str;  //��s1����str
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

//�ַ�������
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

//6.5Ѱ������
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