//Stack.h
#pragma once

#include<stdlib.h>
#include<assert.h>

#define STACKSIZE 20
template<class Type>
class Stack
{
private:
    Type  data[STACKSIZE];
    int maxsize;
    int top;
public:
    Stack()
    {
        maxsize = STACKSIZE;
        top = -1;
    //  ��̬���ٿռ�
    //  data = (Type*)malloc(sizeof(Type)*maxsize);
    //  assert(data != NULL);
    }

    ~Stack()
    {
    //  free(data);
    //  data = NULL;
    }

    int size() const   { return top+1;}               //��ǰԪ�ظ���
    bool empty() const { return size() == 0;}         //ջ�Ƿ�Ϊ��
    bool full() const  { return size() == maxsize;}   //ջ�Ƿ���
    bool push(const Type &x)                          //push������topָ����++�����ֵ
    {
        if(full()) return false;
        data[++top] = x;

        return true;
    }
    bool pop(Type &x)                                 //pop��������ȡֵ��topָ���--
    {
        if(empty()) return false;
        x = data[top--];

        return true;
    }

    bool gettop(Type &x)                             //��ȡջ��Ԫ��
    {
        if(empty()) return false;
        x = data[top];

        return true;
    }
};