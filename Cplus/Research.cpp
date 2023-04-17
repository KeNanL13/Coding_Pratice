
#include <iostream>
#include <vector>
#include "Array_List.hpp"
#include <random>

//Sequential Search
int SequentialSearch(std::vector<int> v,int key)
{
    int p=v[0];
    v[0]=key;
    for(int i=v.size()-1;i>=0;i--)
    {
        if(v[i]==key)
        {
            return i;
        }
    }
}

//Binary search
int BinarySearch(std::vector<int> v,int key)
{
    int end=v.size()-1;
    int start=0;
    int p=0;
    while(start<=end)
    {
        p=(start+end)/2;
        if(v[p]>key)
        {
            end=p-1;
        }else if(v[p]<key ){
            start=p+1;
        }
        else{
            return p;
        }
    }
    return 0;

}

//Binary search(recursion)
int BinarySearch2(const std::vector<int>& v,int key,int start,int end)
{
    int temp=(start+end)/2;
    if(v[temp]>key){
        end=temp-1;
    }else if(v[temp]<key)
    {
        start=temp+1;
    }else{
        return temp;
    }
    if(start<end)
    {
        return BinarySearch2(v,key,start,end);
    }
}


int main()
{
    // std::random_device r_d;
    // std::mt19937 r_eng{r_d()};
    // std::cout<<"rd:"<<r_d()<<std::endl;
    // std::uniform_int_distribution<int> randNum(0,100);
    // std::vector<int> vector;
    // int num=100;
    // for(int i=0;i<num;i++)
    // {
    //     vector.push_back(randNum(r_eng));
    //     std::cout<<i<<":"<<vector[i]<<"\t";
    //     if((i+1)%10==0)
    //     {
    //         std::cout<<std::endl;
    //     }
    // }
    
    // std::cout<<"find key: 48, position: "<<SequentialSearch(vector,48)<<std::endl;
    // std::cout<<"find key: 32, position: "<<SequentialSearch(vector,32)<<std::endl;

    std::vector<int> v1;
    for(int i=0;i<100;i++)
    {
        v1.push_back(i);
    }
    std::cout<<"find key: 48, position: "<<BinarySearch2(v1,48,0,v1.size()-1)<<std::endl;
    std::cout<<"find key: 32, position: "<<BinarySearch2(v1,32,0,v1.size()-1)<<std::endl;
    return 0;
}