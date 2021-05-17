#### 993. 二叉树的堂兄弟节点

#### https://leetcode-cn.com/problems/cousins-in-binary-tree/

简单来说。这道题是寻找指定节点的父节点和深度的结合，将这两道题结合在一起，就可以解出来。



## 方法1：DFS

使用dfs的方法简单粗暴，在递归的时候，参数附上父节点和深度的信息，就可以了。代码中的保存结果的变量也可以用全局变量。

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
private:
   void traversal(TreeNode* cur,TreeNode* parent,int target,int depth,int& Dx_y,TreeNode* &Px_y)   // 传入当前节点，父节点，目标值，当前深度，后面两个传引用，用于保存搜寻到的结果
   {
       if(cur==nullptr) return;
       if(cur->val==target){
           Px_y=parent;
           Dx_y=depth;
           return;
       }
       if(cur->left) traversal(cur->left,cur,target,depth+1,Dx_y,Px_y);     // 递归子节点，深度加1
       if(cur->right) traversal(cur->right,cur,target,depth+1,Dx_y,Px_y);
   }
public:
    bool isCousins(TreeNode* root, int x, int y) {
        int x_depth=0,y_depth=0;
        TreeNode* x_parent=nullptr,*y_parent=nullptr;   // 声明4个遍历保存结果
        traversal(root,nullptr,x,0,x_depth,x_parent);
        traversal(root,nullptr,y,0,y_depth,y_parent);
        return x_depth==y_depth&&x_parent!=y_parent;    //按题目要求，深度相同，父节点不同 
    }
};
```

时间复杂度：O(n)O(n)，其中 nn 是树中的节点个数。在最坏情况下，我们需要遍历整棵树，时间复杂度为 O(n)O(n)。

空间复杂度：O(n)O(n)，即为深度优先搜索的过程中需要使用的栈空间。在最坏情况下，树呈现链状结构，递归的深度为 O(n)O(n)。

相关题目：



## 方法2：BFS

可以使用DFS的话同时也可以使用BFS, 同时，因为层次遍历时，本层节点相同，所以，但在一层中只找到一个，则说明另外一个在跟低层中，若同时找到，则只需判断其父节点是否相同。

```c++
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
    bool isCousins(TreeNode* root, int x, int y) {
        bool findX=false;
        bool findY=false;
        TreeNode* parentX=nullptr;
        TreeNode* parentY=nullptr;
        queue<pair<TreeNode*,TreeNode*>> NandP;
        NandP.emplace(root,nullptr);
        while(!NandP.empty()){
            for(int i=NandP.size();i>0;i--){
            pair<TreeNode*,TreeNode*>& cur=NandP.front();
            if(cur.first->val==x){
                findX=true;
                parentX=cur.second;
            }
            else if(cur.first->val==y){
                findY=true;
                parentY=cur.second;
            }else{
                if(cur.first->left){
                    NandP.emplace(cur.first->left,cur.first);
                }
                if(cur.first->right){
                    NandP.emplace(cur.first->right,cur.first);
                }
            }
               NandP.pop();
            }

            if(findX||findY){
                break;
            }

        }
        return findX&&findY&&parentX!=parentY;
    }
};

```

时间复杂度：O(n)O(n)，其中 nn 是树中的节点个数。在最坏情况下，我们需要遍历整棵树，时间复杂度为 O(n)O(n)。

空间复杂度：O(n)O(n)，即为广度优先搜索的过程中需要使用的队列空间。

相关题目：

