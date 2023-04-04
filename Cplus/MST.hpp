//文件描述
//最小生成树算法 ：Prim 算法和 Kruskal 算法
//对应的存储结构： 邻接矩阵 和 边集数组
#ifndef MST_HPP
#define MST_HPP
#include <iostream>
#include <vector>
#include <assert.h>
#include <stack>
#include <string>
#include <queue>


struct PrimEdge
{
    int adjvex;
    int lowCost;
};

template <typename T> 
class Graph_Prim
{
private:
    std::vector<T> vertex;
    std::vector<std::vector<int>> arc;
public:
    Graph_Prim(std::vector<T> v,int e);
    void BFSTraverse(int v);
    void DFSTraverse(int v);
    void MST_Prim();
    int FindMinCost(const std::vector<PrimEdge>  &p);
    void UpdataShortEdge(std::vector<PrimEdge>  & p ,int j);
    ~Graph_Prim();
};

template<typename T>
Graph_Prim<T>::Graph_Prim(std::vector<T> v,int e)
{
    vertex=v;
    for(int i=0;i<vertex.size();i++)
    {
        std::vector<int> temp;
        for(int j=0;j<vertex.size();j++)
        {
         temp.push_back(-1);   
        }
        arc.push_back(temp);
    }

    for(int i=0;i<e;i++)
    {
        int x,y,w;
        std::cout<<"input the node of "<<i<<" arc:"<<std::endl;
        std::cin>>x>>y;
        std::cout<<"input the weight:";
        std::cin>>w;
        arc[x][y]=w;//有向图
        arc[y][x]=w;//无向图

    }
}

template<typename T>
void Graph_Prim<T>::BFSTraverse(int v)
{
    assert(v<vertex.size());
    std::vector<int>visited;
    for(int i=0;i<vertex.size();i++)
    {
        visited.push_back(0);
    }
    std::queue<int> queue;
    queue.push(v);
    visited[v]=1;
    // std::cout<<vertex[v]<<"\t";
    int p=v;
    while(!queue.empty())
    {
        for(int i=0;i<vertex.size();i++)
        {
            if(visited[i]==0 && arc[p][i]>0)
            {
                queue.push(i);
                visited[i]=1; 
            }
        }
        p=queue.front();
        std::cout<<vertex[p]<<"\t";
        queue.pop();
    }

}

template<typename T>
void Graph_Prim<T>::DFSTraverse(int v)
{
    assert(v<vertex.size());
    std::vector<int>visited;
    for(int i=0;i<vertex.size();i++)
    {
        visited.push_back(0);
    }
    std::stack<int> stack;
    stack.push(v);
    visited[v]=1;
    std::cout<<vertex[v]<<"\t";
    int p=v;
    int last=0;
    while(!stack.empty())
    {
        bool flag=false;
        for(int i=last;i<vertex.size();i++)
        {
            if(visited[i]==0 && arc[p][i]>0)
            {
                p=i;
                std::cout<<vertex[p]<<"\t";
                stack.push(p);
                flag=true;
                visited[p]=1;
                break;
            }
        }
         if(!flag)
            {
                last=p;
                p=stack.top();
                stack.pop();
            }
    }

}
template<typename T>
void Graph_Prim<T>::MST_Prim()
{
    //初始化 shortEdge
    std::vector<PrimEdge> shortEdge;
    for(int i=0;i<vertex.size();i++)
    {
        PrimEdge e;
        e.adjvex=0;
        e.lowCost=-1;
        shortEdge.push_back(e);
    }

    for(int i=1;i<vertex.size();i++)
    {
        // shortEdge[i].adjvex=0;
        shortEdge[i].lowCost=arc[0][i];
    }
    shortEdge[0].lowCost=0;//加入节点0

    for(int i=1;i<vertex.size();i++)
    {
        for(int x=0;x<shortEdge.size();x++)
        {
            std::cout<<x <<": adjvex="<<shortEdge[x].adjvex<<"\tlowcost="<<shortEdge[x].lowCost<<std::endl;
        }
        int j=FindMinCost(shortEdge);
        std::cout<<"arc:"<<shortEdge[j].adjvex<<"-"<<j<<"  :"<<shortEdge[j].lowCost<<std::endl;
        shortEdge[j].lowCost=0;
        UpdataShortEdge(shortEdge,j);

        
    }
}
template <typename T>
int  Graph_Prim<T>::FindMinCost(const std::vector<PrimEdge>  &p)
{
    int min=999999;//设置一个最大数
    int index=0;
    for(int i=0;i<p.size();i++)
    {
        if(p[i].lowCost > 0 && p[i].lowCost<min )
        {
            min=p[i].lowCost;
            index=i;
        }
    }
    return index;
}

template <typename T>
void  Graph_Prim<T>::UpdataShortEdge(std::vector<PrimEdge>  & p,int j )
{
    for(int i=0;i<p.size();i++)
    {
        if(p[i].lowCost>0 && arc[j][i] < p[i].lowCost && arc[j][i]>0  )
        {
            p[i].lowCost=arc[j][i];
            p[i].adjvex=j;
        }
         if(p[i].lowCost==-1 && arc[j][i] > 0)
        {
            p[i].lowCost=arc[j][i];
            p[i].adjvex=j;
        }
    }
}

template<typename T>
Graph_Prim<T>::~Graph_Prim()
{
}

void Mst_Test()
{
    std::vector<std::string> str;
    str.push_back("A");
    str.push_back("B");
    str.push_back("C");
    str.push_back("D");
    str.push_back("E");
    str.push_back("F");
    Graph_Prim<std::string> graph(str,9);
    // graph.DFSTraverse(0);
    graph.BFSTraverse(0);
    graph.MST_Prim();
}

#endif