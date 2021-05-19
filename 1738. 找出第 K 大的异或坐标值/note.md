#### 1738. 找出第 K 大的异或坐标值

#### https://leetcode-cn.com/problems/find-kth-largest-xor-coordinate-value/

给你一个二维矩阵 matrix 和一个整数 k ，矩阵大小为 m x n 由非负整数组成。

矩阵中坐标 (a, b) 的 值 可由对所有满足 0 <= i <= a < m 且 0 <= j <= b < n 的元素 matrix[i][j]（下标从 0 开始计数）执行异或运算得到。

请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。

通过这几天的异或练习，很快就有了思路，即求出所有m*n个数，然后找出最大。

怎么求呢，设有矩阵：

A  B C D

E F G H

 I J K L   

那么依题意有结果矩阵：

A AB ABC ABCD

AE ABEF ABCEFG ABCDEFGH

AEI ABEFIJ ABCEFGIJK ABCDEFGHIJK

经过观察发现，但i,j>0是，dp[ i ] [ j ]=dp[ i-1 ] [ j ]^dp[i] [j-1]^dp[i-1] [j-1]^matrix[i] [j]。

## 方法一： set法

知道了如何求出所有数值，下来的任务就是找到第K大的数值，一开始习惯性的使用了set,在插入的同时排序，输出结果，但是发现结果中是可以重复的，改用multiset,但是插入操作费时，并且在set中找第k大的数只能靠迭代器一个一个移，效率慢，所以超时了。

```cpp
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
        }            //初始化第0行和第0列，保持结果
        for(int i=1;i<m;++i)
            for(int j=1;j<n;++j){
                dp[i][j]=dp[i-1][j]^dp[i][j-1]^dp[i-1][j-1]^matrix[i][j];
                res.insert(dp[i][j]);
            }    //求出所有
        auto it=res.end();
        while(k--) it--;
        return *it;   //使用迭代器一个个找
    }
};
```

空间复杂度：O(m*n) 为矩阵的大小和set的大小

时间复杂度O (m * n * log m * n  ) 循环次数乘插入

## 2 vector+sort

由于插入操作费时，改为无序存放，再排序，同时vector可以随机访问，可以自己出结果。

```cpp
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        vector<int> res;
        int m=matrix.size();
        int n=matrix[0].size();
        vector<vector<int>> dp(m,(vector(n,0)));
        res.push_back(matrix[0][0]);
        dp[0][0]=matrix[0][0];
        for(int i=1;i<n;i++){
            dp[0][i]=dp[0][i-1]^matrix[0][i];
            res.push_back(dp[0][i]);
        }
         for(int i=1;i<m;i++){
            dp[i][0]=dp[i-1][0]^matrix[i][0];
            res.push_back(dp[i][0]);
        }    //初始化第0行和第0列，保持结果
        for(int i=1;i<m;++i)
            for(int j=1;j<n;++j){
                dp[i][j]=dp[i-1][j]^dp[i][j-1]^dp[i-1][j-1]^matrix[i][j];
                res.push_back(dp[i][j]);
            }  //求出所有
        sort(res.begin(),res.end(),greater<int>());  // 降序排序
        return res[k-1];        // 直接返回结果

    }
};
```

空间复杂度：O(m*n) 为矩阵的大小和set的大小

时间复杂度O (m * n  + log m * n  ) 循环次数加上排序。