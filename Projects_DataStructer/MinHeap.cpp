#include <iostream>
using namespace std;

//С���ѣ������ļ�ֵ�����жѽ���ֵ����С�ߡ�

#define HEAP_MAX_SIZE 100

template<class T>
class MinHeap
{
private:
	T *heap;                                         //Ԫ�����飬0��λ��Ҳ����Ԫ��
	int CurrentSize;                                 //ĿǰԪ�ظ���
	int MaxSize;                                     //�����ɵ����Ԫ�ظ���
	void FilterDown(const int start,const int end);  //�������µ�����ʹ�ؼ���С�Ľڵ�����
	void FilterUp(int start);                        //�������ϵ���
public:
	MinHeap(int n=HEAP_MAX_SIZE);
	~MinHeap();
	bool Insert(const T &x);                        //����Ԫ��
	T RemoveMin();                                  //ɾ����СԪ��
	T GetMin();                                     //ȡ��СԪ��
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
void MinHeap<T>::FilterUp(int start) //�������ϵ���
{
	int j=start,i=(j-1)/2; //iָ��j��˫�׽ڵ�
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
void MinHeap<T>::FilterDown(const int start,const int end) //�������µ�����ʹ�ؼ���С�Ľڵ�����
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
	FilterDown(0,CurrentSize-1); //�����µĸ��ڵ�

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