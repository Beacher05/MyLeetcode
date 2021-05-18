#### 746. 使用最小花费爬楼梯

#### https://leetcode-cn.com/problems/min-cost-climbing-stairs/

这还是一道dp题，是爬楼梯的进阶版。

依旧使用递归五部曲：

这是一道动态规划的入门题。判定一道题使用动态规划的标准是看当前状态是否依赖之前的状态，即问题由许多重复的子问题组成，判定为是之后有以下几个步骤：

1. 确定dp数组（dp table）以及下标的含义
2. 确定递推公式
3. dp数组如何初始化
4. 确定遍历顺序
5. 举例推导dp数组

具体到这道题：

1、dp数组含义：跳到第i阶的最低花费为dp[i]。

2、要到达第i阶，可以从第i-2阶跳两步而来，也可以从第i-1阶跳一步而来，而为了是最小代价，所以取最小值，同时支付到底该点对应的cost[i]。即dp[i]=min(dp[i-1]+dp[i-2])+cost[i];

3 、前两步从起点出发，只需支付当前的cost即可，之前的为0。

4、依赖之前的状态，即从前往后遍历。

5、 0，1，2，3,5,8，。。。。

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int>dp(cost.size());
        dp[0]=cost[0];
        dp[1]=cost[1];      //初始化
        for(int i=2;i<cost.size();++i){
            dp[i]=min(dp[i-1],dp[i-2])+cost[i];   //dp公式
        }
        return min(dp[cost.size()-1],dp[cost.size()-2]);    //最后一步看作不需要代价，那么取倒一倒二的最小值即为结果。
    }
};

```

