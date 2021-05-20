#### [793. 阶乘函数后 K 个零]

#### (https://leetcode-cn.com/problems/preimage-size-of-factorial-zeroes-function/)

这道题的数学理论性极强，关于理论证明和结论的，可见

https://leetcode-cn.com/problems/preimage-size-of-factorial-zeroes-function/solution/c-ji-jian-er-fen-jie-fa-chao-guo-100-by-op07g/

这里就只是解释补充几点：

1. 如果有这样的结果，那么数值必为5，是指最后一位0-4或者5-9的五位，对5取余。

2. 可知，数值满5必定会加>=1,并且是单独递增的，当加的那个数大于1时，相关的K就取不到。

3. 二分时的判断，二分的区间是左闭右开，所以退出条件是left<right,并且 小于时是left=m+1,大于等于时是r=m,是因为m是不符合要求的，需要排除在区间外。

4. 小于时是left=m+1,大于等于时是r=m，所以，找到的最后那个数是大于等于K区间的最小值。

5. 判断是否等于，返回结果

   ```cpp
   class Solution {
   public:
       long long f(long long n) {
           long long result = 0ll;
           for (long long p = n / 5;p;p /= 5)        //通过计算质因子5的个数累加得到0的个数，leetcode172
               result += p;
           return result;
       }
   
       int preimageSizeFZF(int K) {
           long long r = 1ll + 5ll * K;
           long long l = 4ll * K+1;       //上下界
           while (l < r) {
               long long m = (l + r) / 2;
               if (f(m) < K) l = m + 1;
               else r = m;                 //二分查找
           }
           return f(l) == K ? 5 : 0;
       }
   };
   ```

   

# 关于二分法：

1. 确定上下界，左右开闭情况
2. 确定查找目标的定义，是等于，大于等于还是小于等于
3. 退出条件：左闭右开为left<right,因为left=right 时[left,right) 是个无效区间 ，左闭右开为left<=right,因为left=right 时[left,right] 是个有效区间
4. 跳跃：闭区间，则left/rihgt=mid+1,开区间为 left/rihgt=mid。
5. 目标：找等于：既要判断m>target,也要判断m<target， 找大于等于，只要判断m<target, 找小于等于，只要判断m>target
6. 结果：一般为left 指向的位置

