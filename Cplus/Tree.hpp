// 数据结构： 二叉树

#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include "Queue.hpp"
#include "Stack.hpp"

template <typename T>
struct BiTree_Node
{
    T data;
    BiTree_Node<T> *leftChild;
    BiTree_Node<T> *rightChild;
    int flag=-1;       //非递归后序 需要一个标志位 flag=0表示刚访问
};

template <typename T>
class BiTree_List
{
public:
    BiTree_List() { root = Create(); }
    ~BiTree_List() { Release(root); }
    void PreOrder() { PreOrder(root); }
    void InOrder() { InOrder(root); }
    void PostOrder() { PostOrder(root); }
    void LeverOrder();
    void PreOrder_Instant();
    void InOrder_Instant();
    void PostOrder_Instant();
    void CreateNode_Instant(std::string arr,std::vector<T> values);//也可利用标志位实现，这里采用指针的指针实现 arr表示拓展二叉树的前序序列，values表示对应的值

private:
    BiTree_Node<T> *root;
    BiTree_Node<T> *Create();
    void Release(BiTree_Node<T> *biTree);
    void PreOrder(BiTree_Node<T> *biTree);
    void InOrder(BiTree_Node<T> *biTree);
    void PostOrder(BiTree_Node<T> *biTree);
};

template <typename T>
void BiTree_List<T>::PreOrder(BiTree_Node<T> *biTree)
{
    if (!biTree)
    {
        return;
    }
    else
    {
        std::cout << biTree->data << std::endl;
        PreOrder(biTree->leftChild);
        PreOrder(biTree->rightChild);
    }
}

template <typename T>
void BiTree_List<T>::InOrder(BiTree_Node<T> *biTree)
{
    if (!biTree)
    {
        return;
    }
    else
    {
        InOrder(biTree->leftChild);
        std::cout << biTree->data << std::endl;
        InOrder(biTree->rightChild);
    }
}

template <typename T>
void BiTree_List<T>::PostOrder(BiTree_Node<T> *biTree)
{
    if (!biTree)
    {
        return;
    }
    else
    {
        PostOrder(biTree->leftChild);
        PostOrder(biTree->rightChild);
        std::cout << biTree->data << std::endl;
    }
}

template <typename T>
void BiTree_List<T>::LeverOrder()
{
    Queue_Link<BiTree_Node<T> *> queue;
    queue.EnQueue(root);
    while (!queue.Empty())
    {
        BiTree_Node<T> *p = queue.DeQueue();
        if (p->leftChild)
        {
            queue.EnQueue(p->leftChild);
        }
        if (p->rightChild)
        {
            queue.EnQueue(p->rightChild);
        }
        std::cout << "is queue empty :" << queue.Empty() << std::endl;
    }
}

template <typename T>
BiTree_Node<T> *BiTree_List<T>::Create()
{
    BiTree_Node<T> *bt;
    char ch;
    std::cout << "Please input the data:";
    std::cin >> ch;
    std::cout << std::endl;
    if (ch == '#')
        bt = nullptr;
    else
    {
        bt = new BiTree_Node<T>;
        bt->data = ch;
        bt->leftChild = Create();
        bt->rightChild = Create();
    }
    return bt;
}

template <typename T>
void BiTree_List<T>::Release(BiTree_Node<T> *biTree)
{
    if (biTree)
    {
        Release(biTree->leftChild);
        Release(biTree->rightChild);
        delete biTree;
    }
}

template <typename T>
void BiTree_List<T>::PreOrder_Instant()
{
    Stack_Link<BiTree_Node<T> *> stack;
    BiTree_Node<T> *p = root;

    while (!stack.Empty() || p != nullptr)
    {
        while (p != nullptr)
        {
            std::cout << p->data << std::endl;
            stack.Push(p);
            p = p->leftChild;
        }

        if (!stack.Empty())
        {
            p = stack.Pop();
            p = p->rightChild;
        }
    }
}

template <typename T>
void BiTree_List<T>::InOrder_Instant()
{
    Stack_Link<BiTree_Node<T> *> stack;
    BiTree_Node<T> *p = root;

    while (!stack.Empty() || p != nullptr)
    {
        while (p != nullptr)
        {
            stack.Push(p);
            p = p->leftChild;
        }

        if (!stack.Empty())
        {
            p = stack.Pop();
            std::cout << p->data << std::endl;
            p = p->rightChild;
        }
    }
}

template <typename T>
void BiTree_List<T>::PostOrder_Instant()
{
    Stack_Link<BiTree_Node<T>*> stack;
    BiTree_Node<T> * p=root;

    while(!stack.Empty() || p!=nullptr)
    {
        while(p!=nullptr )
        {
            stack.Push(p);
            p->flag=0;
            p=p->leftChild;
        }
        if(!stack.Empty())
        {
            p=stack.GetTop();
            if(p->flag==0)
            {
                p->flag=1;
                p=p->rightChild;
            }else if(p->flag==1)
            {
                std::cout<<p->data<<std::endl;
                p->flag=2;
                stack.Pop();
                p=nullptr;
            }
        }
    }
}

