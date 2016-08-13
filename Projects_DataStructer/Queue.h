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
    int front,rear;//front队头，rear队尾
    int cursize;
    int maxsize;

public:
/*  //打印队列元素，测试用
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
    int size() const  { return cursize;}           //队列元素个数
    bool empty() const{ return size() == 0;}       //队列是否为空
    bool full() const { return size() == maxsize;} //队列是否为满

    bool push(const Type &x)                       //push方法，元素放到对尾rear处
    {
        if(full()) return false;
        data[rear] = x;
        rear = (rear+1)%maxsize;
        cursize+=1;
        return true;
    }
    bool pop(Type &x)                             //pop方法，取队列头front处元素出队
    {
        if(empty()) return false;
        x = data[front];
        front = (front+1)%maxsize;
        cursize-=1;
        return true;
    }
    bool get_front(Type &x)                      //获取队头元素
    {
        if(empty()) return false;
        x = data[front];
        return true;
    }
};