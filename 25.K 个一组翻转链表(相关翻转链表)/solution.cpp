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
private:
    void reverse(ListNode * &root,int k){
        int t=k;
        ListNode* tail=root;
        
        while(tail!=nullptr&&t--) tail=tail->next;
        if(tail==nullptr){root=nullptr;  return;} ;
        tail=tail->next;
        ListNode* a=root->next,*b=a->next;
        while(k-->1){
            ListNode* c=b->next;
            b->next=a;
            a=b;
            b=c;
        }
        root->next->next=tail;
        ListNode* nextroot=root->next;
        root->next=a;
        root=nextroot;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy=new ListNode(-1,head);
        ListNode* cur=dummy;
        while(cur!=nullptr){
            reverse(cur,k);
        }
        return dummy->next;

    }
};