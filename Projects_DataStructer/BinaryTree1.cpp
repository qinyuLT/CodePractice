#include<iostream>
#include<assert.h>
#include<stdlib.h>
using namespace std;

//  拷贝构造函数
//  重载 operator=
//  创建二叉树（5种创建方法）
//  递归遍历  （先序，中序，后序） 
//  非递归遍历（不用栈、0(1)空间）

template<class Type>
class BinaryTree
{
protected:
    typedef struct BtNode
    {
        Type data;
        BtNode* leftchild;
        BtNode* rightchild;
		BtNode(Type x):data(x),leftchild(NULL),rightchild(NULL){}
    };
    typedef BtNode* PBtree;

public:
    BinaryTree():root(NULL),RefValue(NULL){}
    BinaryTree(const Type &x):root(NULL),RefValue(x){}
    BinaryTree(const BinaryTree &tree)
    {
        root = Copy(tree.root);
    }

    BinaryTree & operator=(BinaryTree &obj)
    {
        if(this != &obj)
        {
            root = Copy(obj.root);
        }
        return *this;
    }

    ~BinaryTree(){}

public:
    void MakeTree(const Type *&str)
    {
        if(NULL == str)
        {
            root = NULL;
        }
        else
        {//5种创建二叉树的方法：中间三种方法终端输入
            root = Create(str);
            //Create1(root);
            //root = Create2();
            //Create3(&root);
            //root = Create4(&str);
        }
    }

    void PreOrder()const
    {
        cout <<endl<< "先序遍历(递归)  : ";
        PreOrder(root);
        cout << endl;
    }
    void InOrder()const
    {
        cout  << "中序遍历(递归)  : ";
        InOrder(root);
        cout << endl;
    }
    void PastOrder()const
    {
        cout  << "后序遍历(递归)  : ";
        PastOrder(root);
        cout << endl;
    }
/////////////////////////////////////////////////////
	void NNorePreOrder()const
    {
        cout <<endl<< "先序遍历(非递归，不用栈)  : ";
        NNorePreOrder(root);
        cout << endl;
    }
    void NNoreInOrder()const
    {
        cout  << "中序遍历(非递归，不用栈)  : ";
        NNoreInOrder(root);
        cout << endl;
    }
    void NNorePastOrder()const
    {
        cout  << "后序遍历(非递归，不用栈)  : ";
        NNorePastOrder(root);
        cout << endl;
    }
private:
    static BtNode* Buynode()
    {
        BtNode *s = (BtNode*)malloc(sizeof(BtNode));
        assert(s != NULL);
        memset(s,0,sizeof(BtNode));

        return s;
    }

    static void Freenode(BtNode *p)
    {
        free(p);
    }

    BtNode *Create(const Type *&str)
    {
        if(*str == RefValue)return NULL;
        else
        {
            BtNode *s = Buynode();
            s->data = *str;
            s->leftchild = Create(++str);
            s->rightchild = Create(++str);

            return s;
        }
    }

    void Create1(BtNode *&p)
    {
        Type x;
        cin>>x;
        if(x == RefValue) p = NULL;
        else
        {
            p = Buynode();
            p->data = x;
            Create1(p->leftchild);
            Create1(p->rightchild);
        }
    }

    BtNode *Create2()
    {
        Type x;
        BtNode *s=NULL;
        cin>>x;

        if(x != RefValue)
        {
            s = Buynode();
            s->data = x;
            s->leftchild = Create2();
            s->rightchild= Create2();
        }
        return s;
    }

    void Create3(BtNode **p)
    {
        Type x;
        cin>>x;

        if(x == RefValue) p=NULL;
        else
        {
            *p= Buynode();
            (*p)->data = x;
            //Create3(&(*p)->leftchild); //两种写法都可以
            Create3(&(**p).leftchild);
            Create3(&(**p).rightchild);
        }
    }

    BtNode *Create4(const Type **str)
    {
        BtNode *s = NULL;
        if(**str != RefValue)
        {
            s = Buynode();
            s->data = **str;
            s->leftchild = Create4(&++*str);
            s->rightchild= Create4(&++*str);
        }
        return s;
    }
/////////////////////////////////////////////////////////
	static void NNorePreOrder(BtNode *root)
    {
		if(root == NULL)return;
		BtNode *cur = root;
		BtNode *prev = NULL;

		while(cur != NULL)
		{
			if(cur->leftchild == NULL)
			{
				cout<<cur->data<<" ";
				cur = cur->rightchild;
			}
			else
			{
				prev = cur->leftchild;
				while(prev->rightchild != NULL && prev->rightchild != cur)
					prev = prev->rightchild;

				if(prev->rightchild == NULL)
				{
					cout<<cur->data<<" "; //中序和先序只是输出位置不同
					prev->rightchild = cur;
					cur = cur->leftchild;
				}
				else
				{
					prev->rightchild = NULL;
					cur = cur->rightchild;
				}
			}
		}
    }

