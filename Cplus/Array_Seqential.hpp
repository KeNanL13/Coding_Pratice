//文件描述：
//数组的顺序表实现
//数据结构：可变数组
//是否测试：是

#ifndef ARRAY_SEQENTIAL_HPP
#define ARRAY_SEQENTIAL_HPP
#include <iostream>
#include <assert.h>

template <typename T>
class Array_Seqential
{
public:
    Array_Seqential();                           // 默认构造函数
    Array_Seqential(const Array_Seqential &arr); // 拷贝构造函数
    ~Array_Seqential();                          // 析构函数

public:
    void push_back(T num);                          // 添加数据操作
    int getSize() const { return m_size; };         // 获得数组大小
    int getCapacity() const { return m_capacity; }; // 获得数组容量
    const T &operator[](int index) const;           // 重载运算符【】
    T &operator[](int index);
    int Locate(T value);         // 查找数据位置
    void insert(int i, T value); // 指定位置插入数据
    T deleteIndexOf(int i);      // 删除指定位置数据
    void PrintList();            // 遍历数组

private:
    int m_size;        // 数组size
    int m_capacity;    // 数组容量
    T *data = nullptr; // 数组指针
};

template <typename T>
Array_Seqential<T>::Array_Seqential()
{
    m_capacity = 10;
    m_size = 0;
}

template <typename T>
Array_Seqential<T>::Array_Seqential(const Array_Seqential &arr)
{
    m_size = arr.getSize();
    m_capacity = arr.getCapacity();
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
    data = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
        data[i] = arr[i];
    }
}

template <typename T>
Array_Seqential<T>::~Array_Seqential()
{

    if (data != nullptr)
    {
        delete[] data;

        data = nullptr;
    }
}

template <typename T>
void Array_Seqential<T>::push_back(T num)
{
    if (data == nullptr)
    {
        data = new T[m_capacity];
        data[m_size++] = num;
        return;
    }
    if (m_size == m_capacity)
    {
        m_capacity <<= 2;
        T *arr = new T[m_capacity];
        for (int i = 0; i < m_size; i++)
        {
            arr[i] = data[i];
        }
        delete[] data;
        data = arr;
        data[m_size++] = num;
    }
    else
    {
        data[m_size++] = num;
    }
}

template <typename T>
const T &Array_Seqential<T>::operator[](int index) const
{
    assert(index > -1 && index < m_size);

    return data[index];
}

template <typename T>
T &Array_Seqential<T>::operator[](int index)
{
    assert(index > -1 && index < m_size);

    return data[index];
}

template <typename T>
int Array_Seqential<T>::Locate(T value)
{
    for (int i = 0; i < m_size; i++)
    {
        if (value == data[i])
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
void Array_Seqential<T>::insert(int i, T value)
{
    
    assert(i > -1 && i < m_size);
    if (m_size == m_capacity)
    {

        m_capacity <<=2;
        T *arr = new T[m_capacity];
        for (int index = 0; index < m_size; index++)
        {
            arr[index] = data[index];
        }
        delete[] data;
        data = arr;
    }
    for (int j = m_size; j > i; j--)
    {
        data[j] = data[j - 1];
    }
    data[i] = value;
    m_size++;

}

template <typename T>
T Array_Seqential<T>::deleteIndexOf(int i)
{
    assert(i > -1 && i < m_size);
    T temp = data[i];
    for (int j = i; j < m_size - 1; j++)
    {
        data[j] = data[j + 1];
    }
    m_size--;
    return temp;
}

template <typename T>
void Array_Seqential<T>::PrintList()
{
    if (m_size == 0)
    {
        return;
    }
    std::cout << "遍历数组操作：" << std::endl;
    for (int i = 0; i < m_size; i++)
    {
        printf("data[%d] = %d \t",i,data[i]);
        // std::cout << "第" << i << "个数是" << data[i]<<"\t" ;
        if(i%5==0)
        {
            std::cout<<std::endl;
        }
    }
}

void Array_Seqential_Test()
{
    //测试输入功能
    Array_Seqential<int> array;
    for(int i=0;i<10;i++)
    {
        array.push_back(i);
    }
    //测试插入功能
    array.insert(2,14);
    array.insert(4,123);
    //测试删除功能
    array.deleteIndexOf(8);
    array.deleteIndexOf(0);

    //测试拷贝构造函数
    Array_Seqential<int>array2(array);
    std::cout<<"the size of array2 :"<<array.getSize()<<std::endl;
    std::cout<<"the capacity of array2 :"<<array2.getCapacity()<<std::endl;
    array2.PrintList();
    //测试查找数据功能
    std::cout<<"数字7的位置:"<<array2.Locate(7)<<std::endl;
    
}


#endif
