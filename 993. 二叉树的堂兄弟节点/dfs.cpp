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