template<typename T>
void BiTree_List<T>::CreateNode_Instant(std::string arr,std::vector<T> values)
{
    
}

/*****************线索树(中序)******************/
enum flag
{
    Child = 0,
    Thread = 1
};
template <typename T>
struct BiTree_ThreadNode
{
    T data;
    BiTree_ThreadNode<T> *leftChild, *rightChild;
    bool lflag, rflag;
};

template <typename T>
class BiTree_Thread
{
public:
    BiTree_Thread();
    ~BiTree_Thread();
    BiTree_ThreadNode<T> *Next(BiTree_ThreadNode<T> *p); // 查找结点 p的后继
    void InOrder();                                      // 中序遍历线索链
private:
    BiTree_ThreadNode<T> *root;
    BiTree_ThreadNode<T> *Create(BiTree_ThreadNode<T> *biTree);
    void ThreadBiTree(BiTree_ThreadNode<T> *biTree, BiTree_ThreadNode<T> *&pre);
    void Release(BiTree_ThreadNode<T> *biTree);
    void inOrder(BiTree_ThreadNode<T> *bt)
    {
        if (bt == nullptr)
            return;
        else
        {
            inOrder(bt->leftChild);
            std::cout << bt->data << std::endl;
            inOrder(bt->rightChild);
        }
    }
};

template <typename T>
BiTree_Thread<T>::BiTree_Thread()
{
    root = Create(root);
    // inOrder(root);
    BiTree_ThreadNode<T> *pre = nullptr;
    ThreadBiTree(root, pre);
}

template <typename T>
BiTree_Thread<T>::~BiTree_Thread()
{
    Release(root);
}

template <typename T>
BiTree_ThreadNode<T> *BiTree_Thread<T>::Create(BiTree_ThreadNode<T> *biTree)
{
    char ch;
    std::cin >> ch;
    if (ch == '#')
        biTree = nullptr;
    else
    {
        biTree = new BiTree_ThreadNode<T>;
        biTree->data = ch;
        biTree->lflag = 0;
        biTree->rflag = 0;
        biTree->leftChild = Create(biTree->leftChild);
        biTree->rightChild = Create(biTree->rightChild);
    }
    return biTree;
}

template <typename T>
void BiTree_Thread<T>::ThreadBiTree(BiTree_ThreadNode<T> *biTree, BiTree_ThreadNode<T> *&pre)
{

    if (biTree == nullptr)
        return;

    // std::cout<<biTree->data<<std::endl;
    ThreadBiTree(biTree->leftChild, pre);

    if (biTree->leftChild == nullptr)
    {
        biTree->lflag = 1;
        biTree->leftChild = pre;
    }
    if (biTree->rightChild == nullptr)
        biTree->rflag = 1;
    if (pre != nullptr && pre->rflag == 1)
        pre->rightChild = biTree;

    pre = biTree;
    ThreadBiTree(biTree->rightChild, pre);
}

template <typename T>
BiTree_ThreadNode<T> *BiTree_Thread<T>::Next(BiTree_ThreadNode<T> *p)
{

    if (p->rflag == 1)
        p = p->rightChild;
    else
    {
        p = p->rightChild;

        while (p->lflag == 0)
        {
            p = p->leftChild;
        }
    }
    return p;
}
template <typename T>
void BiTree_Thread<T>::InOrder()
{
    std::cout << "Tree InOrder :" << std::endl;
    if (root == nullptr)
    {
        std::cout << "root is nullptr" << std::endl;
        return;
    }
    BiTree_ThreadNode<T> *p = root;
    while (p->leftChild != nullptr)
    {
        p = p->leftChild;
    }
    std::cout << p->data << std::endl;
    while (p->rightChild != nullptr)
    {
        p = Next(p);
        std::cout << p->data << std::endl;
    }
}

template <typename T>
void BiTree_Thread<T>::Release(BiTree_ThreadNode<T> *biTree)
{
    if (biTree != nullptr)
    {
        Release(biTree->leftChild);
        Release(biTree->rightChild);
        delete biTree;
    }
}

void Tree_Test()
{
    /**********基本树********/
    BiTree_List<char> tree;
    // std::cout<<"PreOrder :"<<std::endl;
    // tree.PreOrder();
    // std::cout<<"InOrder :"<<std::endl;
    // tree.InOrder();
    // std::cout<<"PostOrder :"<<std::endl;
    // tree.PostOrder();
    // std::cout<<"leverOrder :"<<std::endl;
    // tree.LeverOrder();
    std::cout << "PreOrder instant :" << std::endl;
    tree.PreOrder_Instant();
    std::cout<<"Inorder instant :"<<std::endl;
    tree.InOrder_Instant();
    std::cout<<"PostOrder instant :"<<std::endl;
    tree.PostOrder_Instant();

    /*******线索树*********/
    // BiTree_Thread<char> tree;
    // std::cout << "already initialize tree" << std::endl;
    // tree.InOrder();
}

#endif