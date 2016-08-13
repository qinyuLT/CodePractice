#include<iostream>
#include<cassert>
#include<cstdlib> //exit
#include<cstring> //memset
#include"Stack.h"
#include"Queue.h"
#include<math.h>
using namespace std;

//      创建二叉树 （先中序，中后序）
//      非递归遍历 （需要使用到栈Stack数据结构）
//      层次遍历   (需要使用到队列Queue数据结构)
//      求二叉树的结点个数，深度
//      查找某个结点是否存在，查找结点的双亲结点
//      判断二叉树是否为满二叉树
//如下函数：
/*  void MakeTreePI(Type *&ps,Type *&is,int n);  //根据先序中序创建二叉树
    void MakeTreeIL(Type *&is, Type *&ls, int n);//根据后序后序创建二叉树

    void NorePreOrder();                         //非递归遍历 
    void NoreInOrder();
    void NorePastOrder();

    void LevelOrder();                           //层次遍历
    void getSize()const;                         //二叉树结点个数
    void getDepth()const;                        //二叉树深度
    void Clear();                                //清空销毁二叉树结点
    BtNode *FindValue(const Type x);             //根据值x查找是否存在结点
    BtNode *FindParent(const BtNode *child);     //根据child结点查询是否存在双亲结点
    bool operator==(const BTree<Type> &bt)const;
    bool operator!=(const BTree<Type> &bt)const;
    bool IsFullBinaryTree1() const;              //非递归 判断是否为满二叉树
    bool IsFullBinaryTree() const;               //  递归 判断是否为满二叉树
*/

template<class T>
T Max(T a, T b)
{
    return a > b ? a : b;
}

template<class Type>
class BTree
{
protected:
    struct BtNode
    {
        Type value;
        BtNode *leftchild;
        BtNode *rightchild;
    };

public:
    typedef BtNode *PBtNode;

private:
    BtNode *root;
    Type  RefValue;  //'#'

    static BtNode *BuyNode()
    {
        BtNode *s = (BtNode*)malloc(sizeof(BtNode));
        assert(s != NULL);
        memset(s, 0, sizeof(BtNode));
        return s;
    }
    static void FreeNode(BtNode *p)
    {
        free(p);
        p = NULL;
    }
    BtNode *CreateTree(const Type *&str)
    {
        if (*str == RefValue)return NULL;
        else
        {
            BtNode *s = BuyNode();
            s->value = *str;
            s->leftchild = CreateTree(++str);
            s->rightchild = CreateTree(++str);
            return s;
        }
    }

    static int findpos(char *is, char x, int n)
    {
        for (int i = 0; i<n; ++i)
        {
            if (is[i] == x)return i;
        }
        return -1;
    }
    static BtNode *CreateTreePI(Type *ps,Type *is, int n)
    {
        BtNode *s = NULL;
        if (n > 0)
        {
            Type x = ps[0];
            s = BuyNode();
            s->value = x;
            int pos = findpos(is, x, n);
            if (pos == -1) exit(1);
            s->leftchild = CreateTreePI(ps + 1, is, pos);
            s->rightchild = CreateTreePI(ps + pos + 1, is + pos + 1, n - pos - 1);
        }
        return s;
    }
    static BtNode *CreateTreeIL(Type *is, Type *ls, int n)
    {
        BtNode *s = NULL;
        if (n > 0)
        {
            Type x = ls[n - 1];
            s = BuyNode();
            s->value = x;
            int pos = findpos(is, x, n);
            if (pos == -1) exit(1);
            s->leftchild = CreateTreeIL(is, ls, pos);
            s->rightchild = CreateTreeIL(is + pos + 1, ls + pos, n - pos - 1);
        }
        return s;
    }

    static void PreOrder(BtNode *p)
    {
            if (p != NULL)
            {
                cout << p->value << "  ";
                PreOrder(p->leftchild);
                PreOrder(p->rightchild);
            }
        }
    static void InOrder(BtNode *p)
    {
        if (p != NULL)
        {
            InOrder(p->leftchild);
            cout << p->value << "  ";
            InOrder(p->rightchild);
        }
    }
    static void PastOrder(BtNode *p)
    {
        if (p != NULL)
        {
            PastOrder(p->leftchild);
            PastOrder(p->rightchild);
            cout << p->value << "  ";
        }
    }

