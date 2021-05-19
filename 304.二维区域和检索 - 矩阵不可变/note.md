#### 304. 二维区域和检索 - 矩阵不可变

#### https://leetcode-cn.com/problems/range-sum-query-2d-immutable/

1738 题的主要思想来源于此，这道题的sum数组记录的是从（0,0) 到（m,n ）的范围和（m,n）为矩阵的行数，列数。

计算sum 时有 sum[i] [j] =s[i-1] [j] +sum[i] [j-1] - sum [i-1] [j-1] + martix[i] [j] 。

而类似的计算自顶范围（l1,r1）(l2,r2) 就有 sum[l2+1] [r2+1] - sum[ l2+1] [ r1] -sum[ l1] [r2 +1] + sum [ l1] [ r1 ]。

（sum[ i ] [ j ]）为左闭右开区间，所以需要注意加1 操作。

```cpp
class NumMatrix {
public:
    vector<vector<int>> sum;
    NumMatrix(vector<vector<int>>& matrix) {
        int m=matrix.size();
        if(m>0){
            int n=matrix[0].size();
            sum.resize(m+1,vector<int>(n+1));
            for(int i=0;i<m;i++)
                for(int j=0;j<n;j++)
                    sum[i+1][j+1]=sum[i][j+1]+sum[i+1][j]-sum[i][j]+matrix[i][j];
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
         return sum[row2 + 1][col2 + 1] - sum[row1][col2 + 1] - sum[row2 + 1][col1] + sum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
```

