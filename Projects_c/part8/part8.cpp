#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vld.h>


/*
//3个整数由小到大排序
void Swap(int *p1,int *p2)  //两个数的交换函数
{
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void Sort_digit(int *p1,int *p2,int *p3)
{
	if(*p1>*p2)
	{
		Swap(p1,p2);
	}
	if(*p1>*p3)
	{
		Swap(p1,p3);
	}
	if(*p2>*p3)
	{
		Swap(p2,p3);
	}
}

int main()
{
	int a = 30;
	int b = 10;
	int c = 20;
	int *p1 = &a;
	int *p2 = &b;
	int *p3 = &c;

	Sort_digit(p1,p2,p3);
	printf("%d<%d<%d\n",a,b,c);
	//Swap(p1,p2);
	return 0;
}
*/


/*
//3个字符串，由小到大输出 
int Mystrcmp(char *str1,char *str2)    //字符串比较
{
	assert(str1!=NULL&& str2!=NULL);
	int tmp;

	while(0 == (tmp = *str1-*str2) && *str1 != '\0')
	{
		str1++;
		str2++;
	}

	return tmp;
}
void Swapstring(char *a,char *b)     //字符串的交换
{
	char c[20];
    strcpy(c,a);
    strcpy(a,b);
    strcpy(b,c);
}
void Sort_string(char *str1,char *str2,char *str3)
{
	if(Mystrcmp(str1,str2)>0)
	{
		Swapstring(str1,str2);
	}
	if(Mystrcmp(str1,str3)>0)
	{
		Swapstring(str1,str3);
	}
	if(Mystrcmp(str2,str3)>0)
	{
		Swapstring(str2,str3);
	}
}

int main()
{
	char str1[] = "acsd";
	char str2[] = "absd";
	char str3[] = "aasd";

	Sort_string(str1,str2,str3);

	printf("%s<%s<%s\n",str1,str2,str3);
	return 0;
}
*/

/*
//多个字符串从小到大排序
void Sort(char *an[],int len)
{
	char *tmp;
	int k = 0;

	for(int i=0;i<len-1;++i)
	{
		k=i; 
		for(int j=i+1;j<len;++j)
		{
			if( strcmp(an[k],an[j])>0 )
			{
				k=j;	
			}
		}
		if(k != i)
		{
			tmp = an[i];
		    an[i] = an[k];
		    an[k] = tmp;
		}	
	}
}
void Show(char *an[],int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%s\n",an[i]);
	}
}
int main()
{
	char *str[] = {"asdf","dgfh","wfv","asw","a","lij","aeec","fgn","edxv","gjf","bcv"};
	int len = sizeof(str)/sizeof(str[0]);
	
	Sort(str,len);
	Show(str,len);

	return 0;
}
*/

/*
//输入10个整数，将最小的与第一个对换，最大的与最后一个对换
int Find_indexMin(int *an,int len)//找到最小值的下标
{
	int indexMin = 0;          //记录最小值的下标

	for(int i=0;i<len;i++)
	{
		if(an[indexMin]>an[i])
		{
			indexMin =  i;
		}
	}
	return indexMin;
}

int Find_indexMax(int *an,int len)//找到最大值的下标
{
	int indexMax = 0;           //记录最大值的下标
	for(int i=0;i<len;i++)
	{
		if(an[indexMax]<an[i])
		{
			indexMax = i;
		}
	}
	return indexMax;
}

int *Exchange(int *an,int len)
{
	int *bn = an;
	int indexMin = Find_indexMin(an,len);
	int indexMax = Find_indexMax(an,len);
	int tmp;

	if(indexMin == len-1 && indexMax == 0)
	{
		tmp = an[0];
		an[0] = an[len-1];
		an[len-1] = tmp;
	}
	else 
	{
		if(indexMin != 0)
		{
			tmp = an[0];
		    an[0] = an[indexMin];
		    an[indexMin] = tmp;
		}
	
	    if(indexMax != len-1)
		{
			tmp = an[len-1];
		    an[len-1] = an[indexMax];
		    an[indexMax] = tmp;
		}
	}
	
	return bn;
}
void Show(int *an,int len)//显示数组
{
	for(int i=0;i<len;++i)
	{
		printf("%d ",an[i]);
	}
	printf("\n");
}

int main()
{
	//int an[] = {555,11,13,4,8,98,34,65,32,56,23,0};
	int an[] = {11,13,4,555,8,98,34,65,32,56,23,0};
	int len = sizeof(an)/sizeof(int);

	Find_indexMin(an,len);
	Find_indexMax(an,len);
	Exchange(an,len);
	Show(an,len);

	return 0;
}
*/


