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
