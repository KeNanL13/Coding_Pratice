#include <iostream>
#include <string>
#include <vector>
// #include "MST.hpp"
// #include "ShortestPath.hpp"

#include <list>
using namespace std;



int main(){


    // DijkstraTest();
    std::list<int *>list ;
    for(int i=0;i<10;i++)
    {
        int * p=new int(i);
        list.push_front(p);
    } 
    for(std::list<int*>::iterator it=list.begin();it!=list.end();it++)
    {
        (*(*it))--;
        // std::cout<<*(*it)<<std::endl;
    }
    for(std::list<int*>::iterator it=list.begin();it!=list.end();it++)
    {
        std::cout<<*(*it)<<std::endl;
    }



    system("pause");
    return 0;
}