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
        if(left==right&&left==root->val) return -1;
        // 三个节点大小相等说明没有第二最小值
        int min_lr=min(left,right);     // 此时分为两种情况，子节点都比父节点大，其中一个子节点与父节点相等。
        if(root->val<min_lr) return min_lr;
        else  return max(left,right);
    }
};