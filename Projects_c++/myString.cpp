#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define SIZE  100
int g_next[SIZE];

//bool Replace(String *pstr, String*t, String *v, int pos);//将pos开始的第一个t替换成v
//bool ReplaceAll(String *pstr, String *t, String*v);//将所有的t替换成v
//bool Insert(String *pstr, int pos, String *t);//在pstr的pos位置处插入t
//bool Delete(String *pstr, int pos, int len);//在pos处删除长度为len的字符

typedef struct String
{
	char elem[SIZE];//字符不包含'\0'
	int length;//字符有效长度
}String;

//"abc"
void StrAssign(String *pstr, const char *cstr)
{
	assert(pstr != NULL && cstr != NULL);
	int i = 0;
	while (*cstr != '\0')
	{
		pstr->elem[i++] = *cstr++;
	}
	pstr->length = i;
}

void StrCpy(String *pstr1, String *pstr2)
{
	assert(pstr1 != NULL && pstr2 != NULL);
	for (int i = 0; i < pstr2->length; ++i)
	{
		pstr1->elem[i] = pstr2->elem[i];
	}
	pstr1->length = pstr2->length;
}

//psub = pstr[pos...pos+len]
bool SubString(String *psub, String *pstr, int pos, int len)
{
	if (pos<0 || pos + len>pstr->length)
	{
		return false;
	}
	for (int i = 0; i < len; ++i)
	{
		psub->elem[i] = pstr->elem[i + pos];
	}
	psub->length = len;
	return true;
}

int BF(String *pstr, String *psub, int pos)
{
	if (pos<0 || pos >= pstr->length)
	{
		return -1;
	}
	int i = pos;//主串下标
	int j = 0;//子串下标
	while (i < pstr->length && j < psub->length)
	{
		if (pstr->elem[i++] == psub->elem[j++]);
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}

	if (j >= psub->length)
	{
		return i - j;
	}
	return -1;
}

void GetNext(String *pstr, int *next)
{
	next[0] = next[1] = 0;
	int len = pstr->length;

	int i = 1;
	int j = 0;
	while (i < len)
	{
		if (pstr->elem[i] == pstr->elem[j])
		{
			next[++i] = ++j;
		}
		else if (j == 0)
		{
			next[++i] = 0;
		}
		else
		{
			j = next[j];
		}
	}
}

int KMP(String *pstr, String *psub, int pos)
{
	int *next = g_next;//用next指向全局数组
	GetNext(pstr, next);
	
	int i = pos;
	int j = 0;
	while (i < pstr->length && j < psub->length)
	{
		if (pstr->elem[i] == psub->elem[j])
		{
			i++;
			j++;
		}
		else if (j == 0)
		{
			i++;
		}
		else
		{
			j = next[j];
		}
	}
	
	int a = -1;
	if (j >= psub->length)
	{
		a =  i - j;
	}

	memset(g_next, 0, SIZE);//把全局数组清空
	return a;
}

bool Delete(String *pstr, int pos, int len);//在pos处删除长度为len的字符
bool Insert(String *pstr, int pos, String *t);
bool Replace(String *pstr, String *t, String *v, int pos)//将pos开始的第一个t替换成v
{
	if (pos<0 || pos>pstr->length || pstr->length-t->length+v->length > SIZE)
	{
		return false;
	}
	int index = KMP(pstr, t, pos);
	if (index < 0)
	{
		return false;
	}
	Delete(pstr, index, t->length);//删除t
	return Insert(pstr, index, v);
}

bool ReplaceAll(String *pstr, String *t, String*v)//将所有的t替换成v
{
	while (Replace(pstr, t, v, 0))
	{
		;
	}
	return true;
}

bool Insert(String *pstr, int pos, String *t)//在pstr的pos位置处插入t
{
	if (pos<0 || pos>pstr->length || pos + t->length > SIZE)
	{
		return false;
	}
	int i;
	int len = t->length;
	for (i = 0; i < pstr->length; ++i)
	{
		pstr->elem[pstr->length - 1 + len - i] =
		pstr->elem[pstr->length - 1 - i];
	}
	for (i = 0; i < len; ++i)
	{
		pstr->elem[pos + i] = t->elem[i];
	}
	pstr->length += len;
	return true;
}
bool Delete(String *pstr, int pos, int len)//在pos处删除长度为len的字符
{
	if (pos<0 || pos + len>pstr->length)
	{
		return false;
	}
	for (int i = 0; i<pstr->length - pos - len; i++)
	{
		pstr->elem[pos + i] = pstr->elem[pos + i + len];
	}
	pstr->length -= len;
	return true;
}

void Destroy(String *pstr)
{
	pstr->length = 0;
}

void Show(String *pstr)
{
	if (pstr == NULL)
	{
		return;
	}
	for (int i = 0; i < pstr->length; ++i)
	{
		printf("%c", pstr->elem[i]);
	}
	printf("\n");
}

int main11()
{
	String str1;
	String str2;
	String str3;
	StrAssign(&str1, "abcabcdabcde");
	StrAssign(&str2, "ab");
	StrAssign(&str3, "hhh");

	int pos = BF(&str1, &str2, 8);
	printf("%d\n", pos);

	Show(&str1);
	Delete(&str1, 1, 3);
	Show(&str1);
	Show(&str2);

	Insert(&str1, 5, &str2);
	Show(&str1);

	//Replace(&str1,&str2,&str3,0);
	ReplaceAll(&str1, &str2, &str3);
	Show(&str1);
	return 0;
}

int main1()
{
	String s1;
	String s2;

	StrAssign(&s1,"abcaabbcabcaabdab");
	StrAssign(&s2, "ab");
	Show(&s1);
	Show(&s2);

	int pos = 1;
	cout << KMP(&s1, &s2, pos) << endl;
	cout << BF(&s1, &s2, pos) << endl;



	return 0;
}