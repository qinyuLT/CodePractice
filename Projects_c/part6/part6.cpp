#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>


//将数组中的数逆序重新存放
int Oppsite(int an[],int len)
{
	int tmp;
	int n = len;

	for(int i=0;i<n--;++i)
	{
		tmp   = an[i];
		an[i] = an[n];
		an[n] = tmp;
	}

	return an[len];
}

//10个整数排序(由小到大)[选择法]
void SelsctSort(int *a,int len)
{
	int indexMin = 0;  //记录最小值的下标
	int tmp;
	for(int i=0;i<len-1;++i)
	{
		indexMin = i;
		for(int j=i+1;j<len;++j)
		{
			if(a[indexMin]>a[j])
			{
				indexMin = j;
			}
		}
		if(indexMin != i)
		{
			tmp = a[i];
			a[i] = a[indexMin];
			a[indexMin] = tmp;
		}
	}
}
/*
int Sort(int *a,int len)
{
	int tmp;
	for(int i=0;i<len;++i)
	{
		for(int j=i+1;j<len;++j)
		{
			if(a[i]>a[j])
			{
			   tmp  = a[j];
		       a[j] = a[i];
		       a[i] = tmp;
			}	
	     }	
	}
	return a[len];
}
*/

//1到100内的素数 
void Showprime(int a)                      
{
	printf("%d\n",a);
}
void Isprime(int a[],int n )
{
	
	int i;                                  
	int j; 

	for(i=0;i<n;++i)                       
	{
		a[i] = i;
	}

	for(i=2;i<n;i++)                        
	{
		for(j=2;j<a[i] && a[i]%j != 0;++j);  
		{
			if(j == a[i])
			{
				Showprime(j);
			}
		}	
	}
}

//求一个3*3整型数组对角线之和
int ArrayAdd(int bn[][3])
{
	int sum = 0;

	for(int i=0;i<3;++i)
	{
		sum += bn[i][i]+bn[i][2-i];
	}

	return sum;
}

//把一个数组排号顺序后插入一个数
int ArrayInsert(int a[],int len,int digit)
{
	int end = a[len-2];     //倒数第二个值赋给end，最后一个值为空
	int tmp1;
	int tmp2;

	if(digit>end)
	{
		a[len-1] = digit;   
	}
	else
	{
		for(int i=0;i<len-1;++i)
		{
			if(a[i]>digit)
			{
				tmp1 = a[i];
				a[i] = digit;

				for(int j=i+1;j<len;++j)
				{
					tmp2 = a[j];
                    a[j] = tmp1;
                    tmp1 = tmp2;
				}
				break;
			}
		}
	}

	return a[len];
}



//输出“魔方阵”
void MagicSquare()
{
#define ROW 9       //必须为奇数
	int arr[ROW][ROW] = {0};
	assert(ROW %2 != 0);
	arr[0][ROW/2] = 1;
	int preRow = 0;
	int preCol = ROW/2;

	for(int i=2;i<=ROW*ROW;i++)
	{
		preRow = (preRow-1+ROW)%ROW;
		preCol = (preCol+1)%ROW;

		if(arr[preRow][preCol] != 0)
		{
			preRow = (preRow+1)%ROW;
			preCol = (preCol-1+ROW)%ROW; //把线性变成环形

			preRow = (preRow+1)%ROW;
		}

		arr[preRow][preCol] = i;
	}

	for(int i=0;i<ROW;i++)
	{
		for(int j=0;j<ROW;j++)
		{
			printf("%d  ",arr[i][j]);
		}
		printf("\n");
	}
#undef ROW
}


//显示数组
void ShowArray(int an[],int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%d ",an[i]);
	}

	printf("\n");
}

//杨辉三角赋值
int YanghuiTrigngle(int arr[][10],int row,int col)
{
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			arr[i][0] = 1;

			if(i==j)
			{
				arr[i][j] = 1;
			}

			else if(i<j)
			{
				arr[i][j] = 0;
			}

			else
			{
				arr[i][j] = arr[i-1][j-1]+arr[i-1][j];
			}
		}
	}

	return arr[10][10];
}
//显示杨辉三角
void ShowYH(int p[][10],int row,int col)
{
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			if(i<j)
			{
				printf(" ");
			}

			else
			{
				printf("%d ",p[i][j]);
			}	
		}

		printf("\n");
	}

	printf("\n");
}


//显示下面的图形
// *****
//  *****
//   *****
//    *****
//     *****

