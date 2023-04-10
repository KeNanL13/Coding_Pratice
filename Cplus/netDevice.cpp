#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>

struct Flow
{
    int id;
    int s;
    int t_In;
    int t_Out;
};

std::vector<Flow *> result;

class Port
{
public:
    Port(int id, int b) : t_sum(0), s_sum(b), port_id(id), m_BandWidth(b)
    {
    }
    ~Port()
    {
        // for (auto x : m_flows)
        // {
        //     delete x;
        //     x = nullptr;
        // }
        // m_flows.clear();
    }

    int GetResidualTime() { return t_sum; }
    int GetResidualBand() { return s_sum; }
    int GetPortId() { return port_id; }
    int GetPortBandWidth() { return m_BandWidth; }
    int GetWaitNum() { return waitList.size(); }
    int GetEvaluation()
    {
        int evaluation = 0;
        for (auto x : m_flows)
        {
            evaluation += (x->s * x->t_Out);
        }
        evaluation += wait_evaluate;
        return evaluation;
    }
    bool IsPortEmpty()
    {
        return m_flows.size() == 0;
    }
    // 更新Flow信息
    void Update()
    {
        t_sum -= m_flows.size(); // 剩余总时间更新
        // 每个正在发送的flow时间更新
        for (std::list<Flow *>::iterator it = m_flows.begin(); it != m_flows.end(); it++)
        {
            // std::cout<<(*it)->t_Out<<std::endl;
            (*it)->t_Out--;
            if ((*it)->t_Out == 0)
            {
                // std::cout << "Flow_id:" << (*it)->id << "\tPort_id:" << port_id << "\tstart_time:" << (*it)->t_In << std::endl;
                result.push_back((*it));
                s_sum += (*it)->s;
                m_flows.remove(*it);
            }
        }

        // //查询等待区
        while (!waitList.empty() && waitList.front()->s < s_sum)
        {
            m_flows.push_front(waitList.front()); // 加入发送区
            // 更新剩余带宽和总时间消耗
            s_sum -= waitList.front()->s;
            wait_evaluate -= (waitList.front()->s * waitList.front()->t_Out); // test
            // t_sum+=waitList.front()->t_Out;
            waitList.pop(); // 退出等待区
        }
    }
    // 添加Flow
    void AddFlow(Flow *f)
    {
        if (s_sum < f->s) // 如果剩余带宽不够，则加入等待区,否则加入发送区
        {
            waitList.push(f);
            wait_evaluate += f->s * f->t_Out;
        }
        else
        {
            m_flows.push_back(f);
            s_sum -= f->s;
        }
        t_sum += f->t_Out;
    }

private:
    std::list<Flow *> m_flows; // 存储正在发送中的Flow
    std::queue<Flow *> waitList;
    int t_sum;             // 总剩余时间
    int s_sum;             // port剩余带宽
    int port_id;           // port id
    int m_BandWidth;       // port 带宽容量
    int wait_evaluate = 0; // 评估指标 带宽 * 时间
};
std::vector<Port *> Ports; // 存储port
std::vector<Flow *> flows; // 存储流
// 分割字符串
void SplitString(const std::string &s, std::vector<std::string> &vector, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        vector.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
    {
        vector.push_back(s.substr(pos1));
    }
}

void ReadData(const char path[], int flag)
{
    if (flag != 0 && flag != 1)
    {
        std::cout << "请输入正确的标志位" << std::endl;
        return;
    }
    std::ifstream Data; // 加载流数据
    Data.open(path, std::ios::in);
    if (Data.is_open())
    {
        std::cout << "read data" << std::endl;
        std::string str;
        bool m_flag = false;

        while (std::getline(Data, str))
        {
            if (m_flag)
            {
                std::vector<std::string> v;
                SplitString(str, v, ",");
                if (flag == 0) // 当输入的是流文件时
                {
                    if (v.size() != 4)
                    {
                        std::cout << "read error" << std::endl;
                        break;
                    }
                    Flow *flow = new Flow;
                    flow->id = std::stoi(v[0]);
                    flow->s = std::stoi(v[1]);
                    flow->t_In = std::stoi(v[2]);
                    flow->t_Out = std::stoi(v[3]);
                    flows.push_back(flow);
                }
                else // 当输入的是端口文件时
                {
                    if (v.size() != 2)
                    {
                        std::cout << "read error" << std::endl;
                        break;
                    }
                    int id = std::stoi(v[0]);
                    int band = std::stoi(v[1]);
                    Port *port = new Port(id, band);
                    Ports.push_back(port);
                }
            }
            else
            {
                m_flag = true;
            }
        }
    }
}

int selectPort(Flow *flow, const std::vector<Port *> &ports)
{
    int max = 0;
    int index = -1;
    for (int i = 0; i < ports.size(); i++)
    {
        if (ports[i]->GetResidualBand() > max)
        {
            max = ports[i]->GetResidualBand();
            index = i;
        }
    }

    // int min = INT_MAX;
    // int index = -1;
    // for (int i = 0; i < ports.size(); i++)
    // {
    //     if (ports[i]->GetEvaluation() < min)
    //     {
    //         min = ports[i]->GetEvaluation();
    //         index = i;
    //     }
    // }

    // int min = INT_MAX;
    // int index = -1;
    // for (int i = 0; i < ports.size(); i++)
    // {
    //     if (ports[i]->GetResidualTime() < min)
    //     {
    //         min = ports[i]->GetResidualTime();
    //         index = i;
    //     }
    // }
    // if(flow->s>max)//如果当前没有可以直接加入的端口
    // {
    //     index=-1;
    //     int t_min=INT_MAX;
    //     for(int i=0;i<ports.size();i++)
    //     {
    //         if(ports[i]->GetEvaluation()<t_min)
    //         {
    //             std::cout<<"evaluation"<<i<<":"<<ports[i]->GetEvaluation()<<"\tmin="<<t_min<<std::endl;
    //             t_min=ports[i]->GetEvaluation();
    //             index=i;
    //         }
    //     }
    // }
    // std::cout<<"index="<<index<<std::endl;
    return index;
}

