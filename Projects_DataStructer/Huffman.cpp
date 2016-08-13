#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct HTNode
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;     //��̬��������洢�շ�����

typedef char **HuffmanCode;//��̬��������洢�շ��������

void mystrcpy(char *des,char *str)
{
	while(*str != '\0')
	{
		*des++ = *str++;
	}
	*des = '\0';
}

//s1,s2���ڱ��浱ǰHT���� Ȩֵ��С�����������±�
void Select(HuffmanTree &HT,int n,int &s1,int &s2)	
{
	int i ,j;
	for(i=1;i<=n;i++)
	{
		if( !HT[i].parent )  //һ���ҵ�����㲻Ϊ0�Ľ���ֹͣ
		{
			 s1 = i;       //��HT�е�һ�������Ϊ0���±긳��s1
			 break;
		}
	}
	for(j=i+1;j<=n;j++)    //j��i���¸���ʼ���Ҹ����Ϊ0���±�
	{
		if( !HT[j].parent )
		{
			s2 = j;      //��HT�еڶ��������Ϊ0���±긳��s2
			break;
		}
	}

	for(i=1;i<=n;i++)
	{
		if(HT[s1].weight>HT[i].weight && 
			HT[i].parent==0 && s2!=i )
		{
			s1 = i;   //���бȽϣ���Ȩֵ��С�����Ҳ�ͬ��s2�Ľ��
		}
	}

	for(j=1;j<=n;j++)
	{
		if(HT[s2].weight > HT[j].weight && 
			HT[j].parent==0 && s1!=j)
		{
			s2 = j;   //���бȽϣ���Ȩֵ��С�����Ҳ�ͬ��s1�Ľ��
		}
	}

	if(s1>s2)
	{
		int temp = s1;    //��Ȩֵ��С�Ľ�㸳��s1
		s1 = s2;
        s2 = temp;
	}
}

//---��Ҷ�ӵ���������ÿ���ַ��ĺշ�������---
void CreateHuffCode(HuffmanTree &HT, HuffmanCode &HC,int n)
{
	int start,f,i;
	char *cd;            //��ʱ����ַ�ÿ���ַ��ı���
	unsigned int c;

	HC = (HuffmanCode)malloc((n+1)*sizeof(char *)); //����n���ַ������ͷָ������
	cd = (char *)malloc(n*sizeof(char));           //���������Ĺ����ռ�
	cd[n-1] = '\0';                              //���������

	for(i=1;i<=n;++i) //����ַ���շ�������
	{
		start = n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)//��Ҷ�ӵ������������
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

		HC[i] = (char *)malloc((n-start)*sizeof(char)); //Ϊ��i���ַ��������ռ�
		mystrcpy(HC[i],&cd[start]);  //��cd���Ʊ��뵽HC
	}

	free(cd); 
}


void ShowHuff(HuffmanTree &HT,int n)//��ӡ�շ�����HT
{
	int m = 2*n-1;
	printf(" ���   weight  parent  lchild  rchild");
	for (int i=1; i<=m; i++)
	{
		printf("\n%4d%8d%8d%8d%8d",i,HT[i].weight,
		 HT[i].parent,HT[i].lchild, HT[i].rchild);
	}
}

void ShowHuffCode(HuffmanCode &HC,int *w,int n)//��ӡ�շ����HC
{
	printf("\n%d�����ĺշ�������:\n\n",n); 
	printf("���  Ȩֵ  ����\n");
	for(int i=1;i<=n;i++)
	{
		printf("%2d %6d:%6s\n",i,w[i-1],HC[i]);
	}
}

void CreateHuffman(HuffmanTree &HT,int *w,int n)//w���n������Ȩֵ,����շ�����HT
{
	int s1, s2;     //s1,s2���ڱ��浱ǰȨֵ��С����������±�
	int m = 2*n-1;  //n��Ҷ�ӽ�㹲��2n-1�����
	
	if(n <= 1)
	{
		return;
	}

	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode)); //�±��1��ʼ
	for(int i=1; i<=n; i++)   //��ʼ��ǰn��Ҷ�ӽ��
	{
		HT[i].weight = w[i-1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for(int i=n+1; i<=m; i++)   //��ʼ��Ҷ�ӽ��֮��Ŀհ׽��
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}

	printf("\n���������Ĺ������������ʾ��\n");
	printf("HT��̬:\n");
	ShowHuff(HT,n);

	for(int i=n+1; i<=m; i++)  //��ʼ���շ�����
	{ 	 
		Select(HT, i-1,s1,s2);// ��HT��ѡ��parentΪ0��weight��С����������±�
		HT[s1].parent = i; 
		HT[s2].parent = i;	
		HT[i].lchild = s1;
		HT[i].rchild = s2; 	 
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	 	
		printf("\nselect: s1=%d s2=%d\n", s1, s2);	//�鿴Select��ȡ���±�
		ShowHuff(HT,n);                          //����ʾ�µĺշ�����
	}
}

int main()
{
	HuffmanTree HT;   //�շ�����HT
	HuffmanCode HC;   //�շ�������HC
	int *w;          //���ÿ��Ҷ�ӽ��ֵ������(��Ȩֵ)
	int n;           //Ҷ�ӽ����
	int i;     

	printf("���������� "); 
	scanf_s("%d",&n); 

	w = (int *)malloc(n*sizeof(int));

	printf("����%d������Ȩֵ: ",n);
	for(i=0;i<n;i++)
	{
		scanf_s("%d",&w[i]);
	}

	CreateHuffman(HT,w,n);   //�����շ�����HT
	CreateHuffCode(HT,HC,n); //�����շ����HC
	ShowHuffCode(HC,w,n);    //��ӡ�շ����HC

	return 0;
}