#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//极大值用于生成Huffman树
#define MAXSIZE 100000000
//用于生成相应叶子节点Huffman编码的二维字符数组
typedef char* HCode;

//Huffman树节点
typedef struct node
{
	int weight;
	int data;
	int parent, lchild, rchild;
}Node;

//count 叶子节点数的计算  sum_bit 记录被压缩文件编码后的编码总长度
int sum_bit, count;
//Huffman叶子节点，最多不过256个（以字节为单位）
Node huffmanNode[260];
//解压缩的时候记录每次读取到编码（0....1..）
int num[8];
//对应词频信息表的信息，用ASCII值表示
int code[260];
//二维字符数组
HCode *HC;

//统计词频时用于查找是否已经记录过,记录过的话返回下标，没有则返回0
int isInNode(int value)
{
	int i = 1;
	for (; i <= count; i++)
	{
		if (huffmanNode[i].data == value)
		{
			return i;
		}
	}
	return 0;
}

//获取文件词频，记录在Node huffmanNode[260]的节点数组当中
void  calWeight(char *file)
{
	count = 0;
	FILE *f;
	int a;
	//以二进制方式打开文件，为了读取到换行符
	f = fopen(file, "rb");
	if (f == NULL)
	{
		printf("文件不存在！打开失败！");
		return;
	}
	while (!feof(f))
	{
		a = fgetc(f);
		if (a == EOF) break;
		if (!isInNode(a))  //count从1开始计数
		{
			count++;
			huffmanNode[count].weight = 1;
			huffmanNode[count].data = a;
		}
		else
		{
			int i = isInNode(a);
			huffmanNode[i].weight++;
		}
	}
	fclose(f);
}

/*得到待压缩文件的总字节数，权值为几就代表着有多少个字节*/
int getSumBytes()
{
	int i = 1;
	int result = 0;
	for (; i <= count; i++)
	{
		result += huffmanNode[i].weight;
	}
	return result;
}

//获取压缩后文件的总bit数
int getSumBits()
{
	int i = 1;
	int result = 0;
	for (; i <= count; i++)
	{
		result += huffmanNode[i].weight * strlen(HC[i]);
	}
	return result;
}

//建立huffman树 根据huffman树的特性,具有n个节点的huffman树的具有2n-1个节点
//n值由全局变量count值来确定，该函数主要用来初始化Huffman树的所有节点信息
void  createHufmanTree(Node * huffmanTree)
{
	int m = 2 * count - 1;
	int m1, m2, x1, x2, i, j;
	//初始化结点信息，从1--count这count个节点信息为叶子节点的信息
	for (i = 1; i <= count; i++)
	{

		huffmanTree[i].data = huffmanNode[i].data;
		huffmanTree[i].lchild = -1;
		huffmanTree[i].rchild = -1;
		huffmanTree[i].parent = -1;
		huffmanTree[i].weight = huffmanNode[i].weight;
	}
	//从count---2*count-1这些节点首先初始化为空
	for (; i <= m; i++)
	{
		huffmanTree[i].data = 0;    huffmanTree[i].weight = 0;
		huffmanTree[i].lchild = -1; huffmanTree[i].rchild = -1;
		huffmanTree[i].parent = -1;
	}
	//构造huffman树，按照huffman树构建原理
	for (i = count + 1; i <= m; i++)
	{
		/*m2,m1分别存储倒数第二小的权值和倒数第一小的权值
		x2,x1分别存储倒数第二小的下标和倒数第一小的下标*/
		m1 = m2 = MAXSIZE;
		x1 = x2 = 0;
		for (j = 1; j<i; j++)
		{
			if (huffmanTree[j].parent == -1 && huffmanTree[j].weight <m1)
			{
				m2 = m1;                    x2 = x1;
				m1 = huffmanTree[j].weight; x1 = j;
			}
			else if (huffmanTree[j].parent == -1 && huffmanTree[j].weight<m2)
			{
				m2 = huffmanTree[j].weight;
				x2 = j;
			}

		}
		/*合并成一颗新的树*/
		huffmanTree[x1].parent = i; huffmanTree[x2].parent = i;
		huffmanTree[i].lchild = x1; huffmanTree[i].rchild = x2;
		huffmanTree[i].weight = m1 + m2;
	}
}

