#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct HTNode
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;     //动态分配数组存储赫夫曼树

typedef char **HuffmanCode;//动态分配数组存储赫夫曼编码表

void mystrcpy(char *des,char *str)
{
	while(*str != '\0')
	{
		*des++ = *str++;
	}
	*des = '\0';
}

//s1,s2用于保存当前HT树中 权值最小的两个结点的下标
void Select(HuffmanTree &HT,int n,int &s1,int &s2)	
{
	int i ,j;
	for(i=1;i<=n;i++)
	{
		if( !HT[i].parent )  //一旦找到父结点不为0的结点就停止
		{
			 s1 = i;       //将HT中第一个父结点为0的下标赋给s1
			 break;
		}
	}
	for(j=i+1;j<=n;j++)    //j从i的下个开始查找父结点为0的下标
	{
		if( !HT[j].parent )
		{
			s2 = j;      //将HT中第二个父结点为0的下标赋给s2
			break;
		}
	}

	for(i=1;i<=n;i++)
	{
		if(HT[s1].weight>HT[i].weight && 
			HT[i].parent==0 && s2!=i )
		{
			s1 = i;   //进行比较，找权值最小，并且不同与s2的结点
		}
	}

	for(j=1;j<=n;j++)
	{
		if(HT[s2].weight > HT[j].weight && 
			HT[j].parent==0 && s1!=j)
		{
			s2 = j;   //进行比较，找权值最小，并且不同与s1的结点
		}
	}

	if(s1>s2)
	{
		int temp = s1;    //将权值最小的结点赋给s1
		s1 = s2;
        s2 = temp;
	}
}

//---从叶子到根逆向求每个字符的赫夫曼编码---
void CreateHuffCode(HuffmanTree &HT, HuffmanCode &HC,int n)
{
	int start,f,i;
	char *cd;            //暂时存放字符每个字符的编码
	unsigned int c;

	HC = (HuffmanCode)malloc((n+1)*sizeof(char *)); //分配n个字符编码的头指针向量
	cd = (char *)malloc(n*sizeof(char));           //分配求编码的工作空间
	cd[n-1] = '\0';                              //编码结束符

	for(i=1;i<=n;++i) //逐个字符求赫夫曼编码
	{
		start = n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)//从叶子到根逆向求编码
		{
			if(HT[f].lchild == c)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}	
		}

		HC[i] = (char *)malloc((n-start)*sizeof(char)); //为第i个字符编码分配空间
		mystrcpy(HC[i],&cd[start]);  //从cd复制编码到HC
	}

	free(cd); 
}


void ShowHuff(HuffmanTree &HT,int n)//打印赫夫曼树HT
{
	int m = 2*n-1;
	printf(" 结点   weight  parent  lchild  rchild");
	for (int i=1; i<=m; i++)
	{
		printf("\n%4d%8d%8d%8d%8d",i,HT[i].weight,
		 HT[i].parent,HT[i].lchild, HT[i].rchild);
	}
}

void ShowHuffCode(HuffmanCode &HC,int *w,int n)//打印赫夫编码HC
{
	printf("\n%d个结点的赫夫曼编码:\n\n",n); 
	printf("编号  权值  编码\n");
	for(int i=1;i<=n;i++)
	{
		printf("%2d %6d:%6s\n",i,w[i-1],HC[i]);
	}
}

void CreateHuffman(HuffmanTree &HT,int *w,int n)//w存放n个结点的权值,构造赫夫曼树HT
{
	int s1, s2;     //s1,s2用于保存当前权值最小的两个结点下标
	int m = 2*n-1;  //n个叶子结点共有2n-1个结点
	
	if(n <= 1)
	{
		return;
	}

	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode)); //下标从1开始
	for(int i=1; i<=n; i++)   //初始化前n个叶子结点
	{
		HT[i].weight = w[i-1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for(int i=n+1; i<=m; i++)   //初始化叶子结点之后的空白结点
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}

	printf("\n哈夫曼树的构造过程如下所示：\n");
	printf("HT初态:\n");
	ShowHuff(HT,n);

	for(int i=n+1; i<=m; i++)  //开始建赫夫曼树
	{ 	 
		Select(HT, i-1,s1,s2);// 在HT中选择parent为0且weight最小的两个结点下标
		HT[s1].parent = i; 
		HT[s2].parent = i;	
		HT[i].lchild = s1;
		HT[i].rchild = s2; 	 
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	 	
		printf("\nselect: s1=%d s2=%d\n", s1, s2);	//查看Select获取的下标
		ShowHuff(HT,n);                          //并显示新的赫夫曼树
	}
}

int main()
{
	HuffmanTree HT;   //赫夫曼树HT
	HuffmanCode HC;   //赫夫曼编码HC
	int *w;          //存放每个叶子结点值的数组(即权值)
	int n;           //叶子结点数
	int i;     

	printf("输入结点数： "); 
	scanf_s("%d",&n); 

	w = (int *)malloc(n*sizeof(int));

	printf("输入%d个结点的权值: ",n);
	for(i=0;i<n;i++)
	{
		scanf_s("%d",&w[i]);
	}

	CreateHuffman(HT,w,n);   //构建赫夫曼树HT
	CreateHuffCode(HT,HC,n); //构建赫夫编码HC
	ShowHuffCode(HC,w,n);    //打印赫夫编码HC

	return 0;
}