void Chart(int row,int col)
{ 
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<i;++j)
		{
			printf(" ");
		}

		for(int k=0;k<col;++k)
		{
			printf("*");
		}

		printf("\n");
	}

	printf("\n");
}

//连接两个字符串
char Mystrcat(char *str1,const char *str2)
{
	assert(str1 != NULL && str2 != NULL);

	for(int i=0;i<20;++i)
	{
		if(str1[i] == '\0')
		{
			for(int j=0;j<6;++j)
			{
				str1[i++] = str2[j];
			}
		}
	}

	return *str1;
}


//字符串的复制
char *Mystrcpy(char *str1,const char* str2)
{
	char *tmp = str1;
	assert(str1!=NULL && str2!=NULL);

	while(*str2 != '\0')
	{
		*str1++ = *str2++;
	}
	*str1 = '\0';

	return tmp;
}

//找出二维数组中的鞍点
int FindAn(int a[][3],int row,int col )
{
	int max;
	int i;
	int j; 

	for(i=0;i<row;++i)
	{
		for(j=0;j<col;++j)
		{
			max = a[i][j];
		}
		break;
	}
	
	if(max < a[i++][j])
	{
		//printf("%d\n",max);
		return max;
	}
	else
	{
		return -1;
	}
}

//在一个有序数组中查找一个数
int FindDigit(int a[],int len,int digit)
{
	for(int i=0;i<len;++i)
	{
		while(a[i]==digit)
		{
			return i+1;
		}
	}

	return -1;
}

// A->Z,a->z,B->Y,b->y....
char Password(char a[],int len)
{
	assert(a != NULL);

	for(int i=0;i<len;++i)
	{
		if( isupper(a[i]))            //判断a[i]是否为大写字母
		{
			//a[i] = 26-('a[i]'-64)+1+64;
			a[i] = 155-a[i];
		}
 		else if( islower(a[i]))       //判断a[i]是否为小写字母
		{
			//a[i] = 26-(a[i]-96 )+1+96;
			a[i] = 219-a[i];
		}
	}

	return a[len];
}

//字符串的比较
int Mystrcmy(const char *s1,const char *s2)
{
	int tmp = 0;
	assert(s1 != NULL && s2 != NULL);

	for(int i=0;i<20;++i)
	{
		if(s1[i] != s2[i])
		{
			tmp = s2[i]-s1[i];
			break;
		}
	}
	
	//printf("%d\n",tmp);
	return tmp;
}

int main()
{
	int a[100];
	int arr[10][10];
	char str1[20] = "Hello ";
	char str2[] = "world";
	char s1[] = "addbfbsb";
	char s2[] = "addbfbsc";
	char brr[] = {'A','B','C','a','b'};
	int an[] = {9,12,3,14,25,6,17,8,6,45};
	int bn[][3] = {{1,2,3},{4,5,6},{7,8,9}}; 
	int cn[10] = {11,22,33,44,55,66,77,88,99};
	int dn[] = {19,12,3,14,25,6,17,8,9,45,3,9};
	int en[] = {11,22,33,44,55,66,77,88,99};
	int len = sizeof(an)/sizeof(an[0]);    //求数组的长度
	
	Isprime(a,100);                       //1到100内的素数
	ArrayAdd(bn);                         //求一个3*3整型数组对角线之和
	Oppsite(an,len);                      //将数组中的数逆序重新存放
	ShowArray(an,len);
	YanghuiTrigngle(arr,10,10);            //杨辉三角
	ShowYH(arr,10,10);                    //显示杨辉三角
    Mystrcat(str1,str2);                  //连接两个字符串
	Mystrcpy(str1,str2);                  //字符串的复制
	Mystrcmy(s1,s2);                      //字符串的比较
    ArrayInsert(cn,10,1);                 //把一个数组排号顺序后插入一个数
	Chart(5,9);                          //显示图形
	//Sort(dn,10);                         //10个整数排序(由小到大)
	SelsctSort(dn,sizeof(dn)/sizeof(dn[0]));
	ShowArray(dn,sizeof(dn)/sizeof(dn[0]));
	FindAn(bn,3,3);                       //找出二维数组中的鞍点
	FindDigit(en,9,55);                   //在一个有序数组中查找一个数
	Password(brr,5);                      //A->Z,a->z,B->Y,b->y
	MagicSquare();                        //魔方阵

	for(int i=0;i<5;++i)
	{
		printf("%c ",brr[i]);
	}
	printf("\n");

	//ShowArray(cn,10);
	

	return 0;
}
