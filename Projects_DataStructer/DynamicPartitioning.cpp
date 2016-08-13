#include<iostream>
//#include<new>
#include<list>
#include<stdlib.h>
using namespace std;

/*
	操作系统选择动态分区算法
	1.首次适应算法     FF
	2.循环首次适应算法 NF
	3.最佳适应算法     BF
	4.最坏适应算法     WF
*/
	
#define G 5

struct Node{
	int size;
	int addr;
	struct Node *next;
};

Node *buyNode(int s,int a)
{
	Node *p =  (Node*)malloc(sizeof(Node));
	p->size = s;
	p->addr = a;
	return p;
}
void freeNode(Node *p)
{
	free(p);
}
Node *init()
{
	Node *head = new Node;
	head->next = NULL;
	head->size = 0;
	return head;
}

void showSpace(Node *head)
{
	Node *p = head->next;
	while(p)
	{
		cout<<p->size<<" -> ";
		p = p->next;
	}
	cout<<endl;
}
void inseartAddr(Node *head,Node *space)
{
	Node *p = head;
	if(p == NULL)
	{
		head->next = space;
	}
	while(p->next != NULL && p->next->addr < space->addr)
	{
		p = p->next;
	}
	space->next = p->next;
	p->next = space;
}
void inseartSize(Node *head,Node *space)
{
	Node *p = head;
	if(p == NULL)
	{
		head->next = space;
	}
	while(p->next != NULL && p->next->size < space->size)
	{
		p = p->next;
	}
	space->next = p->next;
	p->next = space;
}
void getSpaceAddr(Node *head)
{
	//Node *p = head->next;
	cout<<"请依次输入空闲分区的大小 和 起始地址，以0结束"<<endl<<endl;
	int flag = 1;
	int size,addr;
	while(flag)
	{
		cin>>size>>addr;
		if(size == 0)
		{
			flag = 0;
			break;
		}
		else{
			Node *s = buyNode(size,addr);
			//s->next = head->next;
			//head->next = s;
			inseartAddr(head,s);
			head->size += 1;
		}
	}
}
void getSpaceSize(Node *head)
{
	//Node *p = head->next;
	cout<<"请依次输入空闲分区的大小 和 起始地址，以0结束"<<endl<<endl;
	int flag = 1;
	int size,addr;
	while(flag)
	{
		cin>>size>>addr;
		if(size == 0)
		{
			flag = 0;
			break;
		}
		else{
			Node *s = buyNode(size,addr);
			//s->next = head->next;
			//head->next = s;
			inseartSize(head,s);
		}
	}
}
void getSpaceFirst(Node *head)
{
	//Node *p = head->next;
	cout<<"请依次输入空闲分区的大小 和 起始地址，以0结束"<<endl<<endl;
	int flag = 1;
	int size,addr;
	while(flag)
	{
		cin>>size>>addr;
		if(size == 0)
		{
			flag = 0;
			break;
		}
		else{
			Node *s = buyNode(size,addr);
			s->next = head->next;
			head->next = s;
			//inseartAddr(head,s);
		}
	}
}
void reser(Node *head)
{
	Node *p = head->next;
	Node *s = head->next;
	head->next = NULL;
	while(p)
	{
		s = p;
		p = p->next;
		s->next = head->next;
		head->next = s;
	}
}

void FF(Node *head)
{
	getSpaceAddr(head);
	Node *p = head->next;
	cout<<"分配前分区："<<endl;
	showSpace(head);
	int request;
	cout<<endl<<"请输入要求分区大小：";
	cin>>request;
	while(p->next != NULL && p->next->size < request )
	{
		p = p->next;
	}

	Node *s = p->next;
	p->next = s->next;

	s->size -= request;

	inseartSize(head,s);
	cout<<endl<<"分配后分区："<<endl;
	showSpace(head);
}

void BF(Node *head)
{
	getSpaceSize(head);
	Node *p = head->next;
	cout<<"分配前分区："<<endl;
	showSpace(head);
	int request;
	cout<<endl<<"请输入要求分区大小：";
	cin>>request;
	while(p->next != NULL && p->next->size < request )
	{
		p = p->next;
	}

	Node *s = p->next;
	p->next = s->next;

	s->size -= request;

	if(s->size > G)
		inseartSize(head,s);
	cout<<endl<<"分配后分区："<<endl;
	showSpace(head);
}
void WF(Node *head)
{
	getSpaceSize(head);
	reser(head);

	Node *p = head->next;
	cout<<"分配前分区："<<endl;
	showSpace(head);

	int request;
	cout<<endl<<"请输入要求分区大小：";
	cin>>request;
	
	if(p->size < request)
	{
		cout<<" 没有合适的空间"<<endl;
		return;
	}
	head->next = p->next;
	p->next = NULL;
	p->size -= request;

	reser(head);
	if(p->size > G)
		inseartSize(head,p);
	reser(head);
	cout<<endl<<"分配后分区："<<endl;
	showSpace(head);
}
void NF(Node *head)
{
	getSpaceAddr(head);
	int flag = 1;
	while(flag)
	{
		Node *p = head->next;
		cout<<"分配前分区："<<endl;
		showSpace(head);
		int request;
		cout<<endl<<"请输入要求分区大小：";
		cin>>request;
		while(p->next != NULL && p->next->size < request )
		{
			p = p->next;
		}

		Node *s = p->next;
		p->next = s->next;

		s->size -= request;
		if(s->size >= G)
			inseartSize(head,s);
		cout<<endl<<"分配后分区："<<endl;
		showSpace(head);

		if(head->size <= 0)
		{
			cout<<"循环次数已经超过"<<endl;
			return;
		}
		
		head->size -= 1;

		cout<<"是否继续分配 是1，否0〉";
		cin>>flag;
	}
}
void show()
{
	cout<<"========选择分区算法======="<<endl;
	cout<<"1.首次适应算法     FF"<<endl;
	cout<<"2.循环首次适应算法 NF"<<endl;
	cout<<"3.最佳适应算法     BF"<<endl;
	cout<<"4.最坏适应算法     WF"<<endl;
}
int main()
{
	Node *head = init();

	int num;
	switch(1)
	{

	}

	//FF(head);
	//BF(head);
	//WF(head);
	
	NF(head);


	return 0;
}