/*字符编码，从构建好的Huffman树当中读取每个叶子节点的huffman编码，并将叶子节点的信息放入到code[]中*/
HCode * getHuffmanCode(Node * huffmanTree, HCode *HC, int code[])
{
	int i = 1, c, start, f;
	//构造了字符编码的字符数组共有count+1个 通过读取一个复制一个的方式完成编码获取

	char * cd = (char *)malloc((count + 1)*sizeof(char));
	//还是这个问题的
	cd[count] = '\0';
	for (; i <= count; i++)
	{
		start = count;
		for (c = i, f = huffmanTree[i].parent; f != -1; c = f, f = huffmanTree[f].parent)
		{
			if (huffmanTree[f].lchild == c)  cd[--start] = '0';
			else cd[--start] = '1';
		}
		//为每个字符数组分配相应的数量 由于范围的问题要仔细考虑的
		HC[i] = (char *)malloc((count + 1 - start)*sizeof(char));
		//参数均为char *
		strcpy(HC[i], &cd[start]);
		code[i] = huffmanTree[i].data;
	}
	return HC;
}
/*
将编码表写入默认文件当中,并在结尾存入叶子节点数（count）与压缩后文件的总bit数
1111000  27
...........
...........
#sum_bit##count#
*/
void freToFile(int code[], HCode *HC)
{
	int i;
	//打开默认文件
	FILE *fe = fopen("C:\\dic.txt", "wb");
	//将编码信息和叶子节点信息写入词典
	for (i = 1; i <= count; i++)
	{
		fprintf(fe, "%s %d\n", HC[i], code[i]);
	}
	char c = '#';
	//写入sum_bit
	fprintf(fe, "%c", c);
	fprintf(fe, "%d", getSumBits());
	fprintf(fe, "%c", c);
	//写入count
	fprintf(fe, "%c", c);
	fprintf(fe, "%d", count);
	fprintf(fe, "%c", c);

	fclose(fe);
}

//由于词频表是按照字符串方式存储的叶子节点信息,读取出来的字符串需要转换成int值再使用
//其中需要使用pow函数，由于pow函数有精度损失，自己写了一个使用
int powmy(int a, int b)
{
	if (b == 0) return 1;
	int i = 0;
	int result = 1;
	for (; i<b; i++)
	{
		result *= a;
	}
	return result;
}

/*从编码表文件读取相应信息以用来解压文件，读取信息包括编码和叶子信息*/
HCode* freFromFile(int code[], HCode *HC)
{
	int i;
	FILE *fe = fopen("C:\\dic.txt", "rb");
	if (fe == NULL)
	{
		printf("词典文件不存在！");
		return NULL;
	}
	int k;
	int num[10];
	int m;
	int flag = 0;
	char * cd = (char *)malloc((256 + 1)*sizeof(char));
	//读取一个字节
	char c = fgetc(fe);
	for (i = 1; flag != 1; i++)
	{
		//如果读取到#号键，就跳出循环，继续读取sum_bit和count值
		if (c == '#') break;
		//每一行的读取直到读到空格，然后就完成了一条huffman编码的读取
		int j = 0;
		while (c != ' ')
		{
			cd[j++] = c;
			c = fgetc(fe);
		}
		cd[j] = '\0';

		//将读取到的huffman编码存入相应的二维字符数组当中去
		HC[i] = (char *)malloc((j + 1)*sizeof(char));
		strcpy(HC[i], &cd[0]);
		//下面直到读取到空格键为止，读取huffman叶子节点信息，读取到的是字符，需要转换成int值
		c = fgetc(fe);

		k = 0;
		while (c != '\n')
		{
			num[k++] = c - '0';
			c = fgetc(fe);
		}
		code[i] = 0;
		m = 0;
		//转换成int值，存入code[]数组当中
		for (k = k - 1; k >= 0; k--)
		{
			code[i] += num[k] * powmy(10, m);
			m++;
		}
		//继续向下读取
		c = fgetc(fe);
	}
	//获取压缩文件的总bit数，以用来判断最后一次读取的是不是足够8位
	c = fgetc(fe);
	k = 0;
	while (c != '#')
	{
		num[k++] = c - '0';
		c = fgetc(fe);
	}
	//同样将读取到的char转换成int
	m = 0;
	sum_bit = 0;
	for (k = k - 1; k >= 0; k--)
	{
		sum_bit += (num[k] * powmy(10, m));
		m = m + 1;
	}

	c = fgetc(fe);  c = fgetc(fe);//头一个读取#，后一个才开始读取数据
	k = 0;
	while (c != '#')
	{
		num[k++] = c - '0';
		c = fgetc(fe);
	}
	//将读取到的char转换成int
	m = 0;  count = 0;
	for (k = k - 1; k >= 0; k--)
	{
		count += num[k] * (int)pow(10.0, m);
		m++;
	}
	fclose(fe);
	return HC;
}

