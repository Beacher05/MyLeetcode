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