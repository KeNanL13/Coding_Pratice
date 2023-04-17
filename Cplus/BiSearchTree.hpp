#ifndef BISEARCHTREE_HPP
#define BISEARCHTREE_HPP

#include <iostream>
#include <vector>

template <typename T>
struct BiNode
{
    T data;
    BiNode *left;
    BiNode *right;
};

template <typename T>
class BiSortTree
{
public:
    BiSortTree(std::vector<T> v);
    ~BiSortTree();
    void InsertNode(BiNode<T> * &r, BiNode<T> *node);
    void DeleteNode(BiNode<T> *p, BiNode<T> *f);//删除结点f的左节点p
    BiNode<T> *SearchBST(BiNode<T> *r,T value);

private:
    BiNode<T> *root;
};

template <typename T>
BiSortTree<T>::BiSortTree(std::vector<T> v)
{
    root=nullptr;
    for(int i=0;i<v.size();i++)
    {
        BiNode<T> * node=new BiNode<T>;
        node->data=v[i];
        node->left=nullptr;
        node->right=nullptr;
        InsertNode(root,node);
    }
}

template <typename T>
BiSortTree<T>::~BiSortTree()
{
    delete root;
}

template <typename T>
void BiSortTree<T>::InsertNode(BiNode<T> * & r, BiNode<T> *node)
{
    if(r==nullptr)r=node;
    else if(node->data<r->data) InsertNode(r->left,node);
    else InsertNode(r->right,node);
}

//删除结点f的左节点p
template <typename T>
void BiSortTree<T>::DeleteNode(BiNode<T> *p, BiNode<T> *f)
{
    if(p->left==nullptr && p->right ==nullptr)
    {
        f->left=nullptr;
        delete p;
    }else if(p->right==nullptr )
    {
        f->left=p->left;
        delete p;             
    }else if(p->left==nullptr )
    {
        f->left=p->right;
        delete p;
    }else {
        //find mininum node and its parent node 
        BiNode<T> * m1=p->right;
        BiNode<T> * mf=p;
        while(m1->left!=nullptr)
        {
            mf=m1;
            m1=m1->left;
        }
        //
        p->data=m1->data;
        if(mf==p)mf->right=m1->right;
        else mf->left=m1->right;
        delete m1;
    }
}

template <typename T>
BiNode<T> *BiSortTree<T>::SearchBST(BiNode<T> *r,T value)
{
    if(r==nullptr)return nullptr;
    if(r->data<value)
    {
        return SearchBST(r->right,value);
    }
    else if(r->data>value)
    {
        return SearchBST(r->left,value);
    }else{
        return r;
    }
}

#endif