// 文件描述：
// 数据结构类型：循环队列(顺序存储) 链队列
// front 指向第一个元素的前一个位置
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include <assert.h>

template <typename T>
class Queue_Circle
{
public:
    Queue_Circle();    // 构造函数
    ~Queue_Circle();   // 析构函数
    void EnQueue(T x); // 入队操作
    T DeQueue();       // 出队操作
    T GetQueue();      // 取队头元素
    int Empty();       // 判断是否为空
private:
    T *data = nullptr;
    const int QueueSize = 10;
    int front, rear;
};

template <typename T>
Queue_Circle<T>::Queue_Circle()
{
    data = new T[QueueSize];
    front = 0;
    rear = front;
}
template <typename T>
Queue_Circle<T>::~Queue_Circle()
{
    delete[] data;
}
template <typename T>
void Queue_Circle<T>::EnQueue(T x)
{
    assert((rear + 1) % QueueSize != front);
    rear = (rear + 1) % QueueSize;
    data[rear] = x;
}
template <typename T>
T Queue_Circle<T>::DeQueue()
{
    assert(rear != front);
    front = (front + 1) % QueueSize;
    return data[front];
}
template <typename T>
T Queue_Circle<T>::GetQueue()
{
    assert(rear != front);
    return data[(front + 1) % QueueSize];
}
template <typename T>
int Queue_Circle<T>::Empty()
{
    return rear == front ? 1 : 0;
}
template <typename T>
struct Node
{
    T data;
    Node<T> *next;
};

template <typename T>
class Queue_Link
{
    // struct Node
    // {
    //     T data;
    //     Node<T> *next;
    // };

public:
    Queue_Link();
    ~Queue_Link();
    void EnQueue(T x);
    T DeQueue();
    T GetQueue();
    int Empty();

private:
    Node<T> *m_front, *m_rear;
};

template <typename T>
Queue_Link<T>::Queue_Link()
{
    m_front=new Node<T>;
    m_front->next=nullptr;
    m_rear=m_front;
}

template <typename T>
Queue_Link<T>::~Queue_Link()
{
    m_rear = m_front;
    while (m_front)
    {
        m_front = m_front->next;
        delete m_rear;
        m_rear = m_front;
    }
}

template <typename T>
void Queue_Link<T>::EnQueue(T x)
{
    Node<T> * node=new Node<T>;
    
    node->data=x;
    node->next=nullptr;
    m_rear->next=node;
    m_rear=node;
   
}

template <typename T>
T Queue_Link<T>::DeQueue()
{
    assert(m_front->next!=nullptr);
    if(m_front->next==m_rear)
    {
        m_rear=m_front;
    }
    Node<T> * p=m_front->next;
    m_front->next=p->next;
    T value=p->data;
    delete p;

    return value;
}

template <typename T>
T Queue_Link<T>::GetQueue()
{
    assert(m_front->next!=nullptr);
    return m_front->next->data; 
}

template <typename T>
int Queue_Link<T>::Empty()
{
    return m_front->next==nullptr?1:0;
}

void Queue_Test()
{
    /*循环队列*/
    // Queue_Circle<int> queue;
    /*链表形式队列*/
    Queue_Link<int> queue;
    std::cout<<"入队9个数"<<std::endl;
    for(int i=0;i<9;i++)
    {
        queue.EnQueue(i);
    }
    std::cout<<"出队 5 个数"<<std::endl;
    for(int i=0;i<5;i++)
    {
        std::cout<<queue.DeQueue()<<"\t";
    }
    std::cout<<"入队5 个数"<<std::endl;
    for(int i=10;i<15;i++)
    {
        queue.EnQueue(i);
    }

    std::cout<<"依次出队"<<std::endl;
    while(!queue.Empty())
    {
        std::cout<<queue.DeQueue()<<"\t";
    }
    std::cout<<"队列是否为空："<<queue.Empty()<<std::endl;

    /*链表形式队列*/
    
    
}
#endif