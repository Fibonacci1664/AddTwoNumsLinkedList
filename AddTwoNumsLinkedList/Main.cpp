#include<iostream>
#include <list>
#include <vector>

//Definition for singly-linked list
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* head = nullptr;
ListNode* tail = nullptr;

// Prepend stuff to the start of a list
//void prepend(int data)
//{
//    ListNode* newNode = new ListNode(data);
//    ListNode* tempPtr = head;
//    head = newNode;
//    head->next = tempPtr;
//}

void append(int data)
{
    ListNode* newNode = new ListNode(data);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}
 
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    // Case:1
    // Both lists are zero and are only one node in size
    if ((l1->val == 0 && l2->val == 0) && (l1->next == nullptr && l2->next == nullptr))
    {
        return l1;
    }

    // Case:2
    // One list is zero, the other has value stored > 0
    if (l1->val == 0 && l1->next == nullptr)
    {
        // Return l2 in reverse order
        while (l2 != nullptr)
        {
            // Append to new list, then return the head of that list
            append(l2->val);
            l2 = l2->next;
        }

        return head;
    }
    else if(l2->val == 0 && l2->next == nullptr)
    {
        // Return l1 in reverse order
        while (l1 != nullptr)
        {
            // Append to new list, then return the head of that list
            append(l1->val);
            l1 = l1->next;
        }

        return head;
    }

    // Case:3
    // Both lists have value stored > 0
    std::list<int> list1;
    std::list<int> list2;
    std::list<int> ans;

    // Populate new std::list(s) with custom list info to facilitate use of STL funtionality
    // Revesring the order as we go
    while (l1 != nullptr)
    {
        list1.push_front(l1->val);
        l1 = l1->next;
    }

    while (l2 != nullptr)
    {
        list2.push_front(l2->val);
        l2 = l2->next;
    }

    // We always want to make sure we are iterating over the larger list
    if (list1.size() < list2.size())
    {
        std::swap(list1, list2);
    }

    int carry = 0;
    int list2Val = 0;
    int res = 0;
    bool flag = false;

    for (auto iter = list1.rbegin(); iter != list1.rend(); ++iter)
    {
        list2Val = list2.back();

        // If the flag has been set, then we have used the only element left in the list
        // before, so just keep using zeros from here on.
        if (list2.size() == 1 && flag)
        {
            list2Val = 0;
        }

        res = *iter + list2Val + carry;

        if (res > 9)
        {
            res = res % 10;
            carry = 1;
        }
        else
        {
            // Reset carry
            carry = 0;
        }

        // Push res back onto new answer list
        ans.push_back(res);

        // Pop back the last element from list 2 so we can keep using .back() in the calc above
        // Make sure we dont pop the last element though or we try to access a null element
        // in the calc above
        if (list2.size() > 1)
        {
            list2.pop_back();
        }
        else
        {
            flag = true;
        } 
    }

    if (carry == 1)
    {
        ans.push_back(1);
    }

    // Repopulate a new list using the ListNode custom struct with
    // the data from the answer list
    ListNode* it = nullptr;

    for (auto iter = ans.begin(); iter != ans.end(); ++iter)
    {
        ListNode* node = new ListNode(*iter);

        if (iter == ans.begin())
        {
            head = node;
            it = node;
        }
        else
        {
            it->next = node;
            it = it->next;
        }
    }

    // Make sure we point to null once we are off the end of the list
    it->next = nullptr;

    return head;
}

ListNode* addNode(int value)
{
    ListNode* node = new ListNode(value);

    return node;
}

ListNode* createList(std::vector<int> values)
{
    ListNode* head = new ListNode(values[0]);
    ListNode* it = head;

    for (int i = 1; i < values.size(); ++i)
    {
        it->next = addNode(values[i]);
        it = it->next;
    }

    it->next = nullptr;

    return head;
}

int main()
{
    // INPUT
    /*[0, 8, 8, 8, 8, 2, 9, 3, 1, 1]
    [0, 9, 1, 5, 5, 5, 1, 1, 6]*/

    // MY OUTPUT
    // [0,8,8,8,8,2,9,3,1,1]

    // EXPECTED OUTPUT
    // [0,7,0,4,4,8,0,5,7,1]

    std::vector<int> list1Values = { 0, 8, 8, 8, 8, 2, 9, 3, 1, 1 };
    std::vector<int> list2Values = { 0, 9, 1, 5, 5, 5, 1, 1, 6 };

    ListNode* list1Head = createList(list1Values);
    ListNode* list2Head = createList(list2Values);

    ListNode* ansHead = addTwoNumbers(list1Head, list2Head);

    while (ansHead != nullptr)
    {
        std::cout << "[ " << ansHead->val << " ], ";
        ansHead = ansHead->next;
    }

	return 0;
}