#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <float.h>


//13.4通用类型数组排序
void Sort(void *an,int len ,int elemsize,int (*pcmp)(void*,void*))
{
	char *tmp = (char*)malloc(elemsize*sizeof(char));//作为交换两个值的中间临时变量
	assert(tmp != NULL);
	char *p1;
	char *p2;

	for(int i=0;i<len-1;++i)    
	{
		for(int j=0;j<len-i-1;++j)
		{
			p1 = (char*)an+elemsize*j;
			p2 = (char*)an+elemsize*(j+1);
			if(pcmp(p1,p2) > 0)
			{
				memcpy(tmp,p1,elemsize);
				memcpy(p1,p2,elemsize);
				memcpy(p2,tmp,elemsize);
			}
		}
	}
	free(tmp);
}
int Cmp_Int(void *p1,void *p2)
{
	return *(int *)p1-*(int *)p2;
}
int Cmp_Double(void *p1,void *p2)
{
	double diff = *(double*)p1 - *(double*)p2;
	if(diff<DBL_EPSILON && diff>-DBL_EPSILON)
	{
		return 0;
	}
	else if(diff>DBL_EPSILON)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

/*
#define DELTA    100 //数组大小

//11.2从标准输入读取一列有EOF结尾的整型值，并返回一个动态分配的数组
//数组第一个元素为整型值的个数
int *Readints()
{
	int size = DELTA;  //数组大小
	int count = 0;     //记录整型值个数
	int value;        //标准输入的值

	int *an = (int *)malloc( (size+1)*sizeof(int) );
	assert(an != NULL);

	while( (scanf("%d",&value)) == 1 ) //scanf报错
	{
		count++;
		if(count > size )
		{
			size += DELTA;
			an = (int *)realloc(an,(size+1)*sizeof(int) );
			assert(an != NULL);
		}
		an[count] = value;
	}

	if(count <size)//
	{
		an = (int *)realloc(an, (count+1)*sizeof(int) );
		assert(an != NULL);
	}

	an[0] = count;
	return an;
}
*/


//符号前移
int ChangStr(char *str)
{
	assert(str != NULL);
	char *p = NULL;  //p从后往前走，寻找*
	char *q = NULL;  //q标记需要交换的字符
	int count = 0;   //记录 * 符号的个数
	
	for(p=str;*p!='\0';p++)
	{}

	while( p > str)
	{
		if(*p == '*')
		{
			count++;
			for(q=p;q>=str;q--)
			{
				if(*q != '*')
				{
					break;
				}
				count++;
			}
			if(q < str)
			{
				return count-1;
			}
			
			char tmp = *p;
	        *p = *q;
	        *q = tmp;
		}
		p--;
	}

	return count;
}

int main()
{
/*	int arr[] = {4,7,1,2,0,67,90,34,12,66,87,13,57};
	Sort(arr,sizeof(arr)/sizeof(arr[0]),sizeof(arr[0]),Cmp_Int);
	int i;
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

	double brr[] = {12,34.5,67,78.99,23,34.449,132.1,345.67,345.6666669};
	Sort(brr,sizeof(brr)/sizeof(brr[0]),sizeof(brr[0]),Cmp_Double);
	for(i=0;i<sizeof(brr)/sizeof(brr[0]);i++)
	{
		printf("%lf ",brr[i]);
	}
	printf("\n");
*/ 

	/*
	int *an = Readints();
	int len = an[0];
	for(int i=0;i<=len;++i)
	{
		printf("%d ",an[i]);
	}
	printf("\n");
	*/

	
	char str1[] = "ab**cd**";
	char str2[] = "ab**cd";
	char str3[] = "**ab**cd**";
	char str4[] = "**ab**cd";
	char str5[] = "abcd";
	char str6[] = "****";

	ChangStr(str1);
	printf("%s\n",str1);
	printf("%d\n",ChangStr(str1));
	ChangStr(str2);
	printf("%s\n",str2);
	printf("%d\n",ChangStr(str2));
	ChangStr(str3);
	printf("%s\n",str3);
	printf("%d\n",ChangStr(str3));
	ChangStr(str4);
	printf("%s\n",str4);
	printf("%d\n",ChangStr(str4));
	ChangStr(str5);
	printf("%s\n",str5);
	printf("%d\n",ChangStr(str5));
	ChangStr(str6);
	printf("%s\n",str6);
	printf("%d\n",ChangStr(str6));
	

	return 0;
}
