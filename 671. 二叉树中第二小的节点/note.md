#### 671. 二叉树中第二小的节点

#### https://leetcode-cn.com/problems/second-minimum-node-in-a-binary-tree/

给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一个。

更正式地说，root.val = min(root.left.val, root.right.val) 总成立。

## 1、遍历加set 去重

遍历二叉树，储存结果与一个set中，实现排序和去重，再使用迭代器取出其中第二小的值。（没有用到附加的特性，属于通用解法）

```cpp
lass Solution {
public:
    set<int> s;
    void inOrderTraversal(TreeNode* root) {    //其实这里的遍历顺序无所谓
        if(root == NULL) return ;
        inOrderTraversal(root -> left);
        s.insert(root -> val);       //加入到set中
        inOrderTraversal(root -> right);
    }
    int findSecondMinimumValue(TreeNode* root) {
        inOrderTraversal(root);
        if(s.size() < 2) return -1;
        int cnt = 0;
        for(auto it = s.begin(); it != s.end(); ++it) {
            if(cnt == 1) {
                return *it;                 //使用迭代器取出第二下的数
            }
            ++cnt;
        }
        return -1;
    }
};

```

空间复杂度：O(n) set的大小

时间复杂度：O(n) 遍历二叉树

## 2、利用所给的性质递归

由题意可以推出，根节点是根节点与子节点中最小的，在一层递归中，第二小的数可能是子节点中大的那个，也有可能是在以与根节点相等的子节点为根节点的子树中，可以通过递归返回第二个最小值来解决这个问题。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if(root==nullptr||root->left==nullptr||root->right==nullptr) return -1;  
         //走到叶子节点无需比较，直接返回就行
        int left=root->left->val,right=root->right->val;
        if(left==root->val) left=findSecondMinimumValue(root->left);   
        if(right==root->val) right=findSecondMinimumValue(root->right);
        //在当层递归中，根节点为子节点的最小值，也是树的最小值，第二小的节点必定在与根节点的子树中
        
       // 当层递归逻辑：
        
        if(left==right&&left==root->val) return -1;
        // 三个节点大小相等说明没有第二最小值
        int min_lr=min(left,right);     // 此时分为两种情况，子节点都比父节点大，其中一个子节点与父节点相等。
        if(root->val<min_lr) return min_lr;   //此时root为最小值，返回递归得来的左右子树的小值即为结果
        else  return max(left,right);     //在这种情况下，子树中有一个与根相等，左右子树的大值即为结果
    }
};
```

时间复杂度：O(N)O(N)。其中 NN 是给定树中的节点总数。我们最多访问每个节点一次。
空间复杂度：O(N)O(N)，存储在 \text{ans}ans 和 \text{min1}min1 中的信息为 O(1)O(1)，但我们的深度优先搜索可能会在调用堆栈中存储多达 O(h) = O(N)O(h)=O(N) 的信息，其中 hh 是树的高度。

