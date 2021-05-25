#### [215. 数组中的第K个最大元素]

#### [(https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)

寻找第K大的数字，可以使用快速排序和堆排序。

## 方法一 :快速排序

详细知识见袁厨文章：

https://mp.weixin.qq.com/s?__biz=Mzg3NDU4MDQ3Mw==&mid=2247491853&idx=1&sn=ebdf29c58fb6456f181bb58162f3d557&chksm=cecc319bf9bbb88d3da01d5c170c26b2fa381aec6c72cb63c36a4128e11cc7d7631d9f3810fa&scene=21#wechat_redirect

此处记录踩到的坑：

```cpp
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


```

这个区间传错和随机枢纽需要讨论真的是被坑死！

## 方法二：堆排序

建立一个大根堆，做 k - 1*k*−1 次删除操作后堆顶元素就是我们要找的答案

```cpp
class Solution {
private:
    void adjustH(vector<int>& nums,int root,int Hsize){
        int left=2*root+1,right=2*root+2,maxN=root;      //调整堆为大顶堆
        if(left<Hsize&&nums[left]>nums[maxN])
            maxN=left;
        if(right<Hsize&&nums[right]>nums[maxN])
            maxN=right;
        if(maxN!=root){
            swap(nums[root],nums[maxN]);
            adjustH(nums,maxN,Hsize);
        }
    }
    void makeH(vector<int>&n,int Hsize){
        for(int i=Hsize/2;i>=0;i--){
            adjustH(n,i,Hsize);              //自下而上调整建堆
        }
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int Hsize=nums.size();
        makeH(nums,Hsize);
        for(int i=nums.size()-1;i>=nums.size()-k+1;i--){          // 删除k次堆顶得到结果
            swap(nums[0],nums[i]);
            --Hsize;
            adjustH(nums,0,Hsize);   //缩小堆大小
        }
        return nums[0];
    }
};
```

## 方法三：API法

```cpp
int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end,great<int>());
        return nums[k];
    }

int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : nums) {
            if (minHeap.size() < k) {
                minHeap.push(num);
            } else if (minHeap.top() < num) {
                minHeap.pop();
                minHeap.push(num);
            }
        }
        return minHeap.top();ss
    }

```

