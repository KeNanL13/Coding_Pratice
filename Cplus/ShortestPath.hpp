#ifndef SHORTESTPATH_HPP
#define SHORTESTPATH_HPP

#include <vector>
#include <string>
#include <iostream>
#include "Format.h"

struct Edge
{
    int start,end;
    int weight;
};

template <typename T>
class Graph_AdjacencyMatrix
{
public:
    Graph_AdjacencyMatrix(const std::vector<T> &nodes, std::vector<Edge> edges); // 构造函数，建立具有n个顶点e条边的图
    void PrintInfo();
    void Dijkstra();
    ~Graph_AdjacencyMatrix() {}

private:
    // void DFSTraversePrivate(std::vector<int> &visited, int i);
    std::vector<T> vertex;
    std::vector<std::vector<int>> arc;
    int vertexNum, arcNum;
};

template <typename T>
Graph_AdjacencyMatrix<T>::Graph_AdjacencyMatrix(const std::vector<T>  &nodes,  std::vector<Edge> edges)
{
    vertex = nodes;
    for (int x = 0; x < nodes.size(); x++)
    {
        std::vector<int> temp;
        for (int y = 0; y < nodes.size(); y++)
        {
            if(y==x)
            {
                temp.push_back(0);
            }
            else{
                temp.push_back(INT_MAX);
            }
        }
        arc.push_back(temp);
    }
    
    for(int i=0;i<edges.size();i++)
    {
        int row=edges[i].start;
        int column=edges[i].end;
        arc[row][column]=edges[i].weight;
    }
    vertexNum = nodes.size();
    arcNum = edges.size();
}

template<typename T>
void Graph_AdjacencyMatrix<T>::PrintInfo()
{
    for(auto x:vertex)
    {
        std::cout<<x<<std::endl;
    }

    for(auto x : arc)
    {
        for(auto y : x)
        {
            if(y==INT_MAX)
            {
                std::cout<<"oo\t";
            }else{
                std::cout<<y<<"\t";
            }  
        }
        std::cout<<std::endl;
    }
}
template<typename T>
void Graph_AdjacencyMatrix<T>::Dijkstra()
{
    std::vector<int> dist;
    std::vector<std::string> path;
    std::vector<int> source;
    for(int i=0 ;i<vertex.size();i++)
    {
        dist.push_back(0);
        // path.push_back("v0");
    }

    source.push_back(0);//将第一个节点放入源数组
    for(int i=0;i<vertex.size();i++)
    {
        dist[i]=arc[0][i];
        std::string path;
        if(dist[i]==INT_MAX)
        {
             path+=util::Format("v{1}v{2}",0,i);
        }
    }

    for(int i=0;i<)
}

void DijkstraTest()
{
    std::vector<std::string> vertex;
    vertex.push_back("A");
    vertex.push_back("B");
    vertex.push_back("C");
    vertex.push_back("D");
    vertex.push_back("E");
    vertex.push_back("F");
    std::vector<Edge> arc;
    Edge e0;e0.start=0;e0.end=1;e0.weight=34;arc.push_back(e0);
    Edge e1;e1.start=0;e1.end=2;e1.weight=46;arc.push_back(e1);
    Edge e2;e2.start=0;e2.end=5;e2.weight=19;arc.push_back(e2);
    Edge e3;e3.start=1;e3.end=4;e3.weight=12;arc.push_back(e3);
    Edge e4;e4.start=4;e4.end=5;e4.weight=26;arc.push_back(e4);
    Edge e5;e5.start=4;e5.end=3;e5.weight=38;arc.push_back(e5);
    Edge e6;e6.start=2;e6.end=5;e6.weight=25;arc.push_back(e6);
    Edge e7;e7.start=2;e7.end=3;e7.weight=17;arc.push_back(e7);
    Edge e8;e8.start=3;e8.end=5;e8.weight=25;arc.push_back(e8);
    
    Graph_AdjacencyMatrix<std::string> graph(vertex,arc);
    graph.PrintInfo();
}

#endif
