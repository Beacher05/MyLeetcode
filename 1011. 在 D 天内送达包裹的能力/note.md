#### [1011. 在 D 天内送达包裹的能力]

#### (https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/)

传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。

传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。

返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。

 

按照题目要求，需要的结果是能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。求的是运载能力。

那么，可以先想出在忽略天数的情况下考虑运载能力的范围。首先最小运载能力应该大于物品的最大值，才有可能完成任务，最大运载能力应为物品重量的总和，这样就可以一天运走，再大没有必要。

之后使用二分查找，计算当前运载量运输所需要的最小天数，不断的逼近D,得解。详细见代码。

```cpp
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
```



 