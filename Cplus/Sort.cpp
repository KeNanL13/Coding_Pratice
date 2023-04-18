#include <iostream>
#include <vector>

void Insert_Sort(std::vector<int>& v)
{
    for(int i=2;i<v.size();i++)
    {
        v[0]=v[i];
        int j;
        for(  j=i-1;v[0]<v[j];j--)
        {
            v[j+1]=v[j];
        }
        v[j+1]=v[0];
    }
}

void Shell_Sort(std::vector<int> & v)
{
    for(int d=(v.size()-1)/2;d>0;d=d/2)
    {
        for(int i=1+d;i<v.size();i++)
        {
            v[0]=v[i];
            int j;
            for(j=i-d;v[0]<v[j] && j>0;j=j-d)
            {
                v[j+d]=v[j];
            }
            v[j+d]=v[0];
        }
    }
}

int main(int argv,char**argc)
{
    std::vector<int> v;
    v.push_back(0);
    
    // v.push_back(12);
    // v.push_back(15);
    // v.push_back(9);
    // v.push_back(20);
    // v.push_back(6);
    // v.push_back(31);
    // v.push_back(24);
    // Insert_Sort(v);

    v.push_back(59);
    v.push_back(20);
    v.push_back(17);
    v.push_back(36);
    v.push_back(98);
    v.push_back(14);
    v.push_back(23);
    v.push_back(83);
    v.push_back(13);
    v.push_back(28);
    Shell_Sort(v);



    for(int i=1;i<v.size();i++)
    {
        std::cout<<v[i]<<"\t";
    }
    return 0;
}