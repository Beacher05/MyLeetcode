不多说了，解决下一个最大的元素的问题使用单调栈来解决，具体的理论和分析见东哥题解，我添加一些编码时的细节问题。

https://leetcode-cn.com/problems/next-greater-element-i/solution/dan-diao-zhan-jie-jue-next-greater-number-yi-lei-w/

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n2=nums2.size();
        map<int,int>sres;          //由于题目中明确没有重复的值，并且num1是num2的子集，所以不用判断，使用map 来记录所有值								//的结果
        stack<int> stk;          //小顶栈
        for(int i=n2-1;i>=0;i--){    // 由于比较的是右侧以及栈先进后出的特性，所以从后往前遍历
            while(!stk.empty()&&stk.top()<=nums2[i])                 // 调整当前的栈为小顶栈
                stk.pop();  
            sres[nums2[i]]=stk.empty()?-1:stk.top();             // 下一个最大元素核心，在当前元素没有入栈时。栈顶即为下															//一个最大
            stk.push(nums2[i]);                                   // 当前元素入栈
        }
        vector<int> res;
        for(int i:nums1){
            res.push_back(sres[i]);                  // 收集所需要的结果
        }
        return res;
    }
};
```

变种 503 循环数组

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n=nums.size();
        vector<int> res(n);
        stack<int> stk;
        for(int i=2*n-1;i>=0;i--){    // 假装将数组复制，下来取下标的时候记得取余
            while(!stk.empty()&&stk.top()<=nums[i%n])
                stk.pop();
            res[i%n]=stk.empty()?-1:stk.top();
            stk.push(nums[i%n]);
        }
        return res;
    }
};
```

