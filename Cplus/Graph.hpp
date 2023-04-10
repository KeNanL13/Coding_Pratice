#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include "Stack.hpp"
#include "Queue.hpp"
#include <string>
#include <limits>
// 文件描述
// 图的存储结构实现：领接矩阵(无向图)
// 最短路径 Dijkstra

template <typename T>
class Graph_AdjacencyMatrix
{
public:
    Graph_AdjacencyMatrix(std::vector<T> nodes, int e); // 构造函数，建立具有n个顶点e条边的图
    ~Graph_AdjacencyMatrix() {}
    void DFSTraverse(int v);   // 深度优先遍历 非递归
    void DFSTraverse_d(int v); // 深度优先遍历 递归
    void BFSTraverse(int v);   // 广度优先遍历
    void Dijkstra(int v);

private:
    void DFSTraversePrivate(std::vector<int> &visited, int i);
    std::vector<T> vertex;
    std::vector<std::vector<int>> arc;
    int vertexNum, arcNum;
};

template <typename T>
Graph_AdjacencyMatrix<T>::Graph_AdjacencyMatrix(std::vector<T> nodes, int e)
{
    vertex = nodes;
    for (int x = 0; x < nodes.size(); x++)
    {
        std::vector<int> temp;
        for (int y = 0; y < nodes.size(); y++)
        {
            if (x == y)
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
    int i, j,w;
    while (e--)
    {
        std::cout << "input vertex number of arc" << e << " :";
        std::cin >> i >> j;
        std::cout<<"input weight :";
        std::cin>>w;
        // std::cin>>j;
        arc[i][j] = w;
    }
    vertexNum = nodes.size();
    arcNum = e;
}

template <typename T>
void Graph_AdjacencyMatrix<T>::DFSTraverse(int v)
{
    std::vector<int> visited;
    for (int i = 0; i < vertexNum; i++)
    {
        visited.push_back(0);
    }
    Stack_Link<int> stack;
    stack.Push(v);
    visited[v] = 1;
    int p = v;
    int times = 1;
    std::cout << vertex[p] << "\t";
    while (times != vertexNum)
    {
        bool flag = false;
        for (int i = 0; i < vertexNum; i++)
        {
            if (visited[i] == 0 && arc[p][i] == 1)
            {
                p = i;
                visited[p] = 1;
                stack.Push(p);
                times++;
                flag = true;
                std::cout << vertex[p] << "\t";
                break;
            }
        }
        if (!flag && !stack.Empty())
        {
            p = stack.Pop();
        }
    }
}

template <typename T>
void Graph_AdjacencyMatrix<T>::DFSTraverse_d(int v)
{
    std::vector<int> visisted;
    for (int i = 0; i < vertexNum; i++)
    {
        visisted.push_back(0);
    }
    DFSTraversePrivate(visisted, v);
}

template <typename T>
void Graph_AdjacencyMatrix<T>::DFSTraversePrivate(std::vector<int> &visited, int i)
{
    visited[i] = 1;
    std::cout << vertex[i] << "\t";
    for (int j = 0; j < vertexNum; j++)
    {
        if (arc[i][j] == 1 && visited[j] == 0)
        {
            DFSTraversePrivate(visited, j);
        }
    }
}

template <typename T>
void Graph_AdjacencyMatrix<T>::BFSTraverse(int v)
{
    std::vector<int> visisted;
    for (int i = 0; i < vertexNum; i++)
    {
        visisted.push_back(0);
    }
    Queue_Link<int> queue;
    queue.EnQueue(v);
    // int times=1;
    int p;
    while (!queue.Empty())
    {
        p = queue.DeQueue();
        std::cout << vertex[p] << "\t";
        visisted[p] = 1;
        for (int i = 0; i < vertexNum; i++)
        {
            if (arc[v][i] == 1 && visisted[i] == 0)
            {
                queue.EnQueue(i);
            }
        }
    }
}

template <typename T>
void Graph_AdjacencyMatrix<T>::Dijkstra(int v)
{
    std::vector<int> dist;
    std::vector<int> source;
    std::vector<std::string> path;
    for (int i = 0; i < vertex.size)
    {
        std::string temp = "";
        dist.push_back(INT_MAX);
        path.push_back(temp);
    }
    source.push_back(v);
}

struct ArcNode
{
    int adjvex;
    ArcNode *next;
};

template <typename T>
struct VertexNode
{
    T value;
    ArcNode *fristEdge;
};

// 邻接表 (有向图)
template <typename T>
class Graph_AdjacencyList
{
public:
    Graph_AdjacencyList(std::vector<T> nodes, int e); // 构造函数，建立一个n个顶点，e条边的图
    ~Graph_AdjacencyList();

    void DFSTraverse(int v);
    void BFSTraverse(int v);
    void StructTraverse();

private:
    std::vector<VertexNode<T> *> vertex;
    int vertexNum, arcNum;
};
template <typename T>
Graph_AdjacencyList<T>::Graph_AdjacencyList(std::vector<T> nodes, int e)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        VertexNode<T> *vertexNode = new VertexNode<T>;
        vertexNode->value = nodes[i];
        vertexNode->fristEdge = nullptr;
        vertex.push_back(vertexNode);
    }

    while (e--)
    {
        int i, j;
        std::cout << "input the " << e << " th Edge:" << std::endl;
        std::cin >> i >> j;
        if (i >= vertex.size() || j >= vertex.size())
        {
            std::cout << "error:wrong  input" << std::endl;
            break;
        }

        VertexNode<T> *node = vertex[i];
        ArcNode *p = new ArcNode;
        p->adjvex = j;
        p->next = node->fristEdge;
        node->fristEdge = p;
        // VertexNode <T> * node=vertex[i];
        // ArcNode * *p=node->fristEdge;
        // while(*p)
        // {
        //     p=&((*p)->next);
        // }
        // *p=new ArcNode;
        // (*p)->adjvex=j;
        // (*p)->next=nullptr;
    }
}

