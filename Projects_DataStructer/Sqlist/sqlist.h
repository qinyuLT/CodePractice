#pragma once

#define MAX_SIZE  8

typedef struct Sqlist
{
	int elem[MAX_SIZE];
	int length; //顺序表中有效数字个数

}Sqlist;

void InitSqlist(Sqlist *list);

bool Insert(Sqlist*	list,int val,int index);

bool DeleteVal(Sqlist *list,int val,int index);

bool DeleteIndex(Sqlist*list,int index);

int  Search(Sqlist *list,int key,int index);

bool IsEmpty(Sqlist *list);

int GetLength(Sqlist *list);

void Clear(Sqlist *list);

void Destroy(Sqlist *list);

void Show(Sqlist *list);

bool GetElem(Sqlist *list,int index,int *rtval);