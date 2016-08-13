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
    //  动态开辟空间
    //  data = (Type*)malloc(sizeof(Type)*maxsize);
    //  assert(data != NULL);
    }

    ~Stack()
    {
    //  free(data);
    //  data = NULL;
    }

    int size() const   { return top+1;}               //当前元素个数
    bool empty() const { return size() == 0;}         //栈是否为空
    bool full() const  { return size() == maxsize;}   //栈是否满
    bool push(const Type &x)                          //push方法，top指针先++，后放值
    {
        if(full()) return false;
        data[++top] = x;

        return true;
    }
    bool pop(Type &x)                                 //pop方法，先取值，top指针后--
    {
        if(empty()) return false;
        x = data[top--];

        return true;
    }

    bool gettop(Type &x)                             //获取栈顶元素
    {
        if(empty()) return false;
        x = data[top];

        return true;
    }
};