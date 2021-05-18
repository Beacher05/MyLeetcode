#### 1442. 形成两个异或相等数组的三元组数目

#### https://leetcode-cn.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/

给你一个整数数组 arr 。

现需要从数组中取三个下标 i、j 和 k ，其中 (0 <= i < j <= k < arr.length) 。

a 和 b 定义如下：

a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
注意：^ 表示 按位异或 操作。

请返回能够令 a == b 成立的三元组 (i, j , k) 的数目。

 

这道题一看异或就知道需要使用到前缀和的规律来推，记s[i] 为a[0]^....^a[i-1],（左闭右开），并初始化s[0]=0,方便递推。

则a=s[j]^s[i],b=s[k+1]^s[j],又因为a=b,所以有s[i]=s[k+1],题目便转换为在满足s[i]=s[k+1]时，对应的i,j,k有多少，其中0 <= i < j <= k < arr.length。

自然而然会想到三重循环遍历i,j,k。

## 方法一：三重循环

```cpp
class Solution {
public:
    int countTriplets(vector<int> &arr) {
        int n = arr.size();
        vector<int> s(n + 1);
        for (int i = 0; i < n; ++i) {
            s[i + 1] = s[i] ^ arr[i];
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j; k < n; ++k) {
                    if (s[i] == s[k + 1]) {
                        ++ans;
                    }
                }
            }
        }
        return ans;
    }
};

```

时间复杂度（n^3）;

空间复杂度（n）s数组的大小。

## 方法二：双重循环

注意到在三重循环最内层判断中，只需j符合取值要求，而j具体的值无关，而且ans在一层k中被加了k-i次，从理论上讲，在(i,k)区间内的每一个j,都能为结果贡献一，其依据是那一部分代表s[j] ，计算中被约去了。

```cpp
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n=arr.size();
        vector<int> s(n+1);
        for(int i=1;i<=n;i++){
            s[i]=s[i-1]^arr[i-1];           // s[i] 表示从a[0]^...^a[i-1] 的结果。其中s[0]=0,才能进行下一步递推求值
        } 
       int result=0;
       for(int i=0;i<n;i++){
           for(int k=i+1;k<n;k++)
           if(s[i]==s[k+1])  result+=(k-i);
       }
        return result;       // 返回结果
    }
};
```

时间复杂度（n^2）;

空间复杂度（n）s数组的大小。

## 方法三：哈希表

可以看出，双重循环的本质是一个寻找的过程，可以使用哈希表进一步优化到O(n)。

当下标为i1,i2,i3, 时，都满足s[i]=s[k+1],

又方法二可知，对于特定的s[i],他们对res,的贡献为（k-i1）+(k-i2).....+(k-in)=n*k+(i1+i2+...+in),所以需要两个哈希表来记录每一个s[i]对应的值出现的次数，以及下标i的和。需要遍历所有的s[i]。

```cpp
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n=arr.size();
        vector<int> s(n+1);
        for(int i=1;i<=n;i++){
            s[i]=s[i-1]^arr[i-1];           // s[i] 表示从a[0]^...^a[i-1] 的结果。其中s[0]=0,才能进行下一步递推求值
        }
       unordered_map<int,int> cnt,sum;      //使用哈希表来记录对应s[i]出现的次数和下标和。 
       int result=0;
       for(int k=0;k<n;k++){       // 遍历所有的s[i]。
           if(cnt.count(s[k+1])){      // 之前出现过，说明有符合的下标k出现。
               result+=cnt[s[k+1]]*k-sum[s[k+1]];     // 计算当前的k对结果的贡献。
           }
           ++cnt[s[k]];           // 出现次数加1 
           sum[s[k]]+=k;          // 下标和相加
       }
        return result;       // 返回结果
    }
};
```

又注意到循环中只用到了s[k+1]和s[k],所以可以对空间进行压缩。

```cpp
class Solution {
public:
    int countTriplets(vector<int> &arr) {
        int n = arr.size();
        unordered_map<int, int> cnt, total;
        int ans = 0, s = 0;
        for (int k = 0; k < n; ++k) {
            int val = arr[k];
            if (cnt.count(s ^ val)) {       //s^val 即s[k+1],s即s[k]。
                ans += cnt[s ^ val] * k - total[s ^ val];
            }
            ++cnt[s];
            total[s] += k;
            s ^= val;
        }
        return ans;
    }
};

```

时间复杂度：O(n)O(n)，其中 nn 是数组 \textit{arr}arr 的长度。

空间复杂度：O(n)O(n)。我们需要使用 O(n)O(n) 的空间存储两个哈希表。

