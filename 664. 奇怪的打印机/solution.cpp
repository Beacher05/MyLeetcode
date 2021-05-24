class Solution {
public:
    int strangePrinter(string s) {
        int n=s.size();
        vector<vector<int>> dp(n,vector<int>(n));
        for(int i=n-1;i>=0;--i){
            dp[i][i]=1;        //初始化
            for(int j=i+1;j<n;++j){ 
                if(s[i]==s[j]) dp[i][j]=dp[i][j-1];      //相等
                else{
                    int mmin=INT_MAX;
                    for(int k=i;k<j;++k){              // 找k
                        mmin=min(mmin,dp[i][k]+dp[k+1][j]);
                    }
                    dp[i][j]=mmin;
                }
            }
        }
        return dp[0][n-1];   //依dp数组含义返回结果
    }
};