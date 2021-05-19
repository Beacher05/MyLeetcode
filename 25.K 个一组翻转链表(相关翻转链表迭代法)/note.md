#### 25. K 个一组翻转链表

#### (https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

这道题是92（反转指定范围的链表），206（翻转链表）的总和考察。

做这类题，首先从最近简单的反转链表开始，使用的是双指针法，如pa,pb; 在原来的链表中，pa->next==pb,只需要改变为pb->next==pa即可，在实现中，还需要一个辅助指针pc来记录pb->next,防止原来pb->next的信息丢失，修改完毕后，在原来未修改的基础上，移到下一位，即pa=pb(原来pb==pa->next),pb=pc(原来pc==pb->next);直到pb为空。

```cpp
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
```

而反转指定范围的链表，需要要找到反转区间前的一个节点（hh），和反转区间最后的那个节点（在反转结束后可以得到,即cur），并且退出循环是按照范围的大小确定的。最后，还需要将反转好的链表与原来的链表的两部分连接起来。

```cpp
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
            hh = hh->next;      //找反转前的那个节点
 
        ListNode* prv = hh->next;       // 反转部分，prv=a,cur=b,nxt=c
        ListNode* cur = prv->next;
        while (r-- > 0) {             //按范围大小来反转
            ListNode* nxt = cur->next;
            cur->next = prv;
            prv = cur;
            cur = nxt;
        }
        hh->next->next = cur;   //链接后半部分
        hh->next = prv;         //链接前半部分
        return dummyHead->next;
    }
};
```

来到25，由于当区间不满K时，不翻转，所以多了一层判断。具体细节如注释

```cpp
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
    void reverse(ListNode * &root,int k){   //反转（root,root+k）,左右都开的链表
        int t=k;
        ListNode* tail=root;
        
        while(tail!=nullptr&&t--) tail=tail->next;
        if(tail==nullptr){root=nullptr;  return;} ;  //检查长度，并且提前记录，并且将root置空来退出上层循环
        tail=tail->next;
        ListNode* a=root->next,*b=a->next;
        while(k-->1){
            ListNode* c=b->next;
            b->next=a;
            a=b;
            b=c;
        }                          // 范围反转
        root->next->next=tail;
        ListNode* nextroot=root->next;   //记录反转前的第一个节点
        root->next=a;                  //拼接
        root=nextroot;           //可以发现，反转前的第一个节点反转后变为最后一个，也就是下一轮反转的开始的root
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy=new ListNode(-1,head); //左右都开需要虚头节点
        ListNode* cur=dummy;
        while(cur!=nullptr){    //循环中，只要长度小于k就将cur置空，就需要退出
            reverse(cur,k);
        }
        return dummy->next;

    }
};
```

空间复杂度：O（1），使用固定数量的辅助空间记录指针

时间复杂度：O（n）：n为链表长度。