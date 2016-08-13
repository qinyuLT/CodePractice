#include<iostream>
#include<assert.h>
using namespace std;

template<class Type>
class LinkList{

protected:
	typedef struct LinkNode{
		Type data;
		struct LinkNode* next;
	};

public:
	LinkList()
	{
		head = Buynode();
	}
	~LinkList()
	{
		if(empty())//������ǿգ������ͷɾ������һ��һ���ͷ�
		{
			for(int i=0;i<head->data;++i)
			{
				pop_front();
			}
		}
		Freenode(head);//����ͷ�ͷ���
	}
	static LinkNode *Buynode()
	{
		LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
		assert(s != NULL);
		memset(s,0,sizeof(LinkNode));
		return s;
	}
	static void Freenode(LinkNode *p)
	{
		free(p);
	}
public:
	int empty()
	{
		return head->data==0?1:0;
	}

	void push_back(const Type& value)//β��
	{
		LinkNode *s = Buynode();
		s->data = value;
		head->data++;            

		LinkNode *p = head->next;
		if(p == NULL)           //��ǰ����Ϊ�գ�ֻ��ͷ���
		{
			head->next=s;
			return;
		}
		while(p->next != NULL)
		{
			p=p->next;
		}
		p->next = s;
	}
	void pop_back()
	{
		if( empty())
		{
			cout<<"linklist empty,pop_back error !"<<endl;
			return;
		}

		head->data--;
		LinkNode *p = head->next;
		if(p->next == NULL)//��ǰ����ֻ��һ�����ݽ��
		{
			Freenode(p);
			head->next=NULL;
			return;
		}
		while(p->next->next != NULL)
		{
			p = p->next;
		}
		LinkNode *s = p->next;
		Freenode(s);
		p->next=NULL;
	}

	void push_front(const Type& value)//ͷ��
	{
		LinkNode *s = Buynode();
		s->data = value;

		LinkNode *p = head->next;
		head->next = s;
		s->next = p;

		head->data++;
	}
	void pop_front()
	{
		if( empty())
		{
			cout<<"linklist empty,pop_front error !"<<endl;
			return;
		}
		LinkNode *p = head->next;
		head->next = p->next;
		Freenode(p);
		head->data--;
	}
	void reverse()//
	{
		LinkNode *p=head->next;
		LinkNode *s = NULL;
		//�Ͽ�ͷ��㣬����ߵ����ݽ��һ��һ��ͷ�嵽ͷ��㣬��ʵ������
		head->next = NULL;

		while(p)
		{
			s=p;
			p=p->next;

			s->next=head->next;
			head->next=s;
		}
	}
	void show_list()
	{
		LinkNode *p=head->next;
		cout<<"data: ";//
		while(p)
		{
			cout<<p->data<<" ";
			p = p->next;
		}
		cout<<endl;
		cout<<"size: "<<head->data<<endl;
	}

private:
	LinkNode *head;
};

int main()
{
	int an[] = {1,2,3,4,5,6};
	int len = sizeof(an)/sizeof(an[0]);

	LinkList<int> mylist;

	for(int i=0;i<len;++i)
	{
		//mylist.push_front(an[i]);
		mylist.push_back(an[i]);
	}
	mylist.show_list();
	
	mylist.reverse();
	mylist.show_list();

	for(i=0;i<len+1;++i)
	{
		mylist.pop_front();
		//mylist.pop_back();
		mylist.show_list();
	}
	return 0;
}