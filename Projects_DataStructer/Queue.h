//Queue.h
#pragma once

#include<stdlib.h>
#include<assert.h>

#define QUESIZE 8

template<class Type>
class Queue
{
private:
    Type *data;
    int front,rear;//front��ͷ��rear��β
    int cursize;
    int maxsize;

public:
/*  //��ӡ����Ԫ�أ�������
    void print() const
    {
        int k = front;
        for(int i = 0;i<cursize;++i)
        {
            cout<<data[k]<<" ";
            k =  (k+1)%maxsize;
        }
        cout<<endl;
    }
*/  
    Queue(int sz = QUESIZE)
    {
        maxsize = sz;
        cursize =0;
        front = rear = 0;
        data = (Type*)malloc(sizeof(Type)*maxsize);
        assert(data != NULL);
    }
    ~Queue()
    {
        free(data);
        data = NULL;
    }
    int size() const  { return cursize;}           //����Ԫ�ظ���
    bool empty() const{ return size() == 0;}       //�����Ƿ�Ϊ��
    bool full() const { return size() == maxsize;} //�����Ƿ�Ϊ��

    bool push(const Type &x)                       //push������Ԫ�طŵ���βrear��
    {
        if(full()) return false;
        data[rear] = x;
        rear = (rear+1)%maxsize;
        cursize+=1;
        return true;
    }
    bool pop(Type &x)                             //pop������ȡ����ͷfront��Ԫ�س���
    {
        if(empty()) return false;
        x = data[front];
        front = (front+1)%maxsize;
        cursize-=1;
        return true;
    }
    bool get_front(Type &x)                      //��ȡ��ͷԪ��
    {
        if(empty()) return false;
        x = data[front];
        return true;
    }
};