class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len=1,n=nums.size();
        vector<int> dp(n+1,0);
        dp[len]=nums[0];
        for(int i=1;i<n;i++){
            if(nums[i]>dp[len]){
                dp[++len]=nums[i];
            }else{
                int left=1,right=len;
                while(left<=right){
                    int mid=(right+left)/2;
                    if(dp[mid]<nums[i]) left=mid+1;
                    else right=mid-1;
                }
                dp[left]=nums[i];
            }
        }
        return len;
    }
};
