#include <iostream>
#include <vector>

void Insert_Sort(std::vector<int> &v)
{
    for (int i = 2; i < v.size(); i++)
    {
        v[0] = v[i];
        int j;
        for (j = i - 1; v[0] < v[j]; j--)
        {
            v[j + 1] = v[j];
        }
        v[j + 1] = v[0];
    }
}

void Shell_Sort(std::vector<int> &v)
{
    for (int d = (v.size() - 1) / 2; d > 0; d = d / 2)
    {
        for (int i = 1 + d; i < v.size(); i++)
        {
            v[0] = v[i];
            int j;
            for (j = i - d; v[0] < v[j] && j > 0; j = j - d)
            {
                v[j + d] = v[j];
            }
            v[j + d] = v[0];
        }
    }
}

void SelectSort(std::vector<int> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        int index = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[j] < v[index])
            {
                index = j;
            }
        }
        v[0]=v[index];
        v[index] = v[i];
        v[i] = v[0];
    }
}

void BubbleSort2(std::vector<int> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        for (int j = 1; j < v.size() - i; j++)
        {
            if (v[j + 1] < v[j])
            {
                v[0] = v[j];
                v[j] = v[j + 1];
                v[j + 1] = v[0];
            }
        }
    }
}

void BubbleSort3(std::vector<int> &v)
{
    int exchange = v.size();
    while (exchange != 0)
    {
        int up = exchange;
        exchange = 0;
        for (int j = 1; j < up - 1; j++)
        {
            if (v[j + 1] < v[j])
            {
                v[0] = v[j];
                v[j] = v[j + 1];
                v[j + 1] = v[0];
                exchange = j + 1;
            }
        }
    }
}

void QuickSortBase(std::vector<int> & v,int start,int end)
{
    if(start>end)
    {
        return;
    }
    int i=start;
    int j=end;
    while (i !=j)
    {
        while (v[i] < v[j])
        {
            j--;
        }
        if (i < j)
        {
            v[0] = v[i];
            v[i] = v[j];
            v[j] = v[0];
            i++;
        }

        while (v[i] < v[j])
        {
            i++;
        }
        if (i < j)
        {
            v[0] = v[i];
            v[i] = v[j];
            v[j] = v[0];
            j--;
        }
    }
    // std::cout<<"start="<<start<<"\ti-1="<<i-1<<std::endl;
    QuickSortBase(v,start,i-1);
    QuickSortBase(v,i+1,end);
}

void QuickSort(std::vector<int> &v)
{
    QuickSortBase(v,1,v.size());
}

//最小堆
void Sift(std::vector<int> & v,int k,int m)
{
    int i=k;
    int j=2*i;
    while(j<m)
    {
        if(j<m-1 && v[j+1]>v[j])j++;
        if(v[i]>v[j])break;
        v[0]=v[i];
        v[i]=v[j];
        v[j]=v[0];
        i=j;
        j=2*i;
    }
}

void BuildHeap(std::vector<int> & v)
{
    for(int i=(v.size()-1)/2;i>=1;--i)
    {
        Sift(v,i,v.size());
    }
}

void HeapSort(std::vector<int>& v)
{
    BuildHeap(v);
    for(int i=1;i<v.size();i++)
    {
       
        v[0]=v[1];
        v[1]=v[v.size()-i];
        v[v.size()-i]=v[0];
        Sift(v,1,v.size()-i);
    }
}

//一次归并 两个序列范围是 v1[s]-v1[m] , v1[m+1]-v1[t]
void Merge(std::vector<int>& v1,std::vector<int>& v2,int s,int m,int t)
{
    int i=s,j=m+1,k=i;
    while(i<=m && j<=t)
    {
        if(v1[i]<=v1[j]){
            v2[k++]=v1[i++];
        }else{
            v2[k++]=v1[j++];
        }
    }

    while(i<=m)
    {
        v2[k++]=v1[i++];
    }
    while(j<=t)
    {
        v2[k++]=v1[k++];
    }
}

//一趟归并排序 h 表示该次序列长度
void MergePass(std::vector<int> & v1,std::vector<int> & v2,int h)
{
    int i=1;
    while(i<=v1.size()-2*h)
    {
        Merge(v1,v2,i,i+h-1,i+2*h-1);
        i+=2*h;
    }
    if(i<v1.size()-h)
    {
        Merge(v1,v2,i,i+h-1,v1.size()-1);
    }else{
        for(int k=i;k<v1.size();k++)
        {
            v2[k]=v1[k];
        }
    }
}

//归并排序
void MergeSort1(std::vector<int> &v1,std::vector<int> &v2)
{
    
}


int main(int argv, char **argc)
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
    // Shell_Sort(v);
    // SelectSort(v);
    // QuickSort(v);
    // HeapSort(v);
    // BuildHeap(v);
    // HeapSort(v);
 

    for (int i = 1; i < v.size(); i++)
    {
        std::cout << v[i] << "\t";
    }
    return 0;
}