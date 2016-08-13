#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vld.h>

/*
Node *Search(List list,int key);   //查找key，返回key的地址
Node *SearchPre(List list,int key);//查找key，返回key前驱的地址
int Len(List list);                //求单链表长度
void Delete_pos(List list,int k);  //删除第k个结点
void Delete_end(List list,int k);  //删除倒数第k个结点
void Rever_List(List list);        //逆置单链表
void Rever_L(List list);           //链表的逆反
bool IsRing(List list);            //判断是否带环
int Ring_len(List list);           //求环的长度
Node *Ring_node(List list);        //求进入环的第一个结点
//只给定单链表中某个结点p(非空结点)，在p前面插入一个结点。
void Insert_p(Node *p,int val);
//已知递增有序的单链表 A,B 和C 分别存储了一个集合，设计算法实现 A：=A∪（B∩C） ，
//并使求解结构 A 仍保持递增。要求算法的时间复杂度为 O(|A|+|B|+|C|)。
Node *Fun(List a,List b,List c);
//只给定单链表中某个结点p(并非最后一个结点，即p->next!=NULL)指针，删除该结点。 
void Delete_node(Node *p);
*/

typedef struct Node
{
	int data;
	struct Node *next;

}Node,*List;

void InitNode(List *list)
{
	*list = (List)malloc(sizeof(Node));
	(*list)->next = NULL;
}

Node *BuyNode(int val)
{
	Node *list = (List)malloc(sizeof(Node));
	assert(list != NULL);

	list->data = val;
	list->next = NULL;

	return list;
}

Node *Insert_head(List list,int val)//头插
{
	Node *p = BuyNode(val);

	p->next = list->next;
	list->next = p;

	return list;
}

Node *Insert_tail(List list,int val)//尾插
{
	Node *p = BuyNode(val);
	
	Node *q = list;
	while((q->next) != NULL)
	{
		q = q->next;
	}
	
	q->next = p;
	
	return list;
}

Node *Search(List list,int key)//查找key，返回key的地址
{
	Node *p = list->next;
	while(p->next != NULL && p->data != key)
	{
		p = p->next;
	}

	if(p == NULL)
	{
		return NULL;
	}

	return p;
}

Node *SearchPre(List list,int key)//查找key，返回key前驱的地址
{
	for(Node *p = list;p->next != NULL;p = p->next)
	{
		if(p->next->data == key)
		{
			return p;
		}
	}

	return NULL;
}

void Destroy(List list)
{
	while(list->next != NULL)
	{
		Node *p = list->next;
		list->next = p->next;

		free(p);
	}
}

void Show(List list)
{
	list = list->next;
	while(list != NULL)
	{
		printf("%d ",list->data);
		list = list->next;
	}
	printf("\n");
}

int Len(List list)//求单链表长度
{
	int len = 0;
	while(list->next != NULL)
	{
		len++;
		list = list->next;
	}

	return len;
}

void Delete_pos(List list,int k)//删除第k个结点
{
	Node *p = list->next;
	Node *q = list;
	int i = 1;

	while(p != NULL && i != k)
	{
		i++;
		p = p->next;
		q = q->next;
	}

	if( i == k)
	{
		q->next = p->next;
		free(p);
	}
	else
	{
		printf("Error pos!\n");
	}
}

void Delete_end(List list,int k)//删除倒数第k个结点
{
	int pos = Len(list) - k + 1;
	Delete_pos(list,pos);
}

//只给定单链表中某个结点p(并非最后一个结点，即p->next!=NULL)指针，删除该结点。 
void Delete_node(Node *p)
{
	while(p->next != NULL)
	{
		p->data = p->next->data;
		p = p->next;
	}
	free(p);
}

void Rever_List(List list)  //逆置单链表
{
	Node *p = list->next;
	Node *q = p;
	int tmp = p->data;              //标记第一个数据

	while(p->next != NULL)
	{
		Insert_head(list,p->next->data);//把第一个数据之后的数据 头插
		p = p->next;
	}

	while(q->data != tmp)       //找到标记的数据
	{
		q = q->next;
	}

	p = q;
	Destroy(p);             //删除标记之后的数据
	q->next = NULL;

}

