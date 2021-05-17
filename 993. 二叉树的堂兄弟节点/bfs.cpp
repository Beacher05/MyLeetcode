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
        TreeNode* parentY=nullptr;                // 声明四个变量存放结果
        queue<pair<TreeNode*,TreeNode*>> NandP;        // 声明一个队列存放当前节点与父节点
        NandP.emplace(root,nullptr);
        while(!NandP.empty()){                       // 层次遍历
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

            if(findX||findY){           // 完成一层的查找，如果找到一个或两个就可以退出了
                break;
            }

        }
        return findX&&findY&&parentX!=parentY;             // 返回结果
    } 
};
