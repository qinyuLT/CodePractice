template<class Tpye>
class LinkList{

protected:
	typedef struct LinkNode{         //������
		Type data;                   
		struct LinkNode* next;
	};

public:
	LinkList();
	~LinkList();
	static LinkNode *Buynode();
	static void Freenode(LinkNode *p);

public:
	int empty();                        //�ж������Ƿ�Ϊ��
	void push_back(const Type& value);  //β��
	void pop_back;                      //βɾ
	void push_front(const Type& value); //ͷ��
	void pop_front();                   //ͷɾ
	void reverse();                     //���õ�����
	void show_list();                   //��ʾ������Ԫ��

private:
	LinkNode *head;
};

