class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<int>dp(text2.size()+1,0);
        for(int i=1;i<=text1.size();i++){
            int Nextequal=0;
            for(int j=1;j<=text2.size();j++){ 
                int tmp=dp[j];     //记录当前将要被覆盖的dp[i-1][j]作为下次的dp[i-1][j-1]
                if(text1[i-1]==text2[j-1]){
                       dp[j]=Nextequal+1; //使用上次的dp[i-1][j-1]
                   }
                else{
                       dp[j]=max(dp[j],dp[j-1]);//dp[j]=dp[i-1][j],dp[j-1]=dp[i][j-1]
                   }
                Nextequal=tmp;//更新dp[i-1][j-1]为下次使用。
               }
        }
        return dp[text2.size()];
    }
};