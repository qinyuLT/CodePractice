template<class Tpye>
class LinkList{

protected:
	typedef struct LinkNode{         //链表结点
		Type data;                   
		struct LinkNode* next;
	};

public:
	LinkList();
	~LinkList();
	static LinkNode *Buynode();
	static void Freenode(LinkNode *p);

public:
	int empty();                        //判断链表是否为空
	void push_back(const Type& value);  //尾插
	void pop_back;                      //尾删
	void push_front(const Type& value); //头插
	void pop_front();                   //头删
	void reverse();                     //逆置单链表
	void show_list();                   //显示单链表元素

private:
	LinkNode *head;
};

