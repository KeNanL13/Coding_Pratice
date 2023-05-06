#include <iostream>
#include <string>
#include <functional>
//普通函数
void Print(int a,std::string str)
{
    std::cout<<"a="<<a<<"\t"<<"str="<<str<<std::endl;
}

//类的静态成员函数
class Print2
{
    public:
    static void Print(int a, std::string str)
    {
        std::cout<<"a="<<a<<"\t"<<"str="<<str<<std::endl;
    }
};

//类的非静态成员
class Print3
{
    public:
    void Print(int a, std::string str)
    {
        std::cout<<"a="<<a<<"\t"<<"str="<<str<<std::endl;
    }
};

//lamda函数
auto print4=[](int a,std::string str){
    std::cout<<"a="<<a<<"\t"<<"str="<<str<<std::endl;
};

//仿函数
class Print5
{
    public:
    void operator()(int a,std::string str)
    {
        std::cout<<"a="<<a<<"\t"<<"str="<<str<<std::endl;
    }
};

//可转换为函数指针的类对象
class Print6
{
    using PRINT_TYPE = void(*)(int ,std::string );
    public:
    operator PRINT_TYPE()
    {
        return Print;
    }
};

//实现类似thread构造函数
template<typename Fn,typename ...Args>
auto Show(Fn && f,Args&&... args) ->decltype(std::bind(std::forward<Fn>(f),std::forward<Args>(args)...))
{
    auto f1=std::bind(std::forward<Fn>(f),std::forward<Args>(args)...);
    f1();

    std::cout<<"finish show\n";
    return f1;
}

int main()
{
    Print3 p;
    Print6 p2;
    std::function<void(int,std::string)> f1=Print;//普通函数
    std::function<void(int ,std::string)> f2=Print2::Print;//类的静态成员函数
    std::function<void(Print3&,int,std::string)>f3=Print3::Print;//类的非静态成员函数
    std::function<void(int,std::string)>f4=print4;//匿名函数
    std::function<void(int,std::string)>f5=Print5();//仿函数
    std::function<void(int,std::string)>f6=p2;//可被转换成函数指针的类对象
    // std::function<void(int,std::string)>f6=Print6();
    f1(1,"普通函数");
    f2(2,"类的静态成员函数");
    f3(p,3,"类的非静态成员函数");
    f4(4,"匿名函数");
    f5(5,"仿函数");
    f6(6,"可被转换成函数指针的类对象");

    //bind
    std::function<void(int,std::string)> b1=std::bind(Print,std::placeholders::_1,std::placeholders::_2);
    std::function<void(int,std::string)> b2=std::bind(Print2::Print,std::placeholders::_1,std::placeholders::_2);
    std::function<void(Print3&,int,std::string)> b3=std::bind(Print3::Print,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    std::function<void(int,std::string)>b4=std::bind(print4,std::placeholders::_1,std::placeholders::_2);
    std::function<void(int,std::string)>b5=std::bind(Print5(),std::placeholders::_1,std::placeholders::_2);
    std::function<void(int,std::string)>b6=std::bind(p2,std::placeholders::_1,std::placeholders::_2);
    b1(1,"bind:普通函数");
    b2(2,"bind:类的静态成员函数");
    b3(p,3,"bind:类的非静态成员函数");
    b4(4,"bind:匿名函数");
    b5(5,"bind:仿函数");
    b6(6,"bind:可被转换成函数指针的类对象");

    //show
    Show(Print,1,"show");


    return 0;
}