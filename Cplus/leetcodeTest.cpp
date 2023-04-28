#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>

using namespace std;

class DinnerPlates
{

public:
    struct PlatesStack
    {
        int value;
        PlatesStack *next;
    };
    struct PlateHead
    {
        int size;
        PlatesStack *top;
    };

    vector<PlateHead *> list;
    int m_Capacity = 0;
    int currentIndex = 0;
    set<int> indexSet;

    DinnerPlates(int capacity)
    {
        m_Capacity = capacity;
        PlateHead *head = new PlateHead;
        head->size = 0;
        head->top = nullptr;
        list.push_back(head);
    }
    ~DinnerPlates()
    {
        for (auto x : list)
        {
            PlatesStack *p = x->top;
            while (p)
            {
                PlatesStack *temp = p;
                p = p->next;
                delete temp;
            }
            delete x;
        }
    }

    void push(int val)
    {
        
        if (!indexSet.empty())
        {
            int index = (*indexSet.begin());
            if (index >= currentIndex)
            {
                indexSet.clear();
                push(val);
            }
            else
            {
                PlatesStack *p = new PlatesStack;
                p->value = val;
                p->next = list[index]->top;
                list[index]->top = p;
                list[index]->size++;
                indexSet.erase(indexSet.begin());
                return;
            }
        }
        else
        {
            if (list[currentIndex]->size < m_Capacity)
            {
                PlatesStack *p = new PlatesStack;
                p->value = val;
                p->next = list[currentIndex]->top;
                list[currentIndex]->top = p;
                list[currentIndex]->size++;
                return;
            }
            else
            {
                currentIndex = currentIndex + 1;
                if (currentIndex == list.size() )
                {
                    PlateHead *h = new PlateHead;
                    PlatesStack *p = new PlatesStack;
                    h->size = 1;
                    p->value = val;
                    p->next = nullptr;
                    h->top = p;
                    list.push_back(h);
                    
                }
                else{
                    PlatesStack * p=new PlatesStack;
                    p->value=val;
                    p->next=nullptr;
                    list[currentIndex]->top=p;
                    list[currentIndex]->size++;
                }
            }
        }
        // for (int i = 0; i < list.size(); i++)
        // {
        //     if (list[i]->size < m_Capacity)
        //     {
        //         PlatesStack *p = new PlatesStack;
        //         p->value = val;
        //         p->next = list[i]->top;
        //         list[i]->top = p;
        //         list[i]->size++;
        //         return;
        //     }
        // }
        //     PlateHead *h = new PlateHead;
        //     PlatesStack *p = new PlatesStack;
        //     h->size = 1;
        //     p->value = val;
        //     p->next = nullptr;
        //     h->top = p;
        //     list.push_back(h);
    }

    int pop()
    {
        while (currentIndex >= 0 && list[currentIndex]->size == 0)
        {
            --currentIndex;
        }

        if (currentIndex >= 0)
        {
            PlatesStack *temp = list[currentIndex]->top;
            int v = temp->value;
            list[currentIndex]->top = temp->next;
            list[currentIndex]->size--;

            return v;
        }
        else
        {
            currentIndex=0;
            return -1;
        }

        // for (int i = list.size() - 1; i >= 0; i--)
        // {
        //     if (list[i]->size > 0)
        //     {
        //         PlatesStack *temp = list[i]->top;
        //         int v = temp->value;
        //         list[i]->top = temp->next;
        //         list[i]->size--;
        //         return v;
        //     }
        // }
        // return -1;
    }

    int popAtStack(int index)
    {
        if (index > currentIndex)
        {
            return -1;
        }
        PlateHead *h = list[index];
        if (h->size > 0)
        {
            PlatesStack *temp = h->top;
            int v = temp->value;
            h->top = temp->next;
            h->size--;
            indexSet.insert(index);
            return v;
        }
        return -1;
    }

    void PrintList()
    {
        cout << "print List:***************************" << endl;
        for (int i = 0; i < list.size(); i++)
        {
            std::cout << "plate"
                      << " " << i << "\t"
                      << "size=" << list[i]->size << "\n";
            if (list[i]->size > 0)
            {
                cout << "stack value:" << list[i]->top->value << endl;
            }
        }
    }
};
int main()
{
    DinnerPlates *dinner = new DinnerPlates(1);
    dinner->push(1);
    dinner->PrintList();
    dinner->push(2);
    dinner->PrintList();
    cout<<dinner->popAtStack(1)<<endl;
    dinner->PrintList();
    cout<<dinner->pop()<<endl;
    dinner->PrintList();
    dinner->push(1);
    dinner->PrintList();
    dinner->push(2);
    dinner->PrintList();
    cout<<dinner->pop()<<endl;
    dinner->PrintList();
    cout<<dinner->pop()<<endl;
    dinner->PrintList();

    delete dinner;

    return 0;
}