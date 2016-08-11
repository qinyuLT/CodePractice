#include <stdio.h>

//8.1一个数组的声明

//8.3判断一个矩阵是否为单位矩阵
bool IdentityMatrix(int (*an)[3],int row,int col )
{
	if(row != col)    //判断行和列是否相等
	{
		return false;
	}

	for(int i=0;i<row;++i)//判断对角线元素是否为1
	{
		if(an[i][i] != 1)
		{
			return false;
		}
	}

	for(int i=0;i<row;++i) //判断除了对角线元素外是否为0
	{
		for(int j=0;j<i;++j)
		{
			if(an[i][j] != 0)
			{
				return false;
			}
		}
		for(int j=0;j>i;++j)
		{
			if(an[i][j] != 0)
			{
				return false;
			}
		}
	}
	
	return true;
}

//8.5两个矩阵相乘
void MatrixMultiply(int *m1,int *m2,int *r,int x,int y,int z)
{
	int *m1p;
	int *m2p;
	
	for(int i=0;i<x;++i)
	{
		for(int j=0;j<z;++j)
		{
			m1p = m1+i*y;
			m2p = m2+j;
			*r = 0;

			for(int k=0;k<y;++k)
			{
				*r += *m1p * *m2p;
				m1p++;
				m2p += z;
			}
			r++;
		}
	}
}

//8.8

int main()
{
	int an[][3] = {{1,0,0},{0,1,0},{1,0,1}};
	//int bn[][3] = {{1,0,0},{0,1,0},{1,0,0}};
	//IdentityMatrix(bn,3,3);
	IdentityMatrix(an,3,3);

	int m1[] = {2,-6,3,5,1,-1}; 
	int m2[] = {4,-2,-4,-5,-7,-3,6,7};
	int r[12];
	MatrixMultiply(m1,m2,r,3,2,4);
	for(int i = 0;i<12;++i)
	{
		printf("%d ",r[i]);
	}

	int an[10][10];

	int *i = an[2,3];

	return 0;
}