#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
//输一个字符串以“！”结束，将小写字母转换成大写字母输出到磁盘“text”中保存
char *Exchange(char *str,int len,char *bn)
{
	int j = 0;
	for(int i=0;i<len;++i)
	{
		if(islower(str[i]))
		{
			bn[j++] = str[i]-32;
		}
		else if(isupper(str[i]))
		{
			bn[j++] = str[i];
		}
	}
	bn[j] = '\0';

	return bn;
}

int main()
{
	char str[] = "svABCad13rsaf 4ff5";
	int len = strlen(str);
	char bn[100];
	Exchange(str,len,bn);

	char *path = "d:\\text.txt";
	FILE *fw = fopen(path,"w");
	assert(fw != NULL);

	fwrite(bn,sizeof(char),strlen(bn),fw);

	fclose(fw);
	return 0;
}
*/
//磁盘A,B各有一行字符串，按字母顺序输出到磁盘C中

/*
int main()
{
	FILE *fp ;
	char str[3][10];
	char tmp[10];
	int i;
	int j;
	int k;
	int n = 3;
	printf("Enter string:\n");
	for(i=0;i<n;++i)
	{
		gets(str[i]);
	}

	for(i=0;i<n-1;++i)
	{
		k=i;
		for(j=i+1;j<n;++j)
		{
			if(strcmp(str[k],str[j])>0)
			{
				k = j;
			}
			if(k != i)
			{
				strcpy(tmp,str[i]);
				strcpy(str[i],str[k]);
				strcpy(str[k],tmp);
			}
		}
	}

	if((fp=fopen("D:\\1.txt","w"))==NULL)
	{
		printf("Can not openfile!\n");
		exit(0);
	}
	printf("The new sequence:\n");
	for(i=0;i<n;++i)
	{
		fputs(str[i],fp);
		fputs("\n",fp);
		printf("%s\n",str[i]);
	}
	fclose(fp);
}
*/
