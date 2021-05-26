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