    static void NNoreInOrder(BtNode *root)
    {
		if(root == NULL)return;
		BtNode *cur = root;
		BtNode *prev = NULL;

		while(cur != NULL)
		{
			if(cur->leftchild == NULL)
			{
				cout<<cur->data<<" ";
				cur = cur->rightchild;
			}
			else
			{
				prev = cur->leftchild;
				while(prev->rightchild != NULL && prev->rightchild != cur)
					prev = prev->rightchild;

				if(prev->rightchild == NULL)
				{
					prev->rightchild = cur;
					cur = cur->leftchild;
				}
				else
				{
					prev->rightchild = NULL;
					cout<<cur->data<<" ";//中序和先序只是输出位置不同
					cur = cur->rightchild;
				}
			}
		}
    }
	
	static void Reserve(BtNode *from,BtNode *to)
	{
		if(from == to)
			return;
		BtNode *m = from,*n=from->rightchild,*o;
		while(true)
		{
			o = n->rightchild;
			n->rightchild = m;
			m = n;
			n = o;
			if(m == to)
				break;
		}
	}

	static void PrintReverse(BtNode *from,BtNode *to)
	{
		Reserve(from,to);
		BtNode *p = to;
		while(true)
		{
			cout<<p->data<<" ";
			if(p == from)
				break;
			p = p->rightchild;
		}
		Reserve(to,from);
	}

    static void NNorePastOrder(BtNode *root)
    {
        BtNode newRoot(0);//后序遍历需要创建一个新根
		newRoot.leftchild = root;
		BtNode *cur = &newRoot;
		BtNode *prev = NULL;

		while(cur)
		{
			if(cur->leftchild == NULL)
			{
				cur = cur->rightchild;
			}
			else
			{
				prev = cur->leftchild;
				while(prev->rightchild != NULL && prev->rightchild != cur)
					prev = prev->rightchild;

				if(prev->rightchild == NULL)
				{
					prev->rightchild = cur;
					cur = cur->leftchild;
				}
				else
				{
					PrintReverse(cur->leftchild,prev);
					prev->rightchild = NULL;
					cur = cur->rightchild;
				}
			}
		}
    }
///////////////////////////////////////////////////////////
    static void PreOrder(BtNode *p)
    {
        if(NULL != p)
        {
            cout<<p->data<<"  ";
            PreOrder(p->leftchild);
            PreOrder(p->rightchild);
        }
    }

    static void InOrder(BtNode *p)
    {
        if(NULL != p)
        {
            InOrder(p->leftchild);
            cout<<p->data<<"  ";
            InOrder(p->rightchild);
        }   
    }

    static void PastOrder(BtNode *p)
    {
        if(NULL != p)
        {
            PastOrder(p->leftchild);
            PastOrder(p->rightchild);
            cout<<p->data<<"  ";
        }
    }
///////////////////////////////////////////////////////////
    static BtNode *Copy(const BtNode *p)
    {
        BtNode *newroot;

        if(NULL == p)return NULL;
        else
        {
            newroot = Buynode();
            newroot->data = p->data;
            newroot->leftchild  = Copy(p->leftchild);
            newroot->rightchild = Copy(p->rightchild);

            return newroot;
        }
    }

private:
    BtNode* root;
    Type    RefValue;
};

int main()
{
    BinaryTree<char> mytree('#');
    char *str="ABC##DE##F##G#H##";

    mytree.MakeTree(str);
	//递归遍历
    mytree.PreOrder();
    mytree.InOrder();
    mytree.PastOrder();

	//非递归遍历（不用栈）
	mytree.NNorePreOrder();
	mytree.NNoreInOrder();
	mytree.NNorePastOrder();

    BinaryTree<char> youtree(mytree);//拷贝构造
    youtree.PreOrder();
    youtree.InOrder();
    youtree.PastOrder();

    BinaryTree<char> histree;
    histree=mytree;                  //赋值语句（重载operator=方法）
    histree.PreOrder();
    histree.InOrder();
    histree.PastOrder();

    return 0;
}