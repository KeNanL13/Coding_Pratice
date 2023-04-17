#ifndef BISEARCHTREE_HPP
#define BISEARCHTREE_HPP
//二叉排序树
//实现插入、删除、查找功能
//TODO：二叉树的平衡
#include <iostream>
#include <vector>
#include <queue>
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
    void Insert(T value)
    {
        BiNode<T> *node = new BiNode<T>;
        node->data=value;
        node->left=nullptr;
        node->right=nullptr;
        InsertNode(root,node);
    }
    void InsertNode(BiNode<T> *&r, BiNode<T> *node);
    void DeleteNode(BiNode<T> *p, BiNode<T> *f); // 删除结点f的左节点p
    BiNode<T> *SearchBST(BiNode<T> *r, T value);
    BiNode<T> *GetRoot() { return root; }
    BiNode<T> *&GetRootRef() { return root; }
    void LevelOrder();

private:
    BiNode<T> *root;
};

template <typename T>
BiSortTree<T>::BiSortTree(std::vector<T> v)
{
    root = nullptr;
    for (int i = 0; i < v.size(); i++)
    {
        BiNode<T> *node = new BiNode<T>;
        node->data = v[i];
        node->left = nullptr;
        node->right = nullptr;
        InsertNode(root, node);
    }
}

template <typename T>
BiSortTree<T>::~BiSortTree()
{
    delete root;
}

template <typename T>
void BiSortTree<T>::InsertNode(BiNode<T> *&r, BiNode<T> *node)
{
    if (r == nullptr)
        r = node;
    else if (node->data < r->data)
        InsertNode(r->left, node);
    else
        InsertNode(r->right, node);
}

// 删除结点f的左节点p
template <typename T>
void BiSortTree<T>::DeleteNode(BiNode<T> *p, BiNode<T> *f)
{
    if (p->left == nullptr && p->right == nullptr)
    {
        f->left = nullptr;
        delete p;
    }
    else if (p->right == nullptr)
    {
        f->left = p->left;
        delete p;
    }
    else if (p->left == nullptr)
    {
        f->left = p->right;
        delete p;
    }
    else
    {
        // find mininum node and its parent node
        BiNode<T> *m1 = p->right;
        BiNode<T> *mf = p;
        while (m1->left != nullptr)
        {
            mf = m1;
            m1 = m1->left;
        }
        //
        p->data = m1->data;
        if (mf == p)
            mf->right = m1->right;
        else
            mf->left = m1->right;
        delete m1;
    }
}

template <typename T>
BiNode<T> *BiSortTree<T>::SearchBST(BiNode<T> *r, T value)
{
    if (r == nullptr)
        return nullptr;
    if (r->data < value)
    {
        return SearchBST(r->right, value);
    }
    else if (r->data > value)
    {
        return SearchBST(r->left, value);
    }
    else
    {
        return r;
    }
}

template <typename T>
void BiSortTree<T>::LevelOrder()
{
    std::queue<BiNode<T> *> queue;
    queue.push(root);
    while (!queue.empty())
    {
        BiNode<T> *node = queue.front();
        queue.pop();
        if (node->left)
            queue.push(node->left);
        if (node->right)
            queue.push(node->right);
        std::cout << node->data << "\t";
    }
    std::cout << std::endl;
}

void BiSearchTree_Test()
{
    std::vector<int> v;
    v.push_back(55);
    v.push_back(42);
    v.push_back(10);
    v.push_back(70);
    v.push_back(63);
    v.push_back(58);
    v.push_back(83);
    v.push_back(67);
    v.push_back(90);
    v.push_back(45);

    BiSortTree<int> biTree(v);
    biTree.LevelOrder();
    std::cout << "find key 10: " << biTree.SearchBST(biTree.GetRoot(), 10)->data << std::endl;
    std::cout << "find key 45: " << biTree.SearchBST(biTree.GetRoot(), 45)->data << std::endl;
    std::cout << "find key 83: " << biTree.SearchBST(biTree.GetRoot(), 83)->data << std::endl;
    std::cout << "insert key 5:" << std::endl;
    biTree.Insert(5);
    biTree.LevelOrder();
    std::cout<<"delete key 42:"<<std::endl;
    biTree.DeleteNode(biTree.GetRoot()->left,biTree.GetRoot());
    biTree.LevelOrder();
}

#endif