/*压缩文件*/
void compress_file(char* file1, char*file2)
{
	int i, sum = 0, flag = 0, j, k = 0;
	//数组开设的不够大是最后的一个bug的成因，因为有可能这个Huffman编码很长很长
	int eight[1000];
	memset(eight, 0, 1000 * sizeof(int));
	FILE *fo = fopen(file1, "rb");
	FILE *fw = fopen(file2, "wb");
	if (fo == NULL || fw == NULL)
	{
		printf("文件读取失败！");
		return;
	}
	//统计已经压缩的字节总数，用于计算压缩百分比
	int aa = 0;
	int sum_bytes = getSumBytes();
	while (!feof(fo))
	{
		sum = 0;
		int a = fgetc(fo);
		//每次读取一个字节就+1
		aa++;
		//读取了一个字节之后就与编码表进行比较，查找对应的编码
		for (i = 1; i <= count; i++)
		{
			if (code[i] == a)
			{
				//flag作为计数器，当凑够8位之后就作为一个字节写入压缩文件
				flag += strlen(HC[i]);
				int len = strlen(HC[i]);
				//flag 小于8的时候继续累加，直到凑够8个
				if (flag<8)
				{
					for (j = 0; j<len; j++)
						eight[k++] = HC[i][j] - '0';/*我们存储的是字符串，是多少就是多少*/
				}
				//当flag>=8的时候，将8位写进压缩文件，同时将剩余的没有写入的huffman编码重新移到
				//eight【】数组前面去，同时修改flag
				else if (flag >= 8)
				{
					//将匹配到的huffman编码写进8位数组，直到k值为8，k值始终代表现在eight【】数组的长度
					for (j = 0; k<8; j++)
						eight[k++] = HC[i][j] - '0';
					//将匹配到的huffman编码的没有完全写进去的添加到后面。
					for (; j<len; j++)
						eight[k++] = HC[i][j] - '0';
					//计算8位对应的int值，写入文件
					sum += eight[0] * 128 + eight[1] * 64 + eight[2] * 32 + eight[3] * 16 + eight[4] * 8
						+ eight[5] * 4 + eight[6] * 2 + eight[7] * 1;
					//前8为置0
					for (j = 0; j<8; j++)
						eight[j] = 0;
					//将后面的移植到前面去
					for (j = 8; j<k; j++)
						eight[j - 8] = eight[j];
					//重置flag与k
					k = flag = j - 8;
					//写进文件
					char c = sum;
					fputc(c, fw);

					if (aa % 1000 == 0)
					{
						printf("\r正在进行压缩，请稍等……%6.2f%%", (double)aa / sum_bytes*100.0);
					}
					fflush(fw);
					i = count + 1;
				}
			}
		}
	}
	aa = sum_bytes;
	printf("\r正在进行压缩，请稍等……%6.2f%%", (double)aa / sum_bytes*100.0);
	printf("压缩成功！");
	/*考虑到最后可能没有凑够八位的情况*/
	if (flag)
	{
		sum += eight[0] * 128 + eight[1] * 64 + eight[2] * 32 + eight[3] * 16 + eight[4] * 8
			+ eight[5] * 4 + eight[6] * 2 + eight[7] * 1;
		char c = sum;
		fputc(c, fw);
		sum_bit += flag;
		fflush(fw);
	}
	fclose(fw);
	fclose(fo);
}

