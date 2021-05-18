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