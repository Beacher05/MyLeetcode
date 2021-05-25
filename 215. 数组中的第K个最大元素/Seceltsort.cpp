class Solution {
private:
    int qsort(vector<int>& nums,int k,int left,int right){    //[left,right]区间
        int i=left,j=right;
        int ran=(rand()%(right-left+1))+left;      //生成范围内的随机数
        swap(nums[left],nums[ran]);               // 将区间内的随机数与区间内第一个进行交换。
        int key=nums[left];
        while(i<j){
            while(i<j&&nums[j]>=key) j--;
            while(i<j&&nums[i]<=key) i++;
            if(i<j) swap(nums[i],nums[j]);
        }
        swap(nums[i],nums[left]);    // 如果不进行交换,是否需要将枢纽换回去需要讨论过于繁琐。
        int n=nums.size();
        if(i==n-k) return nums[i];     // 每次排序可以得到第i小，即第n-k大的数
        if(i<n-k) return qsort(nums,k,i+1,right);          // 不够大往右边找
        else return qsort(nums,k,left,i-1);              // 太大往左边找
     }
public:
    int findKthLargest(vector<int>& nums, int k) {
        return qsort(nums,k,0,nums.size()-1);  //不要忘记-1！
    }
};