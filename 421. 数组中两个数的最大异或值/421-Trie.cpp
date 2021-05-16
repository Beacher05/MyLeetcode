struct Tree{
    Tree* zero=nullptr;
    Tree* one=nullptr;
    Tree(){}                      //定义一个字典树节点来生成字典树
};
class Solution {
private:
    Tree* root=new Tree();
    static constexpr int HIGH_BIT = 30;        //数据在 0-2^31 用0-30 即可表示。

    void add(int num){
        Tree* cur=root;
        for(int k=HIGH_BIT;k>=0;k--){
            int bit=(num>>k)&1;            //从最高位开始取1位
            if(bit==1){                         //生成对应的节点树
                if(cur->one==nullptr)
                    cur->one=new Tree();
                cur=cur->one;
            }else{
                if(cur->zero==nullptr)
                    cur->zero=new Tree();
                cur=cur->zero;
            }
        }
    }

    int cheak(int num){
        int x=0;
        Tree* cur=root;
        for(int k=HIGH_BIT;k>=0;k--){
            int bit=(num>>k)&1;            //从最高位开始取1位
            if(bit==1){                    // 依据当前位来选择路径和结果
                if(cur->zero!=nullptr){
                    cur=cur->zero;
                    x=x*2+1;
                }else{
                    cur=cur->one;
                    x=x*2;
                }
            }else{
                if(cur->one!=nullptr){
                    cur=cur->one;
                    x=x*2+1;
                }else{
                    cur=cur->zero;
                    x=x*2;
                }
            }
        }
        return x;
    }

public:
    int findMaximumXOR(vector<int>& nums) {
        int result=0;
        int n=nums.size();
        for(int i=1;i<n;i++){
            add(nums[i-1]);            // 此时树中有0~n-2 节点的数据
            result=max(result,cheak(nums[i]));       // 将树与1~n-1 比较 即可得到最大值。
        }
        return result;
    }
};