#include <map>
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
    map<int, string> m1{{1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}, {6, "Six"}, {7, "Seven"}, {8, "Eight"}, {9, "Nine"}, {10, "Ten"}, {11, "Eleven"}, {12, "Twelve"}, {13, "Thirteen"}, {14, "Fourteen"}, {15, "Fifteen"}, {16, "Sixteen"}, {17, "Seventeen"}, {18, "Eighteen"}, {19, "Nineteen"}};
    map<int, string> m2{{2, "Twenty"}, {3, "Thirty"}, {4, "Fourty"}, {5, "Fifty"}, {6, "Sixty"}, {7, "Seventy"}, {8, "Eighty"}, {9, "Ninety"}};
    string numberToWords_Thousand(int num)
    {
        string s ;
        int c = num / 100;
        if (c > 0)
        {
            s = m1.at(c);
            s += " Hundred ";
        }
        int b = num % 100;
        if (m1.find(b) != m1.end())
        {
            s +=m1.at(b);
        }
        else
        {
            int temp = b % 10;
            b = b / 10;
            if(b>0 && temp>0)
            {
                s += m2.at(b) + " " + m1.at(temp);
            }
            else if(b>0)
            {
                s+=m2.at(b);
            }else if(temp>0)
            {
                s+=m2.at(temp);
            }
        }
        return s;
    }
    string numberToWords(int num)
    {
        string s;
        int num_temp = num / 1e9;
        if(num_temp > 0)
        {
            s+=numberToWords_Thousand(num_temp);
            s+=" Billion ";
        }
        num_temp=num % 1000000000 ;
        num_temp=num_temp/1e6;
        if(num_temp>0)
        {
            s+=numberToWords_Thousand(num_temp);
            s+=" Million ";
        }
        num_temp=num % 1000000;
        num_temp=num_temp/1e3;
        if(num_temp>0)
        {
            s+=numberToWords_Thousand(num_temp);
            s+=" Thousand ";
        }
        num_temp=num %1000;
        if(num_temp>0)
        {
            s+=numberToWords_Thousand(num_temp);
        }

       return s;
    }
};

int main()
{
    Solution s;
    string a = s.numberToWords_Thousand(100);
    string b=s.numberToWords(100);
    a.at(a.size())

    // std::cout<<number_u<<std::endl;
    std::cout << b<< std::endl;
}