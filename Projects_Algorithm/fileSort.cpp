#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SIZE  30000
#define ITEM_SIZE   1000

void CreateBigFile(const char *path)
{
	FILE *fw = fopen(path,"wb");
	assert(fw != NULL);
	int tmp;
	for(int i=0;i<NUM_SIZE;i++)
	{
		tmp = rand();
		fwrite(&tmp,sizeof(int),1,fw);
	}
	fclose(fw);
}

//seek从开始往右偏移seek个字节
void Show(const char *path,int num,int seek)
{
	FILE *fr = fopen(path,"rb");
	assert(fr != NULL);
	fseek(fr,seek,SEEK_SET);

	int tmp;
	for(int i=1;i<=num;i++)
	{
		assert(fread(&tmp,sizeof(int),1,fr)>0);
		printf("%d ",tmp);
		if(i%10 == 0)
		{
			printf("\n");
		}
	}
	fclose(fr);
}

void BubbleSort(int *arr,int len)
{
	int tmp;
	int flg;
	for(int i=0;i<len-1;i++)
	{
		flg = 0;
		for(int j=0;j<len-1-i;j++)
		{
			if(arr[j] > arr[j+1])
			{
				flg = 1;
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
		if(flg == 0)
		{
			return ;
		}
	}
}

void FileCopy(const char *desPath,const char *srcPath)
{
	FILE * fr = fopen(srcPath,"rb");
	FILE *fw = fopen(desPath,"wb");
	assert(fr!=NULL && fw!=NULL);
	int arr[ITEM_SIZE];
	int len;

	while((len=fread(arr,sizeof(int),ITEM_SIZE,fr))==ITEM_SIZE)
	{
		assert(fwrite(arr,sizeof(int),len,fw)==len);
	}
	assert(fwrite(arr,sizeof(int),len,fw)==len);

	fclose(fr);
	fclose(fw);
}

void InitBigFile(const char *path)
{
	int arr[ITEM_SIZE];
	char *tmpPath = "D:\\tmp.txt";
	FILE *fr = fopen(path,"rb");
	FILE *fw = fopen(tmpPath,"wb");
	assert(fr!=NULL && fw!=NULL);
	int len;
	while((len=fread(arr,sizeof(int),ITEM_SIZE,fr))==ITEM_SIZE)
	{
		BubbleSort(arr,sizeof(arr)/sizeof(arr[0]));
		assert(fwrite(arr,sizeof(int),len,fw)==len);
	}

	BubbleSort(arr,sizeof(arr)/sizeof(arr[0]));
	assert(fwrite(arr,sizeof(int),len,fw)==len);

	fclose(fr);
	fclose(fw);

	FileCopy(path,tmpPath);
	remove(tmpPath);
}

int Check(const char *path)
{
	FILE *fr = fopen(path,"rb");
	assert(fr != NULL);
	//fseek(fr,seek,SEEK_SET);
	int count = 0;
	int first;
	int end;
	fread(&first,sizeof(int),1,fr);
	int len;
	while((len=fread(&end,sizeof(int),1,fr))==1)
	{
		if(first > end)
		{
			count++;
		}
		first = end;
	}

	fclose(fr);
	return count;
}

void FileMerge(const char *path,int gap)
{
	char *tmpPath = "D:\\tmp.txt";
	FILE *fr = fopen(path,"rb");
	FILE *fw = fopen(tmpPath,"wb");
	assert(fr!=NULL && fw!=NULL);

	int arr[ITEM_SIZE];
	int brr[ITEM_SIZE];
	int crr[ITEM_SIZE];

	int low1 = 0;
	int low2 = low1+gap;
	int count1 = 0;//arr已经归并成功的数据个数
	int count2 = 0;//brr已经归并成功的数据个数

	int i = ITEM_SIZE;
	int j = ITEM_SIZE;
	int k = 0;
	int high2;
	while(low2 < NUM_SIZE)//第二个归并段存在
	{
		high2 = low2+gap<NUM_SIZE?low2+gap:NUM_SIZE;
		while(count1<gap && low2+count2<high2)
		{
			if(i == ITEM_SIZE)
			{
				fseek(fr,sizeof(int)*(low1+count1),SEEK_SET);
				assert(fread(arr,sizeof(int),ITEM_SIZE,fr)==ITEM_SIZE);
				i = 0;
			}
			if(j == ITEM_SIZE)
			{
				fseek(fr,sizeof(int)*(low2+count2),SEEK_SET);
				assert(fread(brr,sizeof(int),ITEM_SIZE,fr)==ITEM_SIZE);
				j = 0;
			}

			if(arr[i] < brr[j])
			{
				crr[k++] = arr[i++];
				count1++;
			}
			else
			{
				crr[k++] = brr[j++];
				count2++;
			}
			if(k == ITEM_SIZE)
			{
				assert(fwrite(crr,sizeof(int),ITEM_SIZE,fw)==ITEM_SIZE);
				k = 0;
			}
		}//两个归并段都有数字

		while(count1<gap)
		{
			if(i == ITEM_SIZE)
			{
				fseek(fr,sizeof(int)*(low1+count1),SEEK_SET);
				assert(fread(arr,sizeof(int),ITEM_SIZE,fr)==ITEM_SIZE);
				i = 0;
			}
			crr[k++] = arr[i++];
			count1++;
			if(k == ITEM_SIZE)
			{
				assert(fwrite(crr,sizeof(int),ITEM_SIZE,fw)==ITEM_SIZE);
				k = 0;
			}
		}
		high2 = low2+gap<NUM_SIZE?low2+gap:NUM_SIZE;
		while(low2+count2 < high2)
		{
			if(j == ITEM_SIZE)
			{
				fseek(fr,sizeof(int)*(low2+count2),SEEK_SET);
				assert(fread(brr,sizeof(int),ITEM_SIZE,fr)==ITEM_SIZE);
				j = 0;
			}
			crr[k++] = brr[j++];
			count2++;

			if(k == ITEM_SIZE)
			{
				assert(fwrite(crr,sizeof(int),ITEM_SIZE,fw) == ITEM_SIZE);
				k = 0;
			}
		}
		low1 = low2+gap;
		low2 = low1+gap;
		count1 = 0;
		count2 = 0;
		i = ITEM_SIZE;
		j = ITEM_SIZE;
	}//end 两个归并段存在

	fseek(fr,sizeof(int)*(low1+count1),SEEK_SET);
	while(low1+count1<NUM_SIZE)
	{
		if(i == ITEM_SIZE)
		{
			assert(fread(arr,sizeof(int),ITEM_SIZE,fr) == ITEM_SIZE);
			i = 0;
		}
		crr[k++] = arr[i++];
		count1++;

		if(k == ITEM_SIZE)
		{
			assert(fwrite(arr,sizeof(int),ITEM_SIZE,fw)==ITEM_SIZE);
			k = 0;
		}
	}
	fclose(fr);
	fclose(fw);
	FileCopy(path,tmpPath);
	remove(tmpPath);
}

void FileSort(const char *path)
{
	for(int i=ITEM_SIZE;i<NUM_SIZE;i*=2)
	{
		FileMerge(path,i);
	}
}

int main()
{
	char *path = "D:\\big.txt";
	CreateBigFile(path);
	InitBigFile(path);
	FileSort(path);
	Show(path,30000,0);
	printf("%d\n",Check(path));
	
	return 0;
}