    static void NorePerOrder(BtNode *ptr)
    {
        if (ptr == NULL)return;
        Stack<BtNode*> st;
        st.push(ptr);
        while (!st.empty())
        {
            BtNode *p = NULL;
            st.pop(p);
            cout << p->value << "  ";
            if (p->rightchild != NULL)
            {
                st.push(p->rightchild);
            }
            if (p->leftchild != NULL)
            {
                st.push(p->leftchild);
            }
        }
        cout << endl;
    }
    static void NoreInOrder(BtNode *ptr)
    {
        if (ptr == NULL) return;
        Stack<BtNode*> st;
        BtNode *p = ptr;
        while (!st.empty() || p != NULL)
        {
            while (p != NULL)
            {
                st.push(p);
                p = p->leftchild;
            }
            if (!st.empty())
            {
                st.pop(p);
                cout << p->value << "  ";
                p = p->rightchild;
            }
        }
        cout << endl;
    }
    static void NorePastOrder(BtNode *ptr)
    {
        if (ptr == NULL)return;
        Stack<BtNode*> st;
        BtNode *p = ptr;
        BtNode *tag = NULL;

        while (!st.empty() || p != NULL)
        {
            while (p != NULL)
            {
                st.push(p);
                p = p->leftchild;
            }
            st.gettop(p);
            if (p->rightchild == NULL || p->rightchild == tag)
            {
                cout << p->value << "  ";
                st.pop(p);
                tag = p;
                p = NULL;
            }
            else
            {
                p = p->rightchild;
            }
        }
        cout << endl;
    }

    static void LevelOrder(BtNode *ptr)
    {
        if (ptr == NULL)return;
        Queue<BtNode*> que;
        BtNode *p = ptr;

        que.push(p);
        while (!que.empty())
        {
            que.pop(p);
            cout << p->value << "  ";
            if (p->leftchild != NULL)
            {
                que.push(p->leftchild);
            }
            if (p->rightchild != NULL)
            {
                que.push(p->rightchild);
            }
        }
        cout << endl;
    }

    static int Size(BtNode *ptr)
    {
        if (ptr != NULL)
            return Size(ptr->leftchild) + Size(ptr->rightchild) + 1;
        return 0;
    }
    static int Depth(BtNode *ptr)
    {
        if (ptr != NULL)
            return Max(Depth(ptr->leftchild), Depth(ptr->rightchild)) + 1;
        return 0;
    }

    static void Destroy(BtNode *ptr)
    {
        if (ptr != NULL)
        {
            Destroy(ptr->leftchild);
            Destroy(ptr->rightchild);
            FreeNode(ptr);
            cout << " 销毁结点 ";
        }
    }

    static BtNode *Copy(BtNode *bt)
    {
        BtNode *p = NULL;
        if (bt != NULL)
        {
            p = BuyNode();
            p->value = bt->value;
            p->leftchild = Copy(bt->leftchild);
            p->rightchild = Copy(bt->rightchild);
        }
        return p;
    }

    static BtNode *FindValue(BtNode *p, const Type x)
    {
        if (p == NULL || p->value == x) return p;
        else
        {
            BtNode *s = FindValue(p->leftchild,x);
            if (s == NULL)
            {

                s = FindValue(p->rightchild,x);
            }
            return s;
        }
    }
    static BtNode *FindParent(BtNode *ptr,const BtNode *child)
    {
        if (ptr == NULL || ptr->leftchild == child || ptr->rightchild == child)
        {
            return ptr;
        }
        else
        {
            BtNode *s = FindParent(ptr->leftchild, child);
            if (s == NULL)
            {
                s = FindParent(ptr->rightchild, child);
            }
            return s;
        }
    }

