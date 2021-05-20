/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
ListNode* reverse(ListNode*pre,ListNode*cur){
    if(cur==NULL)
    return pre;
    ListNode* tmp=cur->next;  //保存原来cur->next,用于下一轮递归
    cur->next=pre;
    return reverse(cur,tmp);
}
public:
    ListNode* reverseList1(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* p = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return p;
    }
    ListNode* reverseList(ListNode* head) {
	return reverse(NULL,head);
    }
}
