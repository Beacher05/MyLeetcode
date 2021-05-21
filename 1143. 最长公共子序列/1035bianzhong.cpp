class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        vector<int>dp(B.size()+1,0);
        for(int i=1;i<=A.size();i++){
            int Nextequal=0;
            for(int j=1;j<=B.size();j++){ 
                int tmp=dp[j];     //记录当前将要被覆盖的dp[i-1][j]作为下次的dp[i-1][j-1]
                if(A[i-1]==B[j-1]){
                       dp[j]=Nextequal+1; //使用上次的dp[i-1][j-1]
                   }
                else{
                       dp[j]=max(dp[j],dp[j-1]);//dp[j]=dp[i-1][j],dp[j-1]=dp[i][j-1]
                   }
                Nextequal=tmp;//更新dp[i-1][j-1]为下次使用。
               }
        }
        return dp[B.size()];
    }
};