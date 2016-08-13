#include <iostream>
using namespace std;

//小根堆：根结点的键值是所有堆结点键值中最小者。

#define HEAP_MAX_SIZE 100

template<class T>
class MinHeap
{
private:
	T *heap;                                         //元素数组，0号位置也储存元素
	int CurrentSize;                                 //目前元素个数
	int MaxSize;                                     //可容纳的最多元素个数
	void FilterDown(const int start,const int end);  //自上往下调整，使关键字小的节点在上
	void FilterUp(int start);                        //自下往上调整
public:
	MinHeap(int n=HEAP_MAX_SIZE);
	~MinHeap();
	bool Insert(const T &x);                        //插入元素
	T RemoveMin();                                  //删除最小元素
	T GetMin();                                     //取最小元素
	bool IsEmpty() const;
	bool IsFull() const;
	void Clear();
};

template<class T>
MinHeap<T>::MinHeap(int n)
	:MaxSize(n),CurrentSize(0)
{
	heap=new T[MaxSize];
}

template<class T>
MinHeap<T>::~MinHeap()
{
	delete []heap;
}

template<class T>
void MinHeap<T>::FilterUp(int start) //自下往上调整
{
	int j=start,i=(j-1)/2; //i指向j的双亲节点
	T temp=heap[j];
	while(j>0)
	{
		if(heap[i]<=temp)
			break;
		else
		{
			heap[j]=heap[i];
			j=i;
			i=(i-1)/2;
		}
	}
	heap[j]=temp;
}

template<class T>
void MinHeap<T>::FilterDown(const int start,const int end) //自上往下调整，使关键字小的节点在上
{
	int i=start,j=2*i+1;
	T temp=heap[i];
	while(j<=end)
	{
		if( (j<end) && (heap[j]>heap[j+1]) )
			j++;
		if(temp<=heap[j])
			break;
		else
		{
			heap[i]=heap[j];
			i=j;
			j=2*j+1;
		}
	}
	heap[i]=temp;
}
template<class T>
bool MinHeap<T>::Insert(const T &x)
{
	if(CurrentSize==MaxSize)
		return false;
	heap[CurrentSize]=x;
	FilterUp(CurrentSize);
	CurrentSize++;

	return true;
}

template<class T>
T MinHeap<T>::RemoveMin( )
{
	T x=heap[0];
	heap[0]=heap[CurrentSize-1];
	CurrentSize--;
	FilterDown(0,CurrentSize-1); //调整新的根节点

	return x;
}

template<class T>
T MinHeap<T>::GetMin()
{
	return heap[0];
}

template<class T>
bool MinHeap<T>::IsEmpty() const
{
	return CurrentSize==0;
}

template<class T>
bool MinHeap<T>::IsFull() const
{
	return CurrentSize==MaxSize;
}

template<class T>
void MinHeap<T>::Clear()
{
	CurrentSize=0;
}

int main ()
{
	int an[] = {72,3,90,2,34,22,43,112,1,87};
	int len = sizeof(an)/sizeof(an[0]);
	int i=0;

	MinHeap<int> minHeap(len);
	for(i=0; i<len; ++i)
		minHeap.Insert(an[i]);

	cout<<minHeap.IsFull()<<endl;

	cout<<minHeap.GetMin()<<endl;

	for(i=0;i<len;++i)
	{
		cout<<minHeap.RemoveMin()<<ends;
	}
	cout<<endl;
	
	return 0;
}