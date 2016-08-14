#include<iostream>
using namespace std;

/* 冒泡
 * 直接插入排序
 * 快排
 * 归并排序
 * shell排序
 * 堆排序：求最小/最大的N个元素
 * 二分查找
 */

//int * tempArr = new int[len];

void Swap(int &a,int &b)
{
	int c=a;
	a = b;
	b = c;
}
void show(int *an,int len)
{
	for(int i=0;i<len;++i)
	{
		cout<<an[i]<<" ";
	}
	cout<<endl;
}
///////////////////快排/////////////////////////////////////
int Partition(int *an,int left,int right)
{
	int pri = an[left];//每次取第一个元素为基准
	while(left < right)
	{
		while(left<right && pri <= an[right]) right--;//从右边寻找第一个小于基准元素的下标
		Swap(an[left],an[right]);            
		while(left<right && pri >= an[left] ) left++; //从左边寻找第一个大于基准元素的下标
		Swap(an[left],an[right]);
	}
	return left;
}
void QuickSort(int *an,int left,int right)
{
	if(left < right)
	{
		int index = Partition(an,left,right);//index 下标位置的数据为该数据的正确位置
		QuickSort(an,left,index-1);          //排序 index 左边数据 [left...index-1];
		QuickSort(an,index+1,right);         //排序 index 右边数据 [index+1...right];
	}
}
void QuickSort(int *an,int len)
{
	QuickSort(an,0,len-1);
}

//////////////////////////归并排序//////////////////////////////////
void Merge(int *an,int *tmpArr,int len,int gap)
{
	int low1 = 0;            //第一个归并段开始下标
	int high1= low1+gap-1;   //第一个归并段结束下标
	int low2 = high1+1;      //第二个归并段开始下标
	int high2= len<low2+gap?len-1:low2+gap-1;//第二个归并段结束下标
	
	int i=0;
	while(low2 < len)//第二个归并段存在
	{
		//一二归并段都存在，取两个归并段开始位置较小的值放到 tmpArr 数组
		while(low1<=high1 && low2<=high2)
		{
			tmpArr[i++] = an[low1]>an[low2]?an[low2++]:an[low1++];
		}//将第一个归并段剩余数据拷贝到 tmpArr 数组
		while(low1<=high1)
		{
			tmpArr[i++] = an[low1++];
		}//将第二个归并段剩余数据拷贝到 tmpArr 数组
		while(low2<=high2)
		{
			tmpArr[i++] = an[low2++];
		}
		//改变两个归并段的开始结束下标（根据 gap 值）
		low1 = high2+1;     
		high1= low1+gap-1;
		low2 = high1+1;
		high2=len<low2+gap?len-1:low2+gap-1;
	}
	//若第二个归并段不存在，将第一个归并段数据拷贝到 tmpArr 数组
	while(low1 < len)
	{
		tmpArr[i++] = an[low1++];
	}
	//将一趟归并的结果 tmpArr 写回到原数据数组 an 中
	for(i=0;i<len;++i)
		an[i]=tmpArr[i];
}
void MergeSort(int *arr,int len)
{
	int *tmpArr = new int[len];//开辟辅助空间数组
	assert(tmpArr != NULL);
	for(int i=1;i<len;i*=2)//归并段的间隔取值：1 2 4 8
	{
		Merge(arr,tmpArr,len,i);
	}
	delete []tmpArr;
}
///////////////////////////////二分查找////////////////////////////////
int BinSearch(int *an,int len,int value)
{
	int left = 0;
	int right= len-1;

	while(left <= right)
	{
		int middle=(left+right)/2;
		
		if(value > an[middle])
			left = middle+1;
		else if(value < an[middle])
			right = middle-1;
		else
			return middle;
	}
	return -1;
}
/////////////////////////////////////////
void ShellSort(int *an,int len,int gap)
{
	int i,j,tmp;
	for(i=0;i<len-gap;++i)
	{
		tmp = an[i+gap];
		for(j=i;j>=0;j -= gap)
		{
			if(tmp < an[j])
				an[j+gap] = an[j];
			else
				break;
		}
		an[j+gap] = tmp;
	}
}

void ShellSort(int *an,int len)
{
	int gap[] = {5,3,1};//步长数组
	for(int i=0;i<sizeof(gap)/sizeof(an[0]);i++)
		ShellSort(an,len,gap[i]);
}
/////////////////////////////堆排序/////////////////////////////
void HeapAdjust(int *an,int s,int len)
{
	int tmp = an[s];
	int child = 2*s+1;
	while(child < len)
	{
		if(child+1 < len && an[child]<an[child+1])
			++child;
		if(an[s] < an[child])
		{
			an[s] = an[child];
			s = child;
			child = child*2+1;
		}else
			break;
		an[s] = tmp;
	}
}