/*
//n个整数，使前面各数顺序向后移动m位
int *Move(int *an,int len,int m)
{
	int *bn = an;       //保存移动后的数组
	int n = len;
	int tmp;
	int q = len-m;      //an的前len-m项

	if(m == 0 || m == len) //m=0或len，表示不移动
	{
		return 0;
	}

	for(int i=0;i<=q--;++i)//逆置an的前len-m项
	{
		tmp = an[q];
		an[q] = an[i];
		an[i] = tmp;
	}

	q = len-m;
	for(int j=q;j<=n--;++j) //逆置an的后m项
	{
		tmp = an[n];
		an[n] = an[j];
		an[j] = tmp;
	}

	n = len;
	for(int k=0;k<n--;++k) //逆置移动后的an
	{
		tmp = an[k];
		an[k] = an[n];
		an[n] = tmp;
	}
	return bn;
}

void Show(int *an,int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%d ",an[i]);
	}
	printf("\n");
}

int main()
{
	int an[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int len = sizeof(an)/sizeof(an[0]);

	Show(an,len);     //显示移动前的数组
	//Move(an,len,0);  
	//Move(an,len,len);
	Move(an,len,5);
	Show(an,len);    //显示移动后的数组

	return 0;
}
*/


/*
//求字符串长度
int Mystrlen(const char *str)
{
	assert(str!=NULL);
	int strlen = 0;

	while(*str++ != '\0')
	{
		strlen++;
	}
	//printf("%d\n",strlen);
	return strlen;
}

int main()
{
	char str[] = "abcdefg";

	Mystrlen(str);
	return 0;
}
*/


/*
//字符串的复制，从第m个开始
void Mystrcpy(char *str1,char const *str2,int m)
{
	assert(str1!=NULL && str2!=NULL);
	str2 = str2 + m -1;           //指针指到第m个字符
	while(*str2 != '\0')
	{
		*str1++ = *str2++;
		//str1++;
		//str2++;
	}

	*str1 = '\0';
}

int main()
{
	char str1[20];
	char str2[] = "abcdefghijklmnopqrst";

	Mystrcpy(str1,str2,5);
	printf("%s\n",str1);
	return 0;
}
*/


//n人从1到3排序，剔除是3的人，问最后剩下的是第几个人
int *Reject(int n)  //报数到3的人踢掉
{
	int *q =(int *)malloc(sizeof(int)*n);
	assert(q != NULL);
	
	int i = 0;
	int m = 0;    //被置剔除的人的个数
	int k = 0;
	int num = 0;
	for(i=0;i<n;++i)
	{
		q[i] = i+1;
	}
	while (m < n-1)//最后只剩一个人
	{
		if (*(q+(i+n)%n) != 0)
		{
			k++;      //记录报数1,2,3	
		}
		if (k ==3)
		{
			*(q+(i+n)%n) = 0;
			k = 0;   //重新计数
			m++;     //被置为0的人的个数
		}
		i++;
	}
	return q;
}
int main()
{
	int n = 10;    //总人数

	int *an = Reject(n);
	for(int i=0;i<n;++i)
	{
		if(an[i] != 0)
		{
			printf("%d人最后剩下的是第 %d 个人\n",n,i+1);
		}
	}
	free(an);
	return 0;
}


/*
//求字符串中大写字母，小写字母，数字，空格，其他字符数
int *Stastistics(char str[], int n)        
{
	int *an = (int *)malloc(sizeof(int)*5); //an保存个数
	assert(an != NULL);

	int digit = 0;         //数字个数
	int letter_big  = 0;   //大写字母个数
	int letter_lit  = 0;   //小写字母个数
	int space = 0;         //空格个数
	int other = 0;         //其他字符个数

	for(int i=0; i<n-1; ++i)
	{
		if( isdigit(str[i]) )
		{
			 an[0] = digit++;
		}

		else if( isupper(str[i]) ) 
		{
			an[1] = letter_big++;
		}
		else if( islower(str[i]) ) 
		{
			an[2] = letter_lit++;
		}
		
		else if(' ' == str[i])
		{
			an[3] = space++;
		}

		else
		{
			an[4] = other++;
		}
	}

	return an;
}

int main()
{
	char str[] = "SF s43ds 12 4F%F $%^&";
    int len = sizeof(str)/sizeof(str[0]);

	int *q = Stastistics(str,len);
	for(int i=0;i<5;++i)
	{
		printf("%d ",q[i]);
	}
	printf("\n");
	free(q);
	return 0;
}
*/


/*
//3*3数组逆置
int	Oppsite(int (*an)[3],int row,int col,int (*bn)[3])
{
	for(int i=0;i<row;++i)
	{
	    for(int j=0;j<col;++j)
		{
			bn[j][i] = an[i][j];
		}
	}

	return bn[col][row];
}
void Show(int an[][3],int row,int col)
{
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			printf("%d ",an[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int main()
{
	int an[][3] = {1,2,3,4,5,6,7,8,9};
	int bn[3][3];

	Oppsite(an,3,3,bn);
	Show(an,3,3);
	Show(bn,3,3);

	return 0;
}
*/


