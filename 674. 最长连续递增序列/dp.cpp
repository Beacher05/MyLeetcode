class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int result=1;
        int n=nums.size();
        if(0==n) return 0;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){
            {if(nums[i]>nums[i-1])
              dp[i]=dp[i-1]+1;
              
              if(dp[i]>result) result=dp[i];
              }
        }
        return result;
    }
};