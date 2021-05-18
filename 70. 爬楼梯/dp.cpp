class Solution {
public:
    int climbStairs(int n) {
        if(n<3) return n;
        int dp[3]={0,1,2};      //滚动dp数组
        for(int i=3;i<=n;++i){
            dp[0]=dp[1]+dp[2];
            dp[1]=dp[2];
            dp[2]=dp[0];
        }
        return dp[0];
    }
};