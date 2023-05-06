#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

template <typename T>
void show(T s)
{
    std::cout<<"Hello,"<<s<<"! What a day~"<<std::endl;
}

void Print()
{
    std::cout<<"program end"<<std::endl;
}

template <typename T,typename ...Args>
void Print(T arg,Args...args)
{
    std::cout<<"paramters:"<<arg<<std::endl;
    show(arg);
    std::cout<<"still have "<<sizeof...(args)<<" parameters need to be done "<<std::endl;
    Print(args...);
}

template<typename...Args>
void func(const std::string & str,Args...args)
{
    std::cout<<str<<std::endl;
    Print(args...);
    std::cout<<"over\n";
}

int main(int argv,char ** argc)
{
    Print("p1",4,"p2");
    // func("start.","people1",8,"people2",3);
    return 0;
}