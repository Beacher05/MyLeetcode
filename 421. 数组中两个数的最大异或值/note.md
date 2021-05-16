# 421. 数组中两个数的最大异或值

链接：

#### (https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/)

给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j < n 。

进阶：你可以在 O(n) 的时间解决这个问题吗？



## 解法1：排序+剪枝

由于异或可以看做是不进位加减，所以先将数排序，从最大得两个数开始比较，若两数的相加的和比当前结果还小，则break（进位比不进位小）,不排序和剪枝则退化为暴力。

```cpp
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        sort(nums.begin(), nums.end());      //排序
        int n = nums.size();
        long long maxValue = 0;
        for (int i = n -1; i >= 1; i--) {
            for (int j = i -1; j >= 0; j--) {
                if ((long long)(nums[i]) + nums[j] < maxValue) {      //剪枝操作
                    break;
                }
                maxValue = max(maxValue, (long long)(nums[i] ^ nums[j]));
            }
        }
        return maxValue;

    }
};
```

空间复杂度：O(1)（记录结果）

时间复杂度  o(nlogn+n**n)=O(n*n)

相关题目：



## 解法2：哈希表

设 x=a[i]^a[j]，x为最终的结果，则a[i]=x^a[j]。又因为x的最大值是已知的， 由此，可以通过逐位延长，两次遍历来寻找有没符合的结果，若找到了，则当前位为1，若没有则为0。由于是延长位，所以之前位的结果得以保存。

```cpp
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int High_bit=30;            //数据在 0-2^31 用0-30 即可表示。
        int result=0;
        for(int i=High_bit;i>=0;i--){
            unordered_set<int> seen;
            for(int num:nums){
                seen.insert(num>>i);        //在每一次的哈希表与遍历中，都是使用num>>i,表示num从最高位到第i位的大小，当i为0时，即为num本身，
            }
            int x=result*2+1;         //假设当前位可以为1。
            bool find=false;

            for(int num:nums){
                if(seen.count((num>>i)^x)){ // 由于i之前的几位已处理过，这步可看作前几位为当前最大的几对中，当前有没有可以取1的。
                    find=true;
                    break;
                }
            }
            if(find){ //更新，准备下一位计算
                result=x; //有，保持
            }else{
                result=x-1;//没有， -1
            }
        }
        return result;
    }
};
```

空间复杂度：O(n)（哈希表）

时间复杂度  o(32*2*n)=O(n)

相关题目：



## 解法3：字典树

可以将数字看成一串31bit 的2进制数，如 00000000 11111111 00001111 11110000，则在树尽量寻找与当前位不同的位，如 11111111 00000000 11110000 00001111，如果没有则取相同的位。从高位到低位构建字典树，并计算出结果。 

```cpp
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
```

空间复杂度：O(n*logC)     n为数组长度  C为数据范围 log来自zero和one的二分 

时间复杂度  O(n*logC)

相关题目：208