template <typename T>
Graph_AdjacencyList<T>::~Graph_AdjacencyList()
{
    VertexNode<T> *node;
    ArcNode *p;
    for (int i = 0; i < vertex.size(); i++)
    {
        node = vertex[i];
        p = node->fristEdge;
        while (p)
        {
            ArcNode *temp = p->next;
            delete p;
            p = temp;
        }
        if (node)
        {
            delete node;
        }
    }
}

template <typename T>
void Graph_AdjacencyList<T>::DFSTraverse(int v)
{
    if (v >= vertex.size())
        return;
    std::vector<int> visited;
    for (int i = 0; i < vertex.size(); i++)
    {
        visited.push_back(0);
    }
    VertexNode<T> *node = vertex[v];
    ArcNode *p = node->fristEdge;
    std::cout << node->value << "\t";
    Stack_Link<ArcNode *> arcList;
    visited[v] = 1;

    int flags;
    while (!arcList.Empty() || p != nullptr)
    {
        flags++;
        if (p == nullptr)
        {
            p = arcList.Pop();
            continue;
        }
        if (visited[p->adjvex] == 0)
        {
            visited[p->adjvex] = 1;
            arcList.Push(p->next);
            node = vertex[p->adjvex];
            std::cout << node->value << "\t";
            p = node->fristEdge;
        }
        else
        {
            p = p->next;
        }
    }
    std::cout << "flags:" << flags << std::endl;
}

template <typename T>
void Graph_AdjacencyList<T>::BFSTraverse(int v)
{
    std::vector<int> visited;
    for (int i = 0; i < vertex.size(); i++)
    {
        visited.push_back(0);
    }
    VertexNode<T> *node = vertex[v];
    visited[v] = 1;
    std::cout << node->value << "\t";
    Queue_Link<int> queue;
    ArcNode *p = node->fristEdge;
    while (!queue.Empty() || p != nullptr)
    {
        while (p)
        {
            if (visited[p->adjvex] == 0)
            {
                queue.EnQueue(p->adjvex);
                visited[p->adjvex] = 1;
            }
            p = p->next;
        }
        if (!queue.Empty())
        {
            int index = queue.DeQueue();
            node = vertex[index];
            std::cout << node->value << "\t";
            p = node->fristEdge;
        }
    }
}

template <typename T>
void Graph_AdjacencyList<T>::StructTraverse()
{
    for (VertexNode<T> *x : vertex)
    {
        std::cout << "value:" << x->value << std::endl;
        ArcNode *p = x->fristEdge;
        while (p != nullptr)
        {
            std::cout << "adjvex:" << p->adjvex << "\t";
            p = p->next;
        }
        std::cout << "\n";
    }
}
void Graph_Test()
{
    std::vector<std::string> vector;
    vector.push_back("A");
    vector.push_back("B");
    vector.push_back("C");
    vector.push_back("D");
    Graph_AdjacencyMatrix<std::string> g(vector, 4);
    // g.DFSTraverse(0);
    g.BFSTraverse(0);
    // g.DFSTraverse_d(0);
}
void GraphList_Test()
{
    std::vector<std::string> vector;
    vector.push_back("A");
    vector.push_back("B");
    vector.push_back("C");
    vector.push_back("D");
    vector.push_back("E");
    Graph_AdjacencyList<std::string> g(vector, 7);
    // g.DFSTraverse(0);
    g.StructTraverse();
    g.BFSTraverse(0);
    // g.DFSTraverse(0);
}
#endif