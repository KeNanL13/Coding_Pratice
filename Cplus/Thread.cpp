#include <iostream>
#include <thread>
#include <windows.h>
#include <string>
#include <chrono>
#include <mutex>
std::mutex mux;
int a=0;
// normal function
void func(int a, const std::string b)
{
    for (int i = 1; i <= 12; i++)
    {
        mux.lock();
        std::cout << "第" << i << "个月" << std::endl;
        mux.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
    }
}


void func_Add_a()
{
    for(int i=0;i<10000;i++)
    {
        ++a;
    }
}
// functor
class MyThread
{
public:
    void operator()(int a, const std::string b)
    {
        std::cout << "Hello the Mr." << a << "+" << b << std::endl;
        for (int i = 1; i <= 12; i++)
        {
            std::cout << "第" << i << "个月" << std::endl;
            Sleep(1000);
        }
    }
};

//static function
class MyThread2
{
    public:
    static void func(int a, const std::string b)
    {
        std::cout << "Hello the Mr." << a << "+" << b << std::endl;
        for (int i = 1; i <= 12; i++)
        {
            std::cout << "第" << i << "个月" << std::endl;
            Sleep(1000);
        }
    }
};

//normal function
class MyThread3
{
    public:
    void func(int a,const std::string & b)
    {
        std::cout << "Hello the Mr." << a << "+" << b << std::endl;
        for (int i = 1; i <= 12; i++)
        {
            std::cout << "第" << i << "个月" << std::endl;
            Sleep(1000);
        }
    }
};

int main()
{
    // auto f=[](int a,const std::string & b){
    //     std::cout << "Hello the Mr." << a << "+" << b << std::endl;
    //     for (int i = 1; i <= 12; i++)
    //     {
    //         std::cout << "第" << i << "个月" << std::endl;
    //         Sleep(1000);
    //     }
    // };
    // std::thread t3(f,3,"robot1");
    // //normal function 
    // MyThread3 myth;
    // std::thread t6(&MyThread3::func,&myth,3,"robot2");
    
    // std::cout<<"任务开始.\n";
    // for(int i=0;i<10;i++)
    // {
    //     std::cout<<"执行任务中...\n";
    //     Sleep(1000);
    // }
    // std::cout<<"任务完成.\n";
    // t3.join();
    // t6.join();

    
    // std::thread t1(func_Add_a);
    // std::thread t2(func_Add_a);

    // t1.join();
    // t2.join();
    // std::cout<<"a="<<a<<std::endl;

    std::thread t1(func,1,"robot1");
    std::thread t2(func,2,"robot2");
    std::thread t3(func,3,"robot3");
    std::thread t4(func,4,"robot4");
    std::thread t5(func,5,"robot5");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
 
    return 0;

}