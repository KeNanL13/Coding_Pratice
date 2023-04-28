#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
void GetLeftAndRight(std::vector<int> &v1, std::vector<int> &v2, const int &standard, int &left, int &right）
{
    left = 0;
    right = 0;
    int start = 0;
    int end = v2.size() - 1;
    int mid;
    while (start < end)
    {
        mid = (start + end) >> 1;
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
}

int FindFlag(std::vector<int> &v1, std::vector<int> &v2)
{
    int left = 0, right = 0, lvalue = 0, rvalue = 0;
    
    int pos = (v1.size() - 1) >>1;

    GetLeftAndRight(v1, v2, v1[pos], left, right);
    lvalue = pos + left;
    rvalue = v1.size() - 1 - pos + right;
    bool flag = rvalue - lvalue > 0;
    std::cout<<"lvalue="<<lvalue<<"\trvalue="<<rvalue<<std::endl;
    while (lvalue - rvalue > 1 || lvalue - rvalue < -1)
    {
        if (rvalue - lvalue > 0 != flag)
        {
            return -1;
        }
        pos += ((rvalue - lvalue) >>1);

        GetLeftAndRight(v1, v2, v1[pos], left, right);
        lvalue = pos + left;
        rvalue = v1.size() - 1 - pos + right;
        
    }
    return pos;
}

int main()
{
    std::vector<int> nums1{2,2,4,4};
    std::vector<int> nums2{2,2,4,4};
    double result;

    
    if (nums1.size() == 0 && nums2.size() == 0)
    {
        result = 0.0;
        
    }else if (nums1.size()==0)
    {
        result =nums2.size()%2==0?(double)(nums2[nums2.size()>>1]+nums2[nums2.size()>>1-1])/2 : nums2[nums2.size()>>1];
    }else if(nums2.size()==0)
    {
        result =nums1.size()%2==0?(double)(nums1[nums1.size()>>1]+nums1[nums1.size()>>1-1])/2 : nums1[nums1.size()>>1];
    }
    
    int f1 = FindFlag(nums1, nums2);
    int f2 = FindFlag(nums2, nums1);
    std::cout<<"f1="<<f1<<"\tf2="<<f2<<std::endl;
    if (f1 >= 0 && f2 >= 0)
    {
        result = (double)(nums1[f1] + nums2[f2]) / 2;
    }
    else if (f1 >= 0)
    {
        result = nums1[f1];
    }
    else if (f2 >= 0)
    {
        result = nums2[f2];
    }
    std::cout<<"result="<<result<<std::endl;
  


    // std::vector<std::string> names{"IEO","Sgizfdfrims","QTASHKQ","Vk","RPJOFYZUBFSIYp","EPCFFt","VOYGWWNCf","WSpmqvb"};
    // std::vector<int> height{17233,32521,14087,42738,46669,65662,43204,8224};
    // sortPeople(names,height);
    // for(auto x : names)
    // {
    //     std::cout<<x<<std::endl;
    // }
    

    return 0;
}