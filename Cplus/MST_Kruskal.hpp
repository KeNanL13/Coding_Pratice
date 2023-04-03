#ifndef MST_KRUSKAL_HPP
#define MST_KRUSKAL_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


struct Edge
{
    int start,end;
    int weight;
};

template <typename T>
class MST_Kruskal
{
private:
    std::vector<T> vertex;
    std::vector<Edge> arcs;
public:
    MST_Kruskal(std::vector<T> v,int e);
    MST_Kruskal(std::vector<T> v,std::vector<Edge> e);
    void GetMST_Kruskal();
    int FindRoot(const std::vector<int> & parent,int index);
    
    ~MST_Kruskal();
};

template<typename T>
MST_Kruskal<T>::MST_Kruskal(std::vector<T> v,int e)
{
    vertex=v;
    std::vector<Edge>temp;
    for(int i=0;i<e;i++)
    {
        std::cout<<"input the vertex of  "<<i<<"arc"<<std::endl;
        int x,y,w;
        std::cin>>x>>y;
        std::cout<<"input the weight :";
        std::cin>>w;
        Edge edge;
        edge.start=x;
        edge.end=y;
        edge.weight=w;
        arcs.push_back(edge);
    }
    std::sort(arcs.begin(),arcs.end(),[=](const Edge & edge1,const Edge & edge2)->bool{
        return edge1.weight<edge2.weight;
    });

    for(int i=0;i<arcs.size();i++)
    {
        std::cout<<arcs[i].start<<"-"<<arcs[i].end<<": "<<arcs[i].weight<<std::endl;
    }
}


template<typename T>
MST_Kruskal<T>::MST_Kruskal(std::vector<T> v,std::vector<Edge> e)
{
    vertex=v;
    arcs=e;
    std::sort(arcs.begin(),arcs.end(),[=](const Edge & edge1,const Edge & edge2)->bool{
        return edge1.weight<edge2.weight;
    });

    for(int i=0;i<arcs.size();i++)
    {
        std::cout<<arcs[i].start<<"-"<<arcs[i].end<<": "<<arcs[i].weight<<std::endl;
    }
}

template<typename T>
int MST_Kruskal<T>::FindRoot(const std::vector<int>  & parent,int index)
{
    int root;
    root=index;
    int p=parent[index];
    while(p!=-1)
    {
        root=p;
        p=parent[root];
    }
    return root;
}

template<typename T>
void MST_Kruskal<T>::GetMST_Kruskal()
{
    std::vector<int> parent;
    int num=0;
    for(int i=0;i<vertex.size();i++)
    {
        parent.push_back(-1);
    }

    for(int i=0;i<arcs.size();i++)
    {
        int root1=FindRoot(parent,arcs[i].start);
        int root2=FindRoot(parent,arcs[i].end);
        if(root1!=root2)
        {
            std::cout<<arcs[i].start<<"-"<<arcs[i].end<<":"<<arcs[i].weight<<std::endl;
            parent[arcs[i].end]=arcs[i].start;
            num++;
        }
        if(num==vertex.size()-1)
        {
            break;
        }
    }

}


template <typename T>
MST_Kruskal<T>::~MST_Kruskal()
{

}


void MST_KruskalTest()
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
    
    MST_Kruskal<std::string> graph(vertex,arc);
    graph.GetMST_Kruskal();
}

#endif