#### 1143. 最长公共子序列

#### (https://leetcode-cn.com/problems/longest-common-subsequence/)

详细的讲解如下：

https://mp.weixin.qq.com/s?__biz=MzUxNjY5NTYxNA==&mid=2247487526&idx=2&sn=0932bd5f65fdb4d3633df573c93cf7f1&scene=21#wechat_redirect

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>>dp(text1.size()+1,vector<int>(text2.size()+1,0));
        for(int i=1;i<=text1.size();i++)
            for(int j=1;j<=text2.size();j++)
                if(text1[i-1]==text2[j-1]){
                    dp[i][j]=dp[i-1][j-1]+1;
                }else{
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }

        return dp[text1.size()][text2.size()];
    }
};
```

但是注意到，dp[i] [j]，依赖于dp[i-1] [j-1],dp[i-1] [j] ,dp [i] [ j-1],只是依赖前面俩行完全可以进行压缩，一目了然的是可以压缩成2行。更注意到，dp[i-1] [j] 便是原来的将要被覆盖的dp[i] [j] ,dp[i] [j-1] 在同一行，就只需要dp [i-1] [j-1] 。只要dp[j]在本轮循环中还没有被重新赋值，那么就是dp[i-1] [j] 详细见代码。

```cpp
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
```



变种题目：1035

```cpp
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
```

原理一致，从比较字符变成数字。