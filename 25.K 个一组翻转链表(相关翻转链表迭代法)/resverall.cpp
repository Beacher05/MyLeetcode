class Solution {
public:
    ListNode* reverseList(ListNode* head) {
ListNode* c;
ListNode* b=head;
ListNode* a=NULL;
while(b){
    c=b->next;
    b->next=a;
    a=b;
    b=c;
}
return a;
    }
};