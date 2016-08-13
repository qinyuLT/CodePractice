#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vld.h>

/*
Node *Search(List list,int key);   //����key������key�ĵ�ַ
Node *SearchPre(List list,int key);//����key������keyǰ���ĵ�ַ
int Len(List list);                //��������
void Delete_pos(List list,int k);  //ɾ����k�����
void Delete_end(List list,int k);  //ɾ��������k�����
void Rever_List(List list);        //���õ�����
void Rever_L(List list);           //������淴
bool IsRing(List list);            //�ж��Ƿ����
int Ring_len(List list);           //�󻷵ĳ���
Node *Ring_node(List list);        //����뻷�ĵ�һ�����
//ֻ������������ĳ�����p(�ǿս��)����pǰ�����һ����㡣
void Insert_p(Node *p,int val);
//��֪��������ĵ����� A,B ��C �ֱ�洢��һ�����ϣ�����㷨ʵ�� A��=A�ȣ�B��C�� ��
//��ʹ���ṹ A �Ա��ֵ�����Ҫ���㷨��ʱ�临�Ӷ�Ϊ O(|A|+|B|+|C|)��
Node *Fun(List a,List b,List c);
//ֻ������������ĳ�����p(�������һ����㣬��p->next!=NULL)ָ�룬ɾ���ý�㡣 
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

Node *Insert_head(List list,int val)//ͷ��
{
	Node *p = BuyNode(val);

	p->next = list->next;
	list->next = p;

	return list;
}

Node *Insert_tail(List list,int val)//β��
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

Node *Search(List list,int key)//����key������key�ĵ�ַ
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

Node *SearchPre(List list,int key)//����key������keyǰ���ĵ�ַ
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

int Len(List list)//��������
{
	int len = 0;
	while(list->next != NULL)
	{
		len++;
		list = list->next;
	}

	return len;
}

void Delete_pos(List list,int k)//ɾ����k�����
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

void Delete_end(List list,int k)//ɾ��������k�����
{
	int pos = Len(list) - k + 1;
	Delete_pos(list,pos);
}

//ֻ������������ĳ�����p(�������һ����㣬��p->next!=NULL)ָ�룬ɾ���ý�㡣 
void Delete_node(Node *p)
{
	while(p->next != NULL)
	{
		p->data = p->next->data;
		p = p->next;
	}
	free(p);
}

void Rever_List(List list)  //���õ�����
{
	Node *p = list->next;
	Node *q = p;
	int tmp = p->data;              //��ǵ�һ������

	while(p->next != NULL)
	{
		Insert_head(list,p->next->data);//�ѵ�һ������֮������� ͷ��
		p = p->next;
	}

	while(q->data != tmp)       //�ҵ���ǵ�����
	{
		q = q->next;
	}

	p = q;
	Destroy(p);             //ɾ�����֮�������
	q->next = NULL;

}

void Rever_L(List list) //������淴
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

bool IsRing(List list) //�ж��Ƿ����
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

int Ring_len(List list) //�󻷵ĳ���
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
	while(p != q->next)  //q�Ⱥ��ƶ���һ��������++len
	{
		q = q->next;
		++len;
	}
	return len;

}

Node *Ring_node(List list)//����뻷�ĵ�һ�����
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

//ֻ������������ĳ�����p(�ǿս��)����pǰ�����һ����㡣
void Insert_p(Node *p,int val)
{
	Insert_tail(p,val); //β��

	p->next->data = p->data;
	p->data = val;
}

//��֪��������ĵ����� A,B ��C �ֱ�洢��һ�����ϣ�����㷨ʵ�� A��=A�ȣ�B��C�� ��
//��ʹ���ṹ A �Ա��ֵ�����Ҫ���㷨��ʱ�临�Ӷ�Ϊ O(|A|+|B|+|C|)��
Node *Fun(List a,List b,List c)
{
	assert(a!=NULL && b!=NULL && c!=NULL);
	Node *pa = a->next;  //pa��a��һ��
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
		//Insert_head(list,i); //ͷ��
		Insert_tail(list,i);  //β��
	}

	//Delete_pos(list,13);  //ɾ����k�����
	//Delete_pos(list,3);
	//Delete_end(list,13);  //ɾ��������k�����
	//Delete_end(list,3);

	Show(list);

	Rever_L(list);   //��������淴

	Show(list);

	printf("�������� = %d\n",Len(list));

	Destroy(list);


	
	/*
	List a,b,c;

	InitNode(&a);
	InitNode(&b);
	InitNode(&c);
	for(int i=1;i<=8;++i)
	{
		//Insert_head(list,i); //ͷ��
		Insert_tail(a,i);  //β��
	}
	for(int i=3;i<=10;++i)
	{
		//Insert_head(list,i); //ͷ��
		Insert_tail(c,i);  //β��
	}
	for(int i=5;i<=11;++i)
	{
		//Insert_head(list,i); //ͷ��
		Insert_tail(b,i);  //β��
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

