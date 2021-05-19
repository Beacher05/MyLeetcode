class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int l, int r) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
 
        // 注意这里是 L 不是 1
        r -= l;
        // hh 就是 “哈哈” 的意思 ...
        // 啊呸。hh 是 head 的意思，为了防止与 height 的简写 h 冲突
        ListNode* hh = dummyHead;
        while (l-- > 1)
            hh = hh->next;
 
        ListNode* prv = hh->next;
        ListNode* cur = prv->next;
        while (r-- > 0) {
            ListNode* nxt = cur->next;
            cur->next = prv;
            prv = cur;
            cur = nxt;
        }
        hh->next->next = cur;
        hh->next = prv;
        return dummyHead->next;
    }
};
