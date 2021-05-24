

#### [312. 戳气球](https://leetcode-cn.com/problems/burst-balloons/)

这是一道区间动态规划的题。

为什么是动态规划，由于戳气球的操作操作会使原来不相邻的两个气球变相邻，所以不如逆向思维变为放气球，放入的第一个气球即为最后戳破的一个气球，放入的最后一个即为戳破第一个气球。每放入一个气球与戳破气球时得分一致。又按照题意，在前后放置一个值为1的虚气球。变为新数组val

动态规划5步曲：

1、确定dp数组和含义：

​	dp[i] [j] 表示在val区间从下标i到下标j的开区间内，可以得分的最大值。

2、确定递推公式：

​	注意到，如果在放入区间（i,j）内放入的第一个气球的位置为k1,那么设接下放入的第二个气球为k2,如果放入的区间在（i,k1）内，那么在（i,k1）区间，k2所在的位置即为放入的第一个位置，以此类推，是个递归的过程，所以可以得到dp[i] [j]=val[i]*val[k] *val[ j ]+dp[i] [k]+ dp[ k] [ j ]。其中的k为第一个放入下标的位置，val[i] *val[k] *val[ j ]为第一次在位置k放入气球得到的分数，dp[i] [k]+ dp[ k] [ j ]，为前后区间已经得到的分数。又因为放入得到的分数又由于需要最大值，所以需要寻找使得dp [i] [j] 最大的k。

3、初始化

​	因为i,j是开区间，所以。当j<=i+1时，区间无效，设为0。

4、遍历顺序

​	由递推公式：dp[i] [j] =max(dp[i] [j],val[i]*val[k] *val[ j ]+dp[i] [k]+ dp[ k] [ j ])（i<k<j)，可以推出i 从右到左，j从左到右。

5 、举例：略

```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n=nums.size();
        vector<int>val(n+2);
        val[0]=val[n+1]=1;
        for(int i=0;i<n;i++){
            val[i+1]=nums[i];
        }     //前后+1
        vector<vector<int>> dp(n+2,vector<int>(n+2));
        for(int i=n-1;i>=0;--i)    //递归
            for(int j=i+2;j<=n+1;++j)
                for(int k=i+1;k<j;k++){
                    int sum=val[i]*val[j]*val[k];
                    sum+=dp[i][k]+dp[k][j];
                    dp[i][j]=max(dp[i][j],sum);
                }
        }

        return dp[0][n+1];  //以题目返回结果
    }
};
```

