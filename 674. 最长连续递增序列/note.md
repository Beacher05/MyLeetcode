#### 674. 最长连续递增序列

#### (https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/)

## 1、动态规划

思路：这道题就与300一开始的思路一样了，如果符合条件，则dp[i]=dp[i-1]+1,但是不等应该是dp[i]=1,而不是拷贝过来。

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int result=1;
        int n=nums.size();
        if(0==n) return 0;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){
            {if(nums[i]>nums[i-1])
              dp[i]=dp[i-1]+1;
              
              if(dp[i]>result) result=dp[i];
              }
        }
        return result;
    }
};
```

## 2、双指针

可以考虑使用双指针来解决这道题，一个指针start指向递增序列的第一个，一个end指向末尾，同时记录区间长度的最大值。

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int start=0,res=1;//默认长度为1个，必须是1
        for(int i=1;i<nums.size();i++){  //i即为end
            if(nums[i]<=nums[i-1])   start=i;   //必须有等于，（2，2，2）算1，不符合要求移动start指针
            res=max(res,i-start+1);   //记录区间长度的最大值
        }
        return res;
    }
};
```



时间复杂度一致，但是双指针的空间复杂度好。