/*
//对n个整数排序
void SelectSort(int *arr,int len)
{
	int indexMin = 0; //最小值的下标
	int tmp;
	for(int i=0;i<len-1;i++)
	{
		indexMin = i;
		for(int j=i+1;j<len;j++)
		{
			if(arr[indexMin] > arr[j])
			{
				indexMin = j;
			}
		}
		if(indexMin != i)
		{
			tmp = arr[i];
			arr[i] = arr[indexMin];
			arr[indexMin] = tmp;
		}
	}
}
void Show(int *an,int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%d ",an[i]);
	}
	printf("\n");
}

int main()
{
	int an[] = {23,54,11,98,65,34,90,55,3,11};
	int len = sizeof(an)/sizeof(an[0]);

	SelectSort(an,len);
	Show(an,len);

	return 0;
}
*/


/*
//输入的整数逆序输出
void Oppsite(int *an,int len)
{
	int n = len;
	int tmp;

	for(int i=0;i<n--;++i)
	{
		tmp = an[i];
	   an[i] = an[n];
	   an[n] = tmp;
	}
}
void Show(int *an,int len)
{
	for(int i=0;i<len;++i)
	{
		printf("%d ",an[i]);
	}
	printf("\n");
}

int main()
{
	int an[] = {23,54,11,98,65,34,90,55,3,11};
	int len = sizeof(an)/sizeof(an[0]);

	Show(an,len);
	Oppsite(an,len);
	Show(an,len);

	return 0;
}
*/

/*
//输入数字，显示英文月份
char *Translate(int q)
{
	char *month[] = {"January","February","March","April","May","June","July",
		 "August","September","October","November","December","Error Month"};
	if(q == 0 || q > 12)
	{
		return month[12];
	}
	else
	{
		return month[q-1];
	}	
}
int main()
{
	char *q = Translate(11);
	printf("%s\n",q);

	return 0;
}
*/

/*
//new(n),开辟存储空间并释
char *New(int n)
{
	char *str =(char *)malloc(n);

	return str;
}
int main()
{
	char *q = New(4);
	free(q);
	return 0;
}
*/



/*
//统计一个字符串中的数字
int *Digit_string(char *str,int len,int *an)
{
	int j = 0;
	int tmp = 0;

	for(int i=0;i<len;++i)
	{
		while(isdigit(str[i]))       //判断str[i]是否为数字
		{
			tmp = tmp*10+str[i]-'0'; //字符数字转换为数字
			i++;
			if( !isdigit(str[i]) )
			{
				an[j] = tmp;       //把数字存放在数组里
				tmp = 0;
				j++;
			}
		}
	}

	for(int k=0;k<j;++k)
	{
		printf("%d ",an[k]);      //显示字符串中的数字
	}
	printf("\n");

	return an;
}

int main()
{
	char str[] =  "asd12 3d45 6j7m67n89 32a43";
	int strlen = sizeof(str)/sizeof(str[0]);
	int an[20];

	Digit_string(str,strlen,an);
	return 0;
}

*/

/*
typedef struct Student 
{
	char number[20];
	char name[20];
	float score[5];    //5门课程的成绩
}Student;
  //求第一门课程的平均成绩
float Average_first(Student *s1,Student *s2,Student *s3)
{
	float average = (s1->score[0]+s2->score[0]+s3->score[0])/3;

	return average;
}
  //找出两门以上不及格的同学
void Fail(Student *s1,Student *s2,Student *s3)
{
	int s1_f = 0;  //记录学生不及格的科目
	int s2_f = 0;  
	int s3_f = 0;

	for(int i=0;i<5;++i)
	{
		if(s1->score[i]<60)
		{
			s1_f++;
		}
		if(s2->score[i]<60)
		{
			s2_f++;
		}
		if(s3->score[i]<60)
		{
			s3_f++;
		}
	}
	if(s1_f>=2)
	{
		printf("%s  %s\n",s1->name,s1->number);
	}
	if(s2_f>=2)
	{
		printf("%s  %s\n",s2->name,s2->number);
	}
	if(s3_f>=2)
	{
		printf("%s  %s\n",s3->name,s3->number);
	}
}
//求每个学生的平均成绩
float Average(Student *st)
{
	float sum = 0;
	for(int i=0;i<5;++i)
	{
		sum += st->score[i];
	}
	printf("%f\n",sum/5);
	return sum/5;
}
//找出平均分在85分以上或者每门都在90分以上的学生
void Find(Student *s1,Student *s2,Student *s3)
{
	if(Average(s1)>=85)
	{
		printf("%s  %s\n",s1->name,s1->number);
	}
	if(Average(s2)>=85)
	{
		printf("%s  %s\n",s2->name,s2->number);
	}
	if(Average(s3)>=85)
	{
		printf("%s  %s\n",s3->name,s3->number);
	}
}

int main()
{
	Student std1 = {{"000001"},{"zhangfei"},{48,46,55,63,55}};
	Student std2 = {{"000002"},{"caocao"},{98,96,95,93,95}};
	Student std3 = {{"000003"},{"liubei"},{89,69,59,79,59}};
	

	Average_first(&std1,&std2,&std3);
	printf("%f\n",Average_first(&std1,&std2,&std3));
	Average(&std1);
	Average(&std2);
	Average(&std3);
	Fail(&std1,&std2,&std3);
    Find(&std1,&std2,&std3);

	return 0;
}
*/

