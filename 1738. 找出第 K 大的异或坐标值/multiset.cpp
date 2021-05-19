class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        multiset<int> res;
        int m=matrix.size();
        int n=matrix[0].size();
        vector<vector<int>> dp(m,(vector(n,0)));
        res.insert(matrix[0][0]);
        dp[0][0]=matrix[0][0];
        for(int i=1;i<n;i++){
            dp[0][i]=dp[0][i-1]^matrix[0][i];
            res.insert(dp[0][i]);
        }
         for(int i=1;i<m;i++){
            dp[i][0]=dp[i-1][0]^matrix[i][0];
            res.insert(dp[i][0]);
        }
        for(int i=1;i<m;++i)
            for(int j=1;j<n;++j){
                dp[i][j]=dp[i-1][j]^dp[i][j-1]^dp[i-1][j-1]^matrix[i][j];
                res.insert(dp[i][j]);
            }
        auto it=res.end();
        while(k--) it--;
        return *it; 
    }
};