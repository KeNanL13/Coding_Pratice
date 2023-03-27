//文件描述：
//数组的链表实现
//数据结构类型：链表数组
//是否测试过：是

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP
#include <iostream>
#include <assert.h>

template <typename T>
struct Node
{
    T data;
    Node<T> *next;
};

template <typename T>
class Array_List
{

public:
    Array_List();
    Array_List(const Array_List &arr);
    Array_List(T a[], int n);
    ~Array_List();
    int GetLength();
    T Get(int i);
    int Locate(T x);
    void Insert(int i, T value);
    T Delete(int i);
    void PrintList();

private:
    Node<T> *m_head = nullptr;
    int m_length;
};

template <typename T>
Array_List<T>::Array_List()
{
    m_head = new Node<T>;
    m_head->next = nullptr;
    m_length = 0;
}

template <typename T>
Array_List<T>::Array_List(const Array_List &arr)
{
    if (m_head)
    {
        Node<T> *p = m_head;
        while (m_head = m_head->next)
        {
            delete p;
            p = m_head;
        }
        delete p;
    }
    
    m_head = new Node<T>;
    m_head->next=nullptr;
    Node<T> *m_p = m_head;
    Node<T> *p = arr.m_head;
    while (p = p->next)
    {
        Node<T> *node = new Node<T>;
        node->data = p->data;
        node->next = nullptr;
        m_p->next = node;
        m_p = node;
    }
}

template <typename T>
Array_List<T>::Array_List(T a[], int n)
{
    assert(n >= 0);
    m_head = new Node<T>;
    m_head->next = nullptr;
    Node<T> *p = m_head;
    for (int i = 0; i < n; i++)
    {
        p->next = new Node<T>;
        p = p->next;
        p->data = a[i];
        p->next = nullptr;
    }
}

template <typename T>
Array_List<T>::~Array_List()
{
    Node<T> *p = m_head;
    while (m_head = m_head->next)
    {
        delete p;
        p = m_head;
    }
    delete p;
}

template <typename T>
void Array_List<T>::PrintList()
{
    Node<T> *p = m_head;
    int i = 0;
    std::cout << "开始遍历\n";
    while (p = p->next)
    {

        printf("list[%d] = %d\t", i, p->data);
        if (i % 5 == 0)
        {
            std::cout << std::endl;
        }
        i++;
    }
}

template <typename T>
int Array_List<T>::GetLength()
{
    int i = 0;
    Node<T> *p = m_head;
    while (p = p->next)
    {
        i++;
    }
    return i;
}

template <typename T>
T Array_List<T>::Get(int i)
{
    assert(i > -1 && i < GetLength());
    int index = 0;
    Node<T> *p = m_head;
    while (p = p->next)
    {
        if (index == i)
        {
            return p->data;
        }
        index++;
    }
}

template <typename T>
int Array_List<T>::Locate(T x)
{
    int index = 0;
    Node<T> *p = m_head;
    while (p = p->next)
    {
        if (p->data == x)
        {
            return index;
        }
    }
    return -1;
}

template <typename T>
void Array_List<T>::Insert(int i, T value)
{
    assert(i > -1 && i < GetLength());
    int index = 0;
    Node<T> *p = m_head;
    while (p)
    {
        if (index == i)
        {
            Node<T> *node = new Node<T>;
            node->data = value;
            node->next = p->next;
            p->next = node;
            return;
        }
        index++;
        p = p->next;
    }
}

template <typename T>
T Array_List<T>::Delete(int i)
{
    assert(i>-1 && i<GetLength());
    int index = 0;
    Node<T> *p = m_head;
    Node<T> *node = nullptr;
    T value;
    while (p)
    {
        if (index == i)
        {
            node = p->next;
            p->next = node->next;
            break;
        }
        index++;
        p = p->next;
    }
    value = node->data;

    delete node;
    return value;
}

void Array_List_Test()
{
    //测试构造函数
    int a[10]{0,1,2,3,4,5,6,7,8,9};
    Array_List<int> array(a,10);
    
    //测试插入操作
    array.Insert(1,23);
    array.Insert(5,10);
    array.Insert(11,99);
    //测试删除操作
    array.PrintList();
    std::cout<<std::endl;
    std::cout<<"删除数据"<<array.Delete(3)<<"\t位置为:"<<"3\n";
    std::cout<<"删除数据"<<array.Delete(7)<<"\t位置为:"<<"7\n";
    std::cout<<"删除数据"<<array.Delete(10)<<"\t位置为:"<<"10\n";
    array.PrintList();
    //测试拷贝构造函数
    Array_List<int> array2(array);
    std::cout<<std::endl;
    array2.PrintList();
    std::cout<<"The length of array2 : "<<array2.GetLength()<<std::endl;


}


#endif