void Rever_L(List list) //链表的逆反
{
	assert(list != NULL);
	Node *s = list->next;
	list->next = NULL;

	while(s != NULL)
	{
		//Insert_head(list,s->data);
		Node *p = s;
		s = s->next;
		p->next = list->next ;
		list->next = p;
		//s = s->next;
	}
}

bool IsRing(List list) //判断是否带环
{
	Node *p = list;
	Node *q = list;

	while(q->next != NULL && p->next->next != NULL)
	{
		q = q->next;
		p = p->next->next;

		if(p->data == q->data)
		{
			return true;
		}
	}

	return false;
}

int Ring_len(List list) //求环的长度
{	
	int len = 0;
	if( !IsRing(list))
	{
		return len;
	}

	Node *p = list;
	Node *q = list;

	while(q->next != NULL && p->next->next != NULL)
	{
		q = q->next;
		p = p->next->next;

		if(p->data == q->data)
		{
			break;
		}
	}
	while(p != q->next)  //q先后移动了一步，所以++len
	{
		q = q->next;
		++len;
	}
	return len;

}

Node *Ring_node(List list)//求进入环的第一个结点
{

	Node *p = list;
	Node *q = list;

	while(q->next != NULL && p->next->next != NULL)
	{
		q = q->next;
		p = p->next->next;

		if(p->data == q->data)
		{
			return p;
		}
	}

	return NULL;
}

//只给定单链表中某个结点p(非空结点)，在p前面插入一个结点。
void Insert_p(Node *p,int val)
{
	Insert_tail(p,val); //尾插

	p->next->data = p->data;
	p->data = val;
}

//已知递增有序的单链表 A,B 和C 分别存储了一个集合，设计算法实现 A：=A∪（B∩C） ，
//并使求解结构 A 仍保持递增。要求算法的时间复杂度为 O(|A|+|B|+|C|)。
Node *Fun(List a,List b,List c)
{
	assert(a!=NULL && b!=NULL && c!=NULL);
	Node *pa = a->next;  //pa比a快一步
	Node *pb = b->next;  
	c = c->next;
	b = b->next;
	while(b->next != NULL)
	{
		while((b->data) < (c->data))
		{
			b = b->next;
			pb = b->next;
		}
		while((b->data) > (c->data))
		{
			c = c->next;
		}
		while((b->data) == (c->data))
		{
			while(pa->next != NULL && (b->data) > (pa->data))
			{
				pa = pa->next;
				a = a->next;
			}
			if((b->data) != (pa->data))
			{
				pb = b;
				if(pa->next == NULL)
				{
					pa->next = pb;
					pb->next = NULL;
				}
				else
				{
					pb->next = pa->next;
					pa->next = pb;
				}
			}
			b = b->next;
			//pb = b->next;
			c = c->next;
			if(b->next == NULL)
			{
				break;
			}
		}
	}
	return a;
}


int main()
{
	Node *list;

	InitNode(&list);
	
	for(int i=1;i<=10;++i)
	{
		//Insert_head(list,i); //头插
		Insert_tail(list,i);  //尾插
	}

	//Delete_pos(list,13);  //删除第k个结点
	//Delete_pos(list,3);
	//Delete_end(list,13);  //删除倒数第k个结点
	//Delete_end(list,3);

	Show(list);

	Rever_L(list);   //单链表的逆反

	Show(list);

	printf("单链表长度 = %d\n",Len(list));

	Destroy(list);


	
	/*
	List a,b,c;

	InitNode(&a);
	InitNode(&b);
	InitNode(&c);
	for(int i=1;i<=8;++i)
	{
		//Insert_head(list,i); //头插
		Insert_tail(a,i);  //尾插
	}
	for(int i=3;i<=10;++i)
	{
		//Insert_head(list,i); //头插
		Insert_tail(c,i);  //尾插
	}
	for(int i=5;i<=11;++i)
	{
		//Insert_head(list,i); //头插
		Insert_tail(b,i);  //尾插
	}
	

	Show(a);
	Show(b);
	Show(c);
	Fun(a,b,c);
	Show(a);
	Destroy(a);
	Destroy(b);
	Destroy(c);
	*/


	return 0;
}