    static bool Equal(BtNode *ap,BtNode *bp)
    {
        if (ap == NULL || bp == NULL) return true;

        if (ap != NULL && bp != NULL
            && ap->value == bp->value
            && Equal(ap->leftchild, bp->leftchild)
            && Equal(ap->rightchild, bp->rightchild))
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    static bool IsFullBT(BtNode *p)
    {
        if (p != NULL)
        {
            return (IsFullBT(p->leftchild) + 1) == (IsFullBT(p->rightchild) + 1);
        }
        return false;
    }

public:
    BTree() :root(NULL) {}
    BTree(const Type &x) :root(NULL), RefValue(x){}
    BTree(const BTree &bt) :root(NULL), RefValue(bt.RefValue)
    {
        root = Copy(bt.root);
    }
    BTree &operator=(const BTree &obj)
    {
        if (this != &obj)
        {
            Destroy(this->root);
            cout << endl;
            this->root = Copy(obj.root);
        }
        return *this;
    }
    ~BTree()
    {
        Clear();
    }

public:

    void MakeTree(const Type *&str)
    {
        cout << "构造二叉树 ：" << str << endl << endl;
        if (str == NULL)
        {
            root = NULL;
        }
        else
        {
            root = CreateTree(str);
        }
    }
    void MakeTreePI(Type *&ps,Type *&is,int n)
    {
        cout << "根据先序: " << ps;
        cout<<" 中序: "<<is <<" 建二叉树" << endl;
        root = CreateTreePI(ps, is, n);
        cout << endl;
    }
    void MakeTreeIL(Type *&is, Type *&ls, int n)
    {
        cout << "根据中序: " << is;
        cout << " 后序: " << ls << " 建二叉树" << endl;
        root = CreateTreeIL(is, ls, n);
        cout << endl;
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

    void NorePreOrder()
    {
        cout << endl << "先序遍历(非递归): ";
        NorePerOrder(root);
    }
    void NoreInOrder()
    {
        cout << "中序遍历(非递归): ";
        NoreInOrder(root);
    }
    void NorePastOrder()
    {
        cout  << "后序遍历(非递归): ";
        NorePastOrder(root);
    }
    void LevelOrder()
    {
        cout << endl << "广度遍历 ： ";
        LevelOrder(root);
    }

    void getSize()const
    {
        cout << " size : ";
        cout << Size(root) << endl;
    }
    void getDepth()const
    {
        cout << "depth : ";
        cout << Depth(root) << endl;
    }
    void Clear()
    {
        Destroy(root);
        root = NULL;
        cout << endl;
    }

    BtNode *FindValue(const Type x)
    {
        cout<<endl << "要查找的值 " << x <<" : " ;
        return (root==NULL)?NULL:FindValue(root, x);
    }
    BtNode *FindParent(const BtNode *child)
    {
        cout << endl << "查找 " << child->value << " 的双亲 : ";
        return (root == NULL || child == NULL || root == child) ?
                NULL : FindParent(root, child);
    }
    bool operator==(const BTree<Type> &bt)const
    {
        return Equal(root, bt.root);
    }
    bool operator!=(const BTree<Type> &bt)const
    {
        return !Equal(this->root,bt.root);
    }
    bool IsFullBinaryTree1() const  //非递归
    {
        if ( (pow(2.0, Depth(root)) - 1) == Size(root) )
        {
            cout << endl << "该树是满二叉树" << endl << endl;
        }
        else
        {
            cout << endl << "该树非满二叉树" << endl << endl;
        }
        return true;
    }
    bool IsFullBinaryTree() const  // 递归
    {
        if (IsFullBT(root))
        {
            cout << endl << "该树是满二叉树" << endl << endl;
        }
        else
        {
            cout << endl << "该树非满二叉树" << endl << endl;
        }
        return true;
    }
};

int main()
{
    BTree<char> mytree('#');
    const char *str = "ABC##DE##F##G#H##";
    const char *str2 = "ABCD#E##F##GH##I##J#K#LM##N##";
    const char *str3 = "ABC##D##EF##G##"; //满二叉树

    mytree.MakeTree(str3);

    mytree.PreOrder();
    mytree.InOrder();
    mytree.PastOrder();

    mytree.NorePreOrder();
    mytree.NoreInOrder();
    mytree.NorePastOrder();

    mytree.LevelOrder();

    mytree.getSize();
    mytree.getDepth();

    mytree.IsFullBinaryTree();

    return 0;
}