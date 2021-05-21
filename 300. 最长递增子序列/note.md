#### 300. 最长递增子序列

#### (https://leetcode-cn.com/problems/longest-increasing-subsequence/)

## 1、纯动态规划

一开始，就认为这道题应该是使用动态规划来解，将当前元素与前一个元素对比，若是大于，则是dp[i]=dp[i-1]+1,但是后来又发生了错误，如在序列1，2,3,4,5,9,7,5，8，中的结果是6，即1,2,3,4,5,9而不是1,2,3,4,5,7,8 发现不能只是与前一个数进行比较，应该与之前所有的数比较，然后取最大值。

详细见：https://mp.weixin.qq.com/s?__biz=MzUxNjY5NTYxNA==&mid=2247487371&idx=2&sn=f57561d52e2322279e2c349a24757faa&scene=21#wechat_redirect

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp(n,1);
        int result=dp[0];
        for(int i=1;i<n;++i)
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]) dp[i]=max(dp[i],dp[j]+1);
                result=max(result,dp[i]);
            } 
        return result;
    }
};
```

## 2、贪心+动态+二分

换一个思路，要让子序列尽量长，就得让序列的最后一个元素尽量小，这样才有更大的可能延长子序列。所有，使用一个数组，来记录当子序列长度为i时，满足要求的子序列的最后一个元素的最小值为dp[i]。详细情况见代码注释。

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len=1,n=nums.size();
        vector<int> dp(n+1,0);  // 最大的情况是整个数组递增，序列长度即为结果
        dp[len]=nums[0];  // 初始化第一个
        for(int i=1;i<n;i++){  // 将所有的数字与序列的最后一个元素对比
            if(nums[i]>dp[len]){       // 符合条件延长，并且当前值更新为序列的最后一个元素
                dp[++len]=nums[i];
            }else{   //不符合条件，但是队列中可能有比当前值小的，需要更新，使特定长度的 子序列的最后一个元素更小
                int left=1,right=len;
                while(left<=right){
                    int mid=(right+left)/2;
                    if(dp[mid]<nums[i]) left=mid+1;
                    else right=mid-1;
                }    // 使用二分，找到大于等于当前值的位置，
                dp[left]=nums[i];  // 更新
            }
        }
        return len;// 遍历结束，序列长度即为结果
    }
};

```

由于dp中需要与之前的每一值比较。时间不如贪心使用二分的操作。