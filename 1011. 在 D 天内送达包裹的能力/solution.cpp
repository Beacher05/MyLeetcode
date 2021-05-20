class Solution {
private:
    bool cantCarry(vector<int>weights,int D,int load){
        int curDay=1,curload=0;       // 判断在运载能力确定时，能不能在D内运完。
        for(int w:weights){
            if(curload+w>load){         // 加上这件物品超载，说明当天运量到上限，需要每天发
                curload=0;  // 清空
                ++curDay;   //天数加1
            }
            curload+=w;   // 装货
        } 
        return curDay>D;   // 是不是运不完。
    }
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int  left= INT_MIN,right=0;
        for(int w:weights){
            left=max(left,w);
            right+=w;        //找出左右界
        }
        while(left<right){                // 二分查找，根据二分查找的笔记，此处找的是符合条件的最小值
            int middle=left+(right-left)/2;
            if(cantCarry(weights,D,middle)){       //运不走，移动左，使变大 
                left=middle+1;
            }
            else{                          // 运得走，移动右，使变小，逼近最小值 
                right=middle;
            }
        }
        return left;  //循环结束时，执行的是left=middle+1,处于有效区间内。 
    }
};