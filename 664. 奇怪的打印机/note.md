#### [664. 奇怪的打印机]

#### [(https://leetcode-cn.com/problems/strange-printer/)

这是一道区间动态规划的题。

为什么是动态规划，因为打印字符时，可以看作是在之前的基础上添加一个字符。

动态规划5步曲：

1、确定dp数组和含义：

​	dp[i] [j] 表示打印从下标i到下标j的打印方法为dp[i] [j]。

2、确定递推公式：

​	当s[i]==s[j] 时，dp[i] [j] = dp[i] [j-1] ,即在附加打印 s[j]时，可以在打印s[i]时一起打出。

​	当s[i]!=s[j]时，由于不相等，所以不能一起打印，此时可以看作需要分成两部分打印，一部分打印s[i]....s[k]，一部份打	印s[k]....s[j]，那么就需要遍历找到使得dp[i] [j]=dp[i] [k]+dp[k] [j]最小的k（i<k<j）。

3、初始化

​	当区间只有一个字符时为1，即dp[i] [i]=1。

4、遍历顺序

​	由递推公式：dp[i] [j] =dp[i] [j-1] 和 dp[i] [j]=dp[i] [k]+dp[k] [j] （i<k<j），可以推出i 从右到左，j从左到右。

5 、举例：略

​	

```cpp
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
```

