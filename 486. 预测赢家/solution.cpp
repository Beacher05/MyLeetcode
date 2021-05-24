class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n= nums.size();
        vector<vector<int>>dp(n,vector<int>(n，0));
        for(int i=0;i<n;++i)
            dp[i][i]=nums[i];              //初始化
        for(int i=n-2;i>=0;--i){ 
            for(int j=i+1;j<n;++j)        //初始化顺序
            dp[i][j]=max(nums[i]-dp[i+1][j],nums[j]-dp[i][j-1]);
        }
        return dp[0][n-1]>=0;        //依题意结果
    }
};