class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int start=0,res=1;
        for(int i=1;i<nums.size();i++){
            if(nums[i]<=nums[i-1])   start=i;
            res=max(res,i-start+1);
        }
        return res;
    }
};