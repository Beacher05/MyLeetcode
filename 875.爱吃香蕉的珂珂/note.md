#### 875. 爱吃香蕉的珂珂

#### https://leetcode-cn.com/problems/koko-eating-bananas/

珂珂喜欢吃香蕉。这里有 N 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 H 小时后回来。

珂珂可以决定她吃香蕉的速度 K （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 K 根。如果这堆香蕉少于 K 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  

珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。

返回她可以在 H 小时内吃掉所有香蕉的最小速度 K（K 为整数）。

 这道题求的是在 H 小时内吃掉所有香蕉的最小速度 K（K 为整数）。所以要先确定最小速度和最大速度。

首先要吃香蕉，所以最小值为1，又因为一小时最多吃一堆，所以最大速度应该是最大一堆的个数，其余细节与1011 相似。

```cpp
class Solution {
private:
    bool CantEat(vector<int>& piles,int h,int k){
        int time=0;
        for(int banana:piles)
            time+=(banana-1)/k+1;    //计算出吃完当前堆的天数
        return time>h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left=1,right=*max_element(piles.begin(), piles.end());   //确定上下界
        while(left<right){ //二分查找，找符合条件的最小值
            int mid=left+(right-left)/2;
            if(CantEat(piles,h,mid))   //吃不完，移动左，使变大
              left=mid+1;
            else                 //吃得完，移动右，使变小，逼近最小
              right=mid;
        }
        return left;   //循环结束时，执行的是left=middle+1,处于有效区间内。 
    }
};
```

做法步骤：

1. 分析题意，确定区间
2. 根据题意写判断函数
3. 进行二分查找