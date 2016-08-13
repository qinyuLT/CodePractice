#include <stdio.h>
#include <assert.h>
#include "sqlist.h"

int main()
{
	Sqlist list;

	InitSqlist(&list);

	for(int i=0;i<10;i++)
	{
		if(!Insert(&list,i,i))
		{
			printf("²åÈëÊ§°Ü\n");
		}
	}

	Show(&list);

	DeleteIndex(&list,0);
	Show(&list);
	printf("len=%d\n",GetLength(&list));

	DeleteVal(&list,5,5);
	Show(&list);

	int rtval;
	if(GetElem(&list,13,&rtval))
	{
		printf("%d\n",rtval);
	}

	return 0;
}