/*用于在解压的时候将读取到的ASCII码转换为二进制数*/
int  swap(int data)
{
	int i = 0;
	while (data)
	{
		num[i++] = data % 2;
		data = data / 2;
	}
	return i;
}

/*进行文件的解压*/
void uncompress_file(char* file1, char* file2)
{

	FILE *fo = fopen(file1, "rb");
	FILE *fw = fopen(file2, "wb");
	if (fo == NULL || fw == NULL)
	{
		printf("文件打开失败！");
		return;
	}
	char str[1000];
	int i, j, k, temp = 0;
	int index;
	int sum_bit2 = sum_bit;
	//直到读取到文件结尾
	while (!feof(fo))
	{
		if (sum_bit2<0) break;
		//读取一次，减去8位
		sum_bit2 -= 8;
		int data = fgetc(fo);
		if (data == -1) break;
		//index用来在sum_bit2小于0的时候设置读取为位数（也就是说最后不用读取8位了）
		if (sum_bit2<0)
		{
			index = 0 - sum_bit2;
		}
		else
		{
			index = 0;
		}
		if (data == -1) break;
		memset(num, 0, sizeof(num));
		//将读取到的data转换成二进制数
		swap(data);
		i = temp;
		//将转换后的二进制数变为字符串，注意顺序
		//是一位一位的往里面填，填进去一位立即进行比较，当找到相应的信息就调出来
		for (k = 7; k >= index; i++, k--)
		{
			if (num[k])
				str[i] = '1';
			else
				str[i] = '0';

			str[i + 1] = '\0';
			//查找编码表当中与该字符串（编码）相同的信息，然后将叶子信息写入解压文件
			for (j = 1; j <= count; j++)
			{
				if (strcmp(str, HC[j]) == 0)
				{
					//将叶子信息写入到文件（写入的是int值，是该int值表示的字符）
					fputc(code[j], fw);
					if ((sum_bit - sum_bit2) % 1500 == 0)
					{
						printf("\r文件正在解压中,请耐心等待……%6.2f%%", (double)(sum_bit - sum_bit2) / sum_bit*100.0);
					}

					fflush(fw);
					j = count + 1;
					i = -1;
				}
			}
		}
		if (i)
		{
			temp = i;
		}
		else
		{
			temp = 0;
		}
	}
	sum_bit2 = 0;
	printf("\r文件正在解压中,请耐心等待……%6.2f%%", (double)(sum_bit - sum_bit2) / sum_bit*100.0);
	printf("解压成功！");
	fclose(fw);
	fclose(fo);
}

int main(int argc, char **argv)
{
	if (strcmp(argv[1], "-c") == 0)
	{
		//获取文件的词频
		calWeight(argv[2]);
		//申请Huffman树的内存，已经获得叶子节点数，根据节点总数与叶子节点数的关系分配内存
		Node *huffmanTree = (Node *)malloc((2 * count - 1 + 1)*sizeof(Node));
		//创建Huffman树
		createHufmanTree(huffmanTree);
		//为Huffman编码表申请一个二维的字符数组指针
		HC = (HCode *)malloc((count + 1)*sizeof(HCode));
		//向指针赋值，getHuffmanCode()函数返回编码��
		HC = getHuffmanCode(huffmanTree, HC, code);
		//根据编码表HC和编码对应的data表code压缩文件
		compress_file(argv[2], argv[3]);
		//将编码存入到默认的编码表当中（C:\\dic.txt）
		freToFile(code, HC);
	}
	else if (strcmp(argv[1], "-u") == 0)
	{
		//为编码表分配内存，由于不知道叶子节点数，分配257
		HC = (HCode *)malloc(257 * sizeof(HCode));
		//从词频表当中获取编码
		HC = freFromFile(code, HC);
		//根据编码表和data表解压文件
		uncompress_file(argv[2], argv[3]);
	}
	return 0;
}