void HeapSort(int *an,int len)
{
	int i;
	for(i=len/2-1;i>=0;--i)
	{
		HeapAdjust(an,i,len);
	}

	for(i=len-1;i>=0;--i)
	{
		Swap(an[0],an[i]);
		HeapAdjust(an,0,i);
	}
}

int main()
{
	int an[] = { 23, 65, 12, 3, 8, 76, 345, 90, 29, 21, 75, 34, 61 };
	int len = sizeof(an) / sizeof(an[0]);
	show(an,len);
	//QuickSort(an,len);
	//MergeSort(an,len);
	//ShellSort(an,len);
	HeapSort(an,len);
	show(an,len);

	return 0;
}


#if 0
//////////////////////////////////////////
int Partition(int *an,int start,int end)
{
	int pri = an[start];
	while(start < end)
	{
		while((start<end) && (pri<=an[end]))end--;
		Swap(an[end],an[start]);
		while((start<end) && (pri>=an[start]))start++;
		Swap(an[start],an[end]);	
	}
	an[start] = pri;
	return start;
}

void quickSort(int *an,int left,int right)
{
	if(left<right)
	{
		int partition = Partition(an,left,right);
		quickSort(an,left,partition-1);
		quickSort(an,partition+1,right);
	}
}

void quickSort(int *an,int len)
{
	quickSort(an,0,len-1);
}

void show(int *an,int len)
{
	for(int i=0;i<len;++i)
	{
		cout<<an[i]<<" ";
	}
	cout<<endl;
}
int main()
{
	int an[] = { 23, 65, 12, 3, 8, 76, 345, 90, 21, 75, 34, 61 };
	int len = sizeof(an) / sizeof(an[0]);
	//mergeSort(an,len);
	quickSort(an,len);
	show(an,len);

	return 0;
}



#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<iostream.h>

#pragma comment (lib,"winmm.lib")

void Show(int *an,int len)
{
	for(int i=0;i<len;++i)
	{
		cout<<an[i]<<" ";
	}
	cout<<endl;
}