int GetMaxBand(const std::vector<Port *> &ports)
{
    int max = 0;
    for (int i = 0; i < ports.size(); i++)
    {
        if (ports[i]->GetResidualBand() > max)
        {
            max = ports[i]->GetResidualBand();
        }
    }
    return max;
}
std::list<Flow *> controlList;
int main(int argv, char **argc)
{
    // 第一步读取数据
    ReadData("./data/flow.txt", 0); // 加载流数据
    ReadData("./data/port.txt", 1); // 加载端口数据
    // 对输入流数据进行排序:按进入时间从小到大排列;
    std::sort(flows.begin(), flows.end(), [=](const Flow *flow1, const Flow *flow2) -> bool
              { return flow1->t_In < flow2->t_In; });

    // test
    // int portMaxBand = 0;
    // for (int i = 0; i < Ports.size(); i++)
    // {
    //     portMaxBand += Ports[i]->GetPortBandWidth();
    // }

    // int test_time = 0;
    // int test_index = 0;
    // Port *testPort = new Port(10, portMaxBand);
    // while (test_index != flows.size() || !testPort->IsPortEmpty())
    // {
    //     testPort->Update();
    //     while (controlList.size() != 0 && testPort->GetResidualBand() > controlList.front()->s)
    //     {
    //         testPort->AddFlow(controlList.front());
    //         controlList.pop_front();
    //     }

    //     while (test_index < flows.size() && flows[test_index]->t_In == test_time)
    //     {
    //         // testPort->AddFlow(flows[test_index]);
    //         // test_index++;
    //         if (testPort->GetResidualBand() >= flows[test_index]->s)
    //         {
    //             testPort->AddFlow(flows[test_index]);
    //         }
    //         else
    //         {
    //             controlList.push_back(flows[test_index]);
    //         }
    //         test_index++;
    //     }

    //     if (controlList.size() != 0)
    //     {
    //         // std::sort(controlList.begin(), controlList.end(), [=](const Flow *flow1, const Flow *flow2) -> bool
    //         //   { return flow1->t_In < flow2->t_In; });
    //         controlList.sort([=](const Flow *flow1, const Flow *flow2) -> bool
    //                          { return flow1->s * flow1->t_Out < flow2->s * flow2->t_Out; });
    //     }
    //     std::cout << test_index << "\t" << testPort->IsPortEmpty() << std::endl;
    //     test_time++;
    // }
    // std::cout << "test result :" << result.size() << std::endl;
    // std::cout << "time:" << test_time << std::endl;
    // delete testPort;
    // test
    //   时间步进
    int time = 0;
    int index = 0;
    bool exitFlag = 0;

    while (index != flows.size() || !exitFlag)
    {
        // 更新Port
        exitFlag = 1; // 结束标志
        for (int i = 0; i < Ports.size(); i++)
        {
            Ports[i]->Update();
            exitFlag &= Ports[i]->IsPortEmpty();
        }
        // 在controlList中加入
        while (controlList.size() != 0 && GetMaxBand(Ports) > controlList.front()->s)
        {
            int port_index = selectPort(controlList.front(), Ports);
            Ports[port_index]->AddFlow(controlList.front());
            controlList.pop_front();
        }

        // 添加当前时间点的flow
        while (index < flows.size() && flows[index]->t_In == time)
        {
            // int port_index = selectPort(flows[index], Ports);
            // Ports[port_index]->AddFlow(flows[index]);
            // index++;
            int maxBand = GetMaxBand(Ports);
            if (flows[index]->s > maxBand)
            {
                controlList.push_back(flows[index]);
            }
            else
            {
                int port_index = selectPort(flows[index], Ports);
                Ports[port_index]->AddFlow(flows[index]);
            }
            index++;
        }
        if (controlList.size() != 0)
        {
            // std::sort(controlList.begin(), controlList.end(), [=](const Flow *flow1, const Flow *flow2) -> bool
            //   { return flow1->t_In < flow2->t_In; });
            controlList.sort([=](const Flow *flow1, const Flow *flow2) -> bool
                             //   { return flow1->s*flow1->t_Out < flow2->s*flow2->t_Out; });
                               { return flow1->s < flow2->s; });
                            //  { return flow1->t_Out <  flow2->t_Out; });
        }

        ++time; // 时间步进
    }

    std::cout << "total time:" << time << std::endl;
    std::cout << "result size:" << result.size() << std::endl;

    for (auto x : flows)
    {
        delete x;
        x = nullptr;
    }
    flows.clear();

    for (auto x : Ports)
    {
        delete x;
        x = nullptr;
    }
    Ports.clear();
    // system("pause");
    return 0;
}