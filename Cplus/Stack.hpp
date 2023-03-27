//类描述：
//数据结构类型：顺序栈、共享栈、链栈
//是否测试过：否
#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <assert.h>

template <typename T>
class Stack_Seqential//基本顺序栈
{
public:
    Stack_Seqential();//构造函数
    ~Stack_Seqential();//析构函数
    void Push(T x);//入栈操作
    T Pop();//出栈操作
    T GetTop();//获得栈顶数据
    int Empty();//判断栈是否为空

private:
    T * m_data=nullptr;//数据指针
    const int m_stackSize=10;//栈大小
    int m_top;//指向栈顶
};

template<typename T>
Stack_Seqential<T>::Stack_Seqential()
{
    m_data=new T[m_stackSize];
    m_top=-1;
}

template<typename T>
Stack_Seqential<T>::~Stack_Seqential()
{
    delete[] m_data;
    m_data=nullptr;
    // m_top=-1;
}

template<typename T>
void Stack_Seqential<T>::Push(T x)
{
    assert(m_top<m_stackSize-1);
    m_data[++m_top]=x;
}

template<typename T>
T Stack_Seqential<T>::Pop()
{
    assert(m_top>-1);
    T value=m_data[m_top--];
    return value;
}

template<typename T>
T Stack_Seqential<T>::GetTop()
{
    assert(m_top>-1);
    return m_data[m_top];
}

template<typename T>
int Stack_Seqential<T>::Empty()
{  
    return m_top==-1?1:0;
}
/*******************************************************************************************************/
template<typename T>
class Stack_Share
{
    public:
    Stack_Share();
    ~Stack_Share();
    void Push(int i,T x);
    T Pop(int i);
    T GetTop(int i);
    int Empty(int i);

    private:
    T * m_data=nullptr;
    int m_top1,m_top2;
    const int m_StackSize=100;
};

template<typename T>
Stack_Share<T>::Stack_Share()
{
    m_data=new T[m_StackSize];
    m_top1=-1;
    m_top2=m_StackSize;
}

template<typename T>
Stack_Share<T>::~Stack_Share()
{
    delete[] m_data;
    m_data=nullptr;
    // m_top1=-1;
    // m_top2=m_StackSize;
}

template<typename T>
void Stack_Share<T>::Push(int i,T x)
{
    assert(m_top2-m_top1>0);
    int top=(i==0?++m_top1:--m_top2);
    m_data[top]=x;
    return;
}

template<typename T>
T Stack_Share<T>::Pop(int i)
{
    // assert(m_top1!=m_top2);
    i==0?assert(m_top1>-1):assert(m_top2<m_StackSize);
    int top=i==0?m_top1--:m_top2++;
    return m_data[top];
}

template<typename T>
T Stack_Share<T>::GetTop(int i)
{
    i==0?assert(m_top1>-1):assert(m_top2<m_StackSize);
    int top=i==0?m_top1:m_top2;
    return m_data[top];
}
template<typename T>
int Stack_Share<T>::Empty(int i)
{
    return i==0?(m_top1==-1?1:0) :(m_top2==m_StackSize?1:0) ;
}
/********************************************************************************************************/
template<typename T>
struct Stack_Node
{
    T value;
    Stack_Node<T> * next;

};

template<typename T>
class Stack_Link
{
public:
    Stack_Link();
    ~Stack_Link();
    void Push(T x);
    T Pop();
    T GetTop();
    int Empty();
    private:
    Stack_Node<T> * m_top=nullptr;

};

template<typename T>
Stack_Link<T>::Stack_Link()
{

}
template<typename T>
Stack_Link<T>::~Stack_Link()
{
   Stack_Node<T> * p=m_top;
   while(m_top)
   {
    m_top=m_top->next;
    delete p;
   }
}
template<typename T>
void Stack_Link<T>::Push(T x)
{
    
    Stack_Node<T> *p=new Stack_Node<T>;
    p->value=x;
    p->next=m_top;
    m_top=p;
   
}

template<typename T>
T Stack_Link<T>::Pop()
{
    Stack_Node<T>*p=m_top;
    m_top=m_top->next;
    T value=p->value;
    delete p;
    return value;
}

template<typename T>
T Stack_Link<T>::GetTop()
{
    assert(m_top!=nullptr);
    return m_top->value;
}
template<typename T>
int Stack_Link<T>::Empty()
{
    return m_top==nullptr?1:0;
}

void Stack_Test()
{
    /*顺序栈测试*/
    Stack_Seqential<int > stack_seqential;
    for(int i=0;i<10;i++)
    {
        stack_seqential.Push(i);
    }

    for(int i=0;i<5;i++)
    {
        std::cout<<"出栈："<<stack_seqential.Pop()<<std::endl;
    }

    std::cout<<"目前栈顶的数是："<<stack_seqential.GetTop();

    while (!stack_seqential.Empty())
    {
        stack_seqential.Pop();
    }
    std::cout<<"是否栈为空 : "<<stack_seqential.Empty();
    /*共享栈测试*/
    Stack_Share<int> stack_share;
    for(int i=0;i<10;i++)
    {
        stack_share.Push(0,i);
    }
    for(int i=0;i<10;i++)
    {
        stack_share.Push(1,i);
    }
    std::cout<<"第一个栈的栈顶："<<stack_share.GetTop(0)<<std::endl;
    std::cout<<"第二个栈的栈顶："<<stack_share.GetTop(1)<<std::endl;
    std::cout<<"第一个栈的数:"<<std::endl;
    while (!stack_share.Empty(0))
    {
        std::cout<<stack_share.Pop(0)<<"\t";
    }
    std::cout<<std::endl;
    std::cout<<"第二个栈的数："<<std::endl;
    while(!stack_share.Empty(1))
    {
        std::cout<<stack_share.Pop(1)<<"\t";
    }
    std::cout<<std::endl;
    /*链栈测试*/
    Stack_Link<int> stack_link;
    for(int i=0;i<10;i++)
    {
        stack_link.Push(i);
    }
    std::cout<<"栈顶的数是："<<stack_link.GetTop()<<std::endl;
    
    std::cout<<"栈内的数字为："<<std::endl;
    while(!stack_link.Empty())
    {
        std::cout<<stack_link.Pop()<<"\t";
    }
       
}
#endif