void Swap(int &a,int &b)
{
	int c =a;
	a = b;
	b = c;
}
/////////////////////冒泡排序///////////////////////////
void BubbleSort(int *an,int len)
{
	int left=0;
	int right=len-1;
	int j;
	while(left < right)
	{
		for(j=left;j<right;++j)
		{
			if(an[j] > an[j+1])
			{
				Swap(an[j],an[j+1]);
			}
		}
		right--;
		for(j=right;j>left;--j)
		{
			if(an[j] < an[j-1])
			{
				Swap(an[j],an[j-1]);
			}
		}
		left++;
	}
}
void BubbleSort3(int *an,int len)
{
	int i = len-1;
	while(i > 0)
	{
		int pos = 0;
		for(int j=0;j<i;++j)
		{
			if(an[j] > an[j+1])
			{
				Swap(an[j],an[j+1]);
				pos = j;
			}
		}
		i = pos;
	}
}
void BubbleSort2(int *an,int len)
{
	for(int i=0;i<len-1;++i)
	{
		for(int j=0;j<len-i+1;++j)
		{
			if(an[j]>an[j+1])
			{
				Swap(an[j],an[j+1]);
			}
		}
	}
}
void BubbleSort1(int *an,int len)
{
	for(int i=0;i<len;++i)
	{
		for(int j=i+1;j<len;++j)
		{
			if(an[i]>an[j])
			{
				Swap(an[i],an[j]);
			}
		}
	}
}
//////////////////////快排//////////////////////////
int Partition(int *an,int left,int right)
{
	int pri = an[left];//int pri = left;
	while(left < right)
	{
		while(left < right && pri <= an[right]) right--;
		Swap(an[right],an[left]);
		while(left < right && pri >= an[left])   left++;
		Swap(an[left],an[right]);
	}
	//cout<<left<<" "<<right<<endl;
	an[left]=pri;
	return left;
}
void QuickSort(int *an,int left,int right)
{
	if(left < right)
	{
		int partition = Partition(an,left,right);
		QuickSort(an,left,partition-1);
		QuickSort(an,partition+1,right);
	}
}
void QuickSort(int *an,int len)
{
	QuickSort(an,0,len-1);
	//QuickSort1(an,0,len-1);
}
///////////////////////堆排序////////////////////////////
void HeapAdjust_High(int *an,int s,int len)//大根堆调整
{
	int tmp = an[s];
	int child = 2*s+1;
	while(child < len)
	{
		if(child+1 < len && an[child] < an[child+1])
		{
			++child;
		}
		if(an[s] < an[child])
		{
			an[s] = an[child];
			s = child;
			child = child*2+1;
		}
		else
		{
			break;
		}
		an[s] = tmp;
	}
}
void HeapAdjust_Low(int *an,int s,int len)//小根堆调整
{
	int tmp = an[s];
	int child = 2*s+1;
	while(child < len)
	{
		if(child+1 < len && an[child] > an[child+1])
		{
			++child;
		}
		if(an[s] > an[child])
		{
			an[s] = an[child];
			s = child;
			child = child*2+1;
		}
		else
		{
			break;
		}
		an[s] = tmp;
	}
}
void BuildHeapLow(int *an,int len)
{
	for(int i=len/2-1;i>=0;--i)
	{
		HeapAdjust_Low(an,i,len);
	}
}
void BuildHeapHigh(int *an,int len)
{
	for(int i=len/2-1;i>=0;--i)
	{
		HeapAdjust_High(an,i,len);
	}
}
void HeapSort(int *an,int len)//大根堆
{
	BuildHeapHigh(an,len);
	for(int i=len-1;i>0;--i)
	{
		Swap(an[i],an[0]);
		HeapAdjust_High(an,0,i);
	}
}
///////////////////////求最小的N个元素//////////////////////////////
void LowN(int *an,int len,int n)
{
	assert(n < len);
	int *bn = (int*)malloc(n*sizeof(int));
	
	int i;
	for(i=0;i<n;++i)
	{
		bn[i] = an[i];
	}
	BuildHeapHigh(bn,n);//调用大根堆调整
	for(i;i<len;++i)
	{
		if(bn[0] > an[i])
		{
			bn[0] = an[i];
			HeapAdjust_High(bn,0,n);
		}
	}
	BubbleSort(bn,n);//
	Show(bn,n);
	free(bn);
}
/////////////////////求最大的N个元素/////////////////////////
void TopN(int *an,int len,int n)
{
	assert(n < len);
	int *bn = (int*)malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;++i)
	{
		bn[i] = an[i];
	}
	BuildHeapLow(bn,n);//调用小根堆调整
	for(i;i<len;++i)
	{
		if(bn[0] < an[i])
		{
			bn[0] = an[i];
			HeapAdjust_Low(bn,0,n);
		}
	}
	BubbleSort(bn,n);//
	Show(bn,n);
	free(bn);
}
////////////////////////直接插入排序/////////////////////////////////
void InsertSort(int *an,int len)
{
	int i,j,tmp;
	for(i=1;i<len;++i)
	{
		tmp = an[i];
		for(j=i-1;j>=0;--j)
		{
			if(an[j] <= tmp)
			{
				break;
			}
			an[j+1] = an[j];
		}
		an[j+1] = tmp;
	}
}
/////////////////////////////////////////////////////////
void shell(int *an,int len,int gap)
{
	int i,j,tmp;
	for(i=gap;i<len;++i)
	{
		tmp = an[i];
		for(j=i-gap;j>=0;j -= gap)
		{
			if(an[j] <= tmp)
			{
				break;
			}
			an[j+gap] = an[j];
		}
		an[j+gap] = tmp;
	}
}

void ShellSort(int *an,int len)
{
	int d[] = {5,3,1};
	for(int i=0;i<sizeof(d)/sizeof(d[0]);++i)
	{
		shell(an,len,d[i]);
	}
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
int main()
{
	int an[] = {1,4,63,7,4,87,98,453,23,898,-1,-2,435};
	int len = sizeof(an)/sizeof(an[0]);
	Show(an,len);
	//BubbleSort(an,len);
	//QuickSort(an,len);

	//HeapSort(an,len);
	//TopN(an,len,5);
	//LowN(an,len,5);

	//InsertSort(an,len);
	//ShellSort(an,len);
	
	Show(an,len);
	
	return 0;
}

int main11()
{
	int an[100000];
	int len = 100000;

	srand((unsigned)time(NULL));
	for(int i = 0; i < len ; ++i )
	{
		if(len == 100000)
		{
			an[i] = rand();
		}
		else
		{
			an[i] = rand() % 200;
		}
	}
	int count =0 ;
	for(i=0;i<len;++i)
	{
		cout<<an[i]<<" ";
		count++;
		if(count == 10)
		{
			count=0;
			cout<<endl;
		}
			
	}
	cout<<endl<<"================================================="<<endl;
	DWORD t1 = timeGetTime();
	TopN(an,len,10);
	LowN(an,len,10);
	DWORD t2 = timeGetTime();
	DWORD t = t2 -t1;
	printf("用时 ：%02ld分%02ld秒%03ld毫秒\n",(t / 1000) / 60,(t /1000)%60, t%1000);
	
	return 0;
}


#endif
