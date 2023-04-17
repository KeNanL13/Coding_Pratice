#ifndef SHORTESTPATH_HPP
#define SHORTESTPATH_HPP

#include <vector>
#include <string>
#include <iostream>
#include "Format.h"

struct Edge
{
    int start, end;
    int weight;
};

template <typename T>
class Graph_AdjacencyMatrix
{
public:
    Graph_AdjacencyMatrix(const std::vector<T> &nodes, std::vector<Edge> edges); // 构造函数，建立具有n个顶点e条边的图
    void PrintInfo();
    void Dijkstra(int v);
    void Floyd();
    ~Graph_AdjacencyMatrix() {}

private:
    // void DFSTraversePrivate(std::vector<int> &visited, int i);
    std::vector<T> vertex;
    std::vector<std::vector<int>> arc;
    int vertexNum, arcNum;
};

template <typename T>
Graph_AdjacencyMatrix<T>::Graph_AdjacencyMatrix(const std::vector<T> &nodes, std::vector<Edge> edges)
{
    vertex = nodes;
    for (int x = 0; x < nodes.size(); x++)
    {
        std::vector<int> temp;
        for (int y = 0; y < nodes.size(); y++)
        {
            if (y == x)
            {
                temp.push_back(0);
            }
            else
            {
                temp.push_back(INT_MAX);
            }
        }
        arc.push_back(temp);
    }

    for (int i = 0; i < edges.size(); i++)
    {
        int row = edges[i].start;
        int column = edges[i].end;
        arc[row][column] = edges[i].weight;
    }
    vertexNum = nodes.size();
    arcNum = edges.size();
}

template <typename T>
void Graph_AdjacencyMatrix<T>::PrintInfo()
{
    for (auto x : vertex)
    {
        std::cout << x << std::endl;
    }

    for (auto x : arc)
    {
        for (auto y : x)
        {
            if (y == INT_MAX)
            {
                std::cout << "oo\t";
            }
            else
            {
                std::cout << y << "\t";
            }
        }
        std::cout << std::endl;
    }
}
int FindMin(std::vector<int> d)
{
    int min = INT_MAX;
    int index = -1;

    for (int i = 0; i < d.size(); i++)
    {
        if (d[i] < min && d[i] != 0)
        {
            min = d[i];
            index = i;
        }
    }
    return index;
}
template <typename T>
void Graph_AdjacencyMatrix<T>::Dijkstra(int v)
{
    std::vector<int> dist;
    std::vector<std::string> path;
    std::vector<int> source;
    for (int i = 0; i < vertex.size(); i++)
    {
        dist.push_back(v);
        path.push_back("");
    }

    source.push_back(v); // 将第一个节点放入源数组
    for (int i = 0; i < vertex.size(); i++)
    {
        dist[i] = arc[v][i];

        if (dist[i] != INT_MAX && dist[i] != 0)
        {
            std::string t_path;
            t_path = util::Format("v{0}v{1}", v, i);
            path[i] = t_path;
        }
    }

    while (source.size() != vertex.size())
    {

        std::cout << "result" << std::endl;
        int index = FindMin(dist);
        if (index == -1)
        {
            break;
        }                                                             // find min value in the dist
        std::cout << dist[index] << "\t" << path[index] << std::endl; // print the minimum path information
        source.push_back(index);                                      // add this vertex to the source

        // update dist and path
        for (int i = 0; i < dist.size(); i++)
        {
            int d = arc[index][i];
            if (d != INT_MAX && dist[i] > dist[index] + d)
            {
                dist[i] = dist[index] + d;
                std::string a = util::Format("v{0}", i);
                path[i] = path[index] + a;
            }
        }

        dist[index] = 0;
        // std::cout << "dist and path" << std::endl;
        // for (int i = 0; i < dist.size(); i++)
        // {
        //     std::cout << dist[i] << "\t" << path[i] << std::endl;
        // }
    }
}

template <typename T>
void Graph_AdjacencyMatrix<T>::Floyd()
{
    std::vector<std::vector<int>> dist;
    std::vector<std::vector<std::string>> path;
    // 初始化 dist 和 path
    for (int i = 0; i < vertex.size(); ++i)
    {
        std::vector<int> temp;
        std::vector<std::string> s_temp;
        for (int j = 0; j < vertex.size(); j++)
        {
            temp.push_back(arc[i][j]);
            if (arc[i][j] != INT_MAX &&arc[i][j]!=0)
            {
                s_temp.push_back(util::Format("v{0}v{1}", i, j));
            }
            else
            {
                s_temp.push_back("");
            }
        }
        dist.push_back(temp);
        path.push_back(s_temp);
    }

    for (int k = 0; k < vertex.size(); ++k)
    {
        for (int i = 0; i < vertex.size(); i++)
        {
            for (int j = 0; j < vertex.size(); j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k] + path[k][j];
                }
            }
        }
    }

    // Print dist and path matrix
    for (int i = 0; i < vertex.size(); i++)
    {
        for (int j = 0; j < vertex.size(); j++)
        {
            std::cout << dist[i][j] << "\t";
        }
        std::cout << "\n";
    }

    for (int i = 0; i < vertex.size(); i++)
    {
        for (int j = 0; j < vertex.size(); j++)
        {
            std::cout << path[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void DijkstraTest()
{
    // std::vector<std::string> vertex;
    // vertex.push_back("A");
    // vertex.push_back("B");
    // vertex.push_back("C");
    // vertex.push_back("D");
    // vertex.push_back("E");
    // std::vector<Edge> arc;
    // Edge e0;
    // e0.start = 0;
    // e0.end = 1;
    // e0.weight = 10;
    // arc.push_back(e0);
    // Edge e1;
    // e1.start = 0;
    // e1.end = 3;
    // e1.weight = 30;
    // arc.push_back(e1);
    // Edge e2;
    // e2.start = 0;
    // e2.end = 4;
    // e2.weight = 100;
    // arc.push_back(e2);
    // Edge e3;
    // e3.start = 1;
    // e3.end = 2;
    // e3.weight = 50;
    // arc.push_back(e3);
    // Edge e4;
    // e4.start = 2;
    // e4.end = 4;
    // e4.weight = 10;
    // arc.push_back(e4);
    // Edge e5;
    // e5.start = 3;
    // e5.end = 4;
    // e5.weight = 60;
    // arc.push_back(e5);
    // Edge e6;
    // e6.start = 3;
    // e6.end = 2;
    // e6.weight = 20;
    // arc.push_back(e6);

    // Graph_AdjacencyMatrix<std::string> graph(vertex, arc);
    // graph.PrintInfo();
    // graph.Dijkstra(4);
/***********************Floyd***************************************/
    std::vector<std::string> vertex;
    vertex.push_back("A");
    vertex.push_back("B");
    vertex.push_back("C");
    std::vector<Edge> arc;
    Edge e0;
    e0.start = 0;
    e0.end = 1;
    e0.weight = 4;
    arc.push_back(e0);
    Edge e1;
    e1.start = 1;
    e1.end = 0;
    e1.weight = 6;
    arc.push_back(e1);
    Edge e2;
    e2.start = 2;
    e2.end = 0;
    e2.weight = 3;
    arc.push_back(e2);
    Edge e3;
    e3.start = 0;
    e3.end = 2;
    e3.weight = 11;
    arc.push_back(e3);
    Edge e4;
    e4.start = 1;
    e4.end = 2;
    e4.weight = 2;
    arc.push_back(e4);
    Graph_AdjacencyMatrix<std::string> graph(vertex, arc);
    graph.Floyd();
}

#endif
