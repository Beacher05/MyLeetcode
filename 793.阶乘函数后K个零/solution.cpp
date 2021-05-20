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