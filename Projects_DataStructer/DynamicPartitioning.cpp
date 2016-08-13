#include<iostream>
//#include<new>
#include<list>
#include<stdlib.h>
using namespace std;

/*
	����ϵͳѡ��̬�����㷨
	1.�״���Ӧ�㷨     FF
	2.ѭ���״���Ӧ�㷨 NF
	3.�����Ӧ�㷨     BF
	4.���Ӧ�㷨     WF
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
	cout<<"������������з����Ĵ�С �� ��ʼ��ַ����0����"<<endl<<endl;
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
	cout<<"������������з����Ĵ�С �� ��ʼ��ַ����0����"<<endl<<endl;
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
	cout<<"������������з����Ĵ�С �� ��ʼ��ַ����0����"<<endl<<endl;
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
	cout<<"����ǰ������"<<endl;
	showSpace(head);
	int request;
	cout<<endl<<"������Ҫ�������С��";
	cin>>request;
	while(p->next != NULL && p->next->size < request )
	{
		p = p->next;
	}

	Node *s = p->next;
	p->next = s->next;

	s->size -= request;

	inseartSize(head,s);
	cout<<endl<<"����������"<<endl;
	showSpace(head);
}

void BF(Node *head)
{
	getSpaceSize(head);
	Node *p = head->next;
	cout<<"����ǰ������"<<endl;
	showSpace(head);
	int request;
	cout<<endl<<"������Ҫ�������С��";
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
	cout<<endl<<"����������"<<endl;
	showSpace(head);
}
void WF(Node *head)
{
	getSpaceSize(head);
	reser(head);

	Node *p = head->next;
	cout<<"����ǰ������"<<endl;
	showSpace(head);

	int request;
	cout<<endl<<"������Ҫ�������С��";
	cin>>request;
	
	if(p->size < request)
	{
		cout<<" û�к��ʵĿռ�"<<endl;
		return;
	}
	head->next = p->next;
	p->next = NULL;
	p->size -= request;

	reser(head);
	if(p->size > G)
		inseartSize(head,p);
	reser(head);
	cout<<endl<<"����������"<<endl;
	showSpace(head);
}
void NF(Node *head)
{
	getSpaceAddr(head);
	int flag = 1;
	while(flag)
	{
		Node *p = head->next;
		cout<<"����ǰ������"<<endl;
		showSpace(head);
		int request;
		cout<<endl<<"������Ҫ�������С��";
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
		cout<<endl<<"����������"<<endl;
		showSpace(head);

		if(head->size <= 0)
		{
			cout<<"ѭ�������Ѿ�����"<<endl;
			return;
		}
		
		head->size -= 1;

		cout<<"�Ƿ�������� ��1����0��";
		cin>>flag;
	}
}
void show()
{
	cout<<"========ѡ������㷨======="<<endl;
	cout<<"1.�״���Ӧ�㷨     FF"<<endl;
	cout<<"2.ѭ���״���Ӧ�㷨 NF"<<endl;
	cout<<"3.�����Ӧ�㷨     BF"<<endl;
	cout<<"4.���Ӧ�㷨     WF"<<endl;
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
