#include <iostream>
#include <vector>

class Pattern_Matching
{
public:
    Pattern_Matching();
    static int simpleBF(const char string[], const char pattern[]);
    static std::vector<int> KMP_GetK(const char pattern[]);//slow method but simple
    static std::vector<int> KMP_GetK2(const char pattern[]);//Most Fast method
    static int KMP_Algo(const char string[], const char pattern[]);
};

int Pattern_Matching::simpleBF(const char string[], const char pattern[])
{
    int i = 0, j = 0;
    while (string[i] != '\0' && pattern[j] != '\0')
    {
        if (string[i + j] == pattern[j])
        {
            j++;
        }
        else
        {
            i++;
            j = 0;
        }
    }
    if (pattern[j] == '\0')
    {
        return i;
    }
    else
    {
        return -1;
    }
}

std::vector<int> Pattern_Matching::KMP_GetK(const char pattern[])
{
    int i = 0;
    std::vector<int> value;
    while (pattern[i] != '\0')
    {
        if (i == 0)
            value.push_back(-1);
        else if (i == 1)
            value.push_back(0);
        else
        {
            int k = i;
            int result = 0;
            while (--k)
            {
                bool flag = true;

                for (int j = 0; j < k; j++)
                {
                    if (pattern[j] != pattern[i - k + j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    result = k;
                    break;
                }
            }
            value.push_back(result);
        }
        i++;
    }
    return value;
}

std::vector<int> Pattern_Matching:: KMP_GetK2(const char pattern[])
{
    int i = 0;
    std::vector<int> value;
    while (pattern[i] != '\0')
    {
        if (i == 0)
            value.push_back(-1);
        else if (i == 1)
            value.push_back(0);
        else
        {
           int k=i-1,j=k;
           while(pattern[k]!=pattern[value[j]] && value[j]!=-1)
           {
            j=value[j];
           }
           value.push_back(value[j]+1);
        }
        i++;
    }
    return value;
}

int Pattern_Matching::KMP_Algo(const char string[],const char pattern[])
{
    int i=0,k=0;
    std::vector<int> kv=KMP_GetK2(pattern);
    while(string[i]!='\0' && pattern[k]!='\0')
    {
        if(string[i]==pattern[k])
        {
            k++;
            i++;
        }
        else{
            k=kv[k];
            if(k==-1)
            {
                k++;
                i++;
            }
        }
        
    }
    return pattern[k]=='\0'? i-k: -1;
}


