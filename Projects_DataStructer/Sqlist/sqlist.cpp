#include <stdio.h>
#include <assert.h>
#include "sqlist.h"

void InitSqlist(Sqlist *list)
{
	assert(list != NULL);
	list->length = 0;
}

bool Insert(Sqlist*	list,int val,int index)//在下标index插入值val
{
	assert(list != NULL);
	if(index<0 || index>list->length || index>=MAX_SIZE)
	{
		return false;
	}
	
	for(int i=list->length-1;i>=index;--i)
	{
		list->elem[i+1] = list->elem[i];
	}

	list->elem[index] = val;
	list->length++;

	return true;
}

bool DeleteVal(Sqlist *list,int val,int index)
{
	assert(list != NULL);
	if(index<0 || index>list->length)
	{
		return false;
	}

	int i = Search(list,val,index);

	return DeleteIndex(list,i);
}

bool DeleteIndex(Sqlist*list,int index)
{
	if(index<0 || index>=list->length)
	{
		return false;
	}

	for(int i=index;i<list->length-1;++i)
	{
		list->elem[i] = list->elem[i+1];
	}

	list->length--;
	return true;
}

int  Search(Sqlist *list,int key,int index)//从下标index查找key，找到返回下标
{
	if(index<0 || index >= list->length)
	{
		return -1;
	}

	for(int i=index;i<list->length;++i)
	{
		if(list->elem[i] == key)
		{
			return i;
		}
	}

	return -1;
}

bool IsEmpty(Sqlist *list)
{
	return list->length == 0;
}

int GetLength(Sqlist *list)
{
	return list->length;
}

void Clear(Sqlist *list)
{
	list->length = 0;
}

void Destroy(Sqlist *list)
{
	Clear(list);
}

void Show(Sqlist *list)
{
	for(int i=0;i<list->length;++i)
	{
		printf("%d ",list->elem[i]);
	}
	printf("\n");
}

bool GetElem(Sqlist *list,int index,int *rtval)
{
	if(index<0 || index>=list->length)
	{
		return false;
	}

	*rtval = list->elem[index];
	return true;
}