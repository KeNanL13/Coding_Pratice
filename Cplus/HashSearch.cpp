//散列查找
#include <iostream>
#include <vector>

template<typename T>
struct HashNode
{
    T data;
    HashNode<T> * next;
};

int Hash(int key,int size)
{
    return key%size;
}

//闭散列表查找算法
int HashSearch(std::vector<int>& ht,int key)
{
    int j=Hash(key,ht.size());
    if(ht[j]==key)return j;
    else if(ht[j]==INT_MIN)
    {
        ht[j]=key;
        return 0;
    }
    int i=(j+1)%ht.size();
    while(ht[i]!=INT_MIN && i!=j)
    {
        if(ht[i]==key)
        {
            return i;
        }else{
            i=(i+1)%ht.size();
        }
    }
    if(i==j){return -1;}
    else {
        ht[i]=key;
        return 0;
    }
    
}

//开散列表查找算法
HashNode<int> * HashSearch2(std::vector<HashNode<int> *>& vector,int data)
{
    int j=Hash(data,vector.size());
    HashNode<int> * p=vector[j];
    while (p!=nullptr )
    {
        if(p->data==data)
        {
            std::cout<<"1"<<std::endl;
            return p;
        }
        p=p->next;
    }
    HashNode<int> * node=new HashNode<int>;
    node->data=data;
    node->next=vector[j];
    vector[j]=node;
    
}

int main()
{
    /*************闭散********************/
    // std::vector<int> HashVector;
    // for(int i=0;i<11;i++)
    // {
    //     HashVector.push_back(INT_MIN);
    // }
    // HashSearch(HashVector,47);
    // HashSearch(HashVector,7);
    // HashSearch(HashVector,29);
    // HashSearch(HashVector,11);
    // HashSearch(HashVector,16);
    // HashSearch(HashVector,92);
    // HashSearch(HashVector,22);
    // HashSearch(HashVector,8);
    // HashSearch(HashVector,3);
    // for(auto x  : HashVector)
    // {
    //     std::cout<<x<<std::endl;
    // }
    // std::cout<<"find key 92:"<<HashSearch(HashVector,92)<<std::endl;
    // std::cout<<"find key 11:"<<HashSearch(HashVector,11)<<std::endl;
    // std::cout<<"find key 100:"<<HashSearch(HashVector,100)<<std::endl;
    // std::cout<<"find key 200:"<<HashSearch(HashVector,200)<<std::endl;
    // std::cout<<"find key 300:"<<HashSearch(HashVector,300)<<std::endl;
    /****************开散******************/
    std::vector<HashNode<int>*> nodeList;
    for(int i=0;i<11;i++)
    {
        nodeList.push_back(nullptr);
    }
    HashSearch2(nodeList,47);
    HashSearch2(nodeList,7);
    HashSearch2(nodeList,29);
    HashSearch2(nodeList,11);
    HashSearch2(nodeList,16);
    HashSearch2(nodeList,92);
    HashSearch2(nodeList,22);
    HashSearch2(nodeList,8);
    HashSearch2(nodeList,3);

        for(auto x  : nodeList)
    {
        while (x!=nullptr)
        {
            std::cout<<x->data<<"\t";
            x=x->next;
        }
        std::cout<<std::endl;
    }
    // std::cout<<HashSearch2(nodeList,22)->data<<std::endl;
    return 0;
}