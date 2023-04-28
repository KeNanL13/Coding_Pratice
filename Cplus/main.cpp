#include <iostream>
#include <string>
#include <vector>
#include "BiSearchTree.hpp"
#include <algorithm>
#include <set>

#include <list>
using namespace std;




int main(){

    set<int> set;
    set.insert(1);
    set.insert(4);
    set.insert(7);
    set.insert(9);
    int b=(*set.begin());
    set.erase(set.begin());
    cout<<b<<endl;
    b=(*set.begin());
    set.erase(set.begin());
    cout<<b;
    // system("pause");
    return 0;
}