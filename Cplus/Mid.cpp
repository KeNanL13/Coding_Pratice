#include <iostream>
#include <vector>
#include <string>
void GetLeftAndRight(std::vector<int> &v1, std::vector<int> &v2, const int &standard, int &left, int &right)
{
    left = 0;
    right = 0;
    int start = 0;
    int end = v2.size() - 1;
    int mid;
    while (start < end)
    {
        mid = (start + end) / 2;
        if (standard > v2[mid])
        {
            left += mid - start + 1;
            start = mid + 1;
        }
        else
        {
            right += end - mid + 1;
            end = mid - 1;
        }

        if (start == end)
        {

            if (standard > v2[start])
            {

                left++;
            }
            else
            {
                right++;
            }
        }
        // std::cout<<"start:"<<start<<"end:"<<end<<std::endl;
        // std::cout<<"left:"<<left<<"\tright:"<<right<<std::endl;
    }
}

std::vector<std::string> sortPeople(std::vector<std::string>& names,std:: vector<int>& heights) {
        for(int i=0;i<heights.size();i++)
        {
            int max=heights[i];
            int index=i;
            std::cout<<"i="<<i<<"\tmax="<<max<<std::endl;
            for(int j=i+1;j<heights.size();j++)
            {
                if(heights[j]>max)
                {
                    max=heights[j];
                    index=j;
                }
            }
            std::cout<<"i="<<i<<"\tmax="<<max<<std::endl;
            if(index!=i)
            {
            std::string temp=names[i];
            names[i]=names[index];
            names[index]=temp;
            }
        }
        return names;
}

int main()
{
    std::vector<int> v1{1,3};
    std::vector<int> v2{2};
    int left = 0;
    int right = 0;
    int flag1 = (v1.size() - 1) / 2;
    int flag2 = (v2.size() - 1) / 2;
    int lvalue = 0, rvalue = 0;
    GetLeftAndRight(v1, v2, v1[flag1], left, right);
    lvalue = flag1 + left;
    rvalue = v1.size() - 1 - flag1 + right;
    flag1 += ((rvalue - lvalue) / 2);
    bool flag=rvalue-lvalue>0;
    while (lvalue - rvalue > 1 || lvalue - rvalue < -1)
    {
        GetLeftAndRight(v1, v2, v1[flag1], left, right);
        std::cout << "v1 mid ,v2  left:" << left << "\tv2 right" << right << std::endl;
        lvalue = flag1 + left;
        rvalue = v1.size() - 1 - flag1 + right;
        std::cout << "lvalue:" << lvalue << "\trvalue:" << rvalue << std::endl;
        std::cout << "flag1=" << flag1 << std::endl;
        if(rvalue-lvalue>0 !=flag){
            break;
        }
        flag1 += ((rvalue - lvalue) / 2);
    }
    std::cout<<"flag1="<<flag1<<std::endl;
    flag2=left-1;
    GetLeftAndRight(v2,v1,v2[flag2],left,right);
    lvalue=flag2+left;
    rvalue=v2.size()-1-flag2+right;
    flag2+=(rvalue-lvalue)/2;
    flag=rvalue-lvalue>0;
    while(lvalue - rvalue > 1 || lvalue - rvalue < -1)
    {
        GetLeftAndRight(v2, v1, v2[flag2], left, right);
        std::cout << "v1 mid ,v2  left:" << left << "\tv2 right" << right << std::endl;
        lvalue = flag2 + left;
        rvalue = v2.size() - 1 - flag2 + right;
        std::cout << "lvalue:" << lvalue << "\trvalue:" << rvalue << std::endl;
        std::cout << "flag2=" << flag2 << std::endl;
        if(rvalue-lvalue>0 !=flag){
            break;
        }
        flag1 += ((rvalue - lvalue) / 2);
    }
    std::cout<<"flag2="<<flag2<<std::endl;
    std::cout<<"left="<<left<<"\tright="<<right<<std::endl;


    // std::vector<std::string> names{"IEO","Sgizfdfrims","QTASHKQ","Vk","RPJOFYZUBFSIYp","EPCFFt","VOYGWWNCf","WSpmqvb"};
    // std::vector<int> height{17233,32521,14087,42738,46669,65662,43204,8224};
    // sortPeople(names,height);
    // for(auto x : names)
    // {
    //     std::cout<<x<<std::endl;
    // }

    return 0;
}