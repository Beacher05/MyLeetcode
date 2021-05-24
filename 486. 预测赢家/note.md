#### [486. 预测赢家]

#### [(https://leetcode-cn.com/problems/predict-the-winner/)

这是一道区间动态规划的题。

为什么是动态规划，因为取数字时，可以看作是在之前的基础上取。

动态规划5步曲：

1、确定dp数组和含义：

​	dp[i] [j] 表示区间从下标i到下标j，当前玩家与另一个玩家的分数之差的最大值。

2、确定递推公式：

​	轮到当前的玩家取的时候，玩家可以取nums[i],也可以去nums[j],取num[i]时 dp[i] [j]=num[i] - dp[i+1] [j],取num[j]时 dp[i] [j]=num[j] - dp[i] [j-1],取最大值。

3、初始化

​	当区间只有一个字符时为num，即dp[i] [i]=nums[i],且i>j时，无意义，默认为0。

4、遍历顺序

​	由递推公式：dp[i] [j] =max(nums[j]-dp[i] [j-1], nums[i]-dp[i+1] [j])（i<j)，可以推出i 从右到左，j从左到右。

5 、举例：略

```cpp
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
```



变种：数组的长度是偶数；

​			数组的元素之和是奇数，所以没有平局。

#### [877. 石子游戏]

#### [(https://leetcode-cn.com/problems/stone-game/)]

除了上面的做法，还有逻辑上的分析：
如果是偶数堆，设石头的标记为a[0],a[1]......a[n-2],a[n-1]。

那么可以把石头分为2堆 S1:a[0],a[2],.....a[n-2] 和S2:a[1],a[3].....a[n-1],两堆石子数量相等，设为重量为sum1，和sum2,当sum1>sum2时，先手的人取a[0],此时后手只能去a[1]或a[n-1],先手的人只要保持在与后手取的同一端取，就能将S1全取到手，反之，若sum1<sum2,则第一手取a[n-1],之后保持在与后手取的同一端取，就能将S2全取到手。所以先手必胜。

