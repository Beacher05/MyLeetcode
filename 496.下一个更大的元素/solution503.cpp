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