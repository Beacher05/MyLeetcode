class Solution {
private:
    bool CantEat(vector<int>& piles,int h,int k){
        int time=0;
        for(int banana:piles)
            time+=(banana-1)/k+1;    //计算出吃完当前堆的天数
        return time>h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left=1,right=*max_element(piles.begin(), piles.end());   //确定上下界
        while(left<right){ //二分查找，找符合条件的最小值
            int mid=left+(right-left)/2;
            if(CantEat(piles,h,mid))   //吃不完，移动左，使变大
              left=mid+1;
            else                 //吃得完，移动右，使变小，逼近最小
              right=mid;
        }
        return left;   //循环结束时，执行的是left=middle+1,处于有效区间内。 
    }
};