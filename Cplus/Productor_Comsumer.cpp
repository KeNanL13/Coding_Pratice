#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <deque>
#include <queue>
#include <condition_variable>

class AA
{
private:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::queue<std::string, std::deque<std::string>> m_q;
    bool m_flag=false;
    
public:
    // void End(){flag=true;}
    void InCache(int num,bool isLast)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (int i = 0; i < num; i++)
        {
            static int b = 1;
            std::string message = std::to_string(b++) + "members";
            m_q.push(message);
        }
        // m_cond.notify_one();
        m_cond.notify_all();
        m_flag=isLast;
    }

    void OutCache()
    {
        bool flag=true;
        while (flag)
        {
            std::string message;
            // {
                std::unique_lock<std::mutex> lock(m_mutex);

                // while (m_q.empty())
                // {
                //     m_cond.wait(lock);
                // }
                m_cond.wait(lock,[this]{return !m_q.empty();});
                message = m_q.front();
                m_q.pop();
            // }
            // std::this_thread::sleep_for(std::chrono::milliseconds(1));
            std::cout << "thread:" << std::this_thread::get_id() << "," << message << std::endl;
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            // if(m_q.empty() && m_flag){
            //     std::cout<<"thread id:"<<std::this_thread::get_id()<<std::endl;
            //     std::cout<<"trigger"<<std::endl;
            //     flag=false;}
            
        }
    }
};

int main()
{
    AA aa;

    std::thread t1(&AA::OutCache, &aa);
    std::thread t2(&AA::OutCache, &aa);
    std::thread t3(&AA::OutCache, &aa);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    aa.InCache(3,false);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    aa.InCache(5,true);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}