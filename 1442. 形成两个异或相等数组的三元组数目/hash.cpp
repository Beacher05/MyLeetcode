class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n=arr.size();
        vector<int> s(n+1);
        for(int i=1;i<=n;i++){
            s[i]=s[i-1]^arr[i-1];           // s[i] 表示从a[0]^...^a[i-1] 的结果。其中s[0]=0,才能进行下一步递推求值
        }
       unordered_map<int,int> cnt,sum;      //使用哈希表来记录对应s[i]出现的词和下标和。 
       int result=0;
       for(int k=0;k<n;k++){
           if(cnt.count(s[k+1])){
               result+=cnt[s[k+1]]*k-sum[s[k+1]];     // 计算当的K对结果的贡献。
           }
           ++cnt[s[k]];           // 出现次数加1 
           sum[s[k]]+=k;          // 下标和相加
       }
        return result;       // 返回结果
    }
};