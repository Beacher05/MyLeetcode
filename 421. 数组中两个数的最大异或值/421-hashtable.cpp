class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int High_bit=30;            //数据在 0-2^31 用0-30 即可表示。
        int result=0;
        for(int i=High_bit;i>=0;i--){
            unordered_set<int> seen;
            for(int num:nums){
                seen.insert(num>>i);        //在每一次的哈希表与遍历中，都是使用num>>i,表示num从最高位到第i位的大小，当i为0时，即为num本身，
            }
            int x=result*2+1;         //假设当前位可以为1。
            bool find=false;

            for(int num:nums){
                if(seen.count((num>>i)^x)){           // 由于i之前的几位已处理过，这步可看作前几位为当前最大的几对中，当前有没有可以取1的。
                    find=true;
                    break;
                }
            }
            if(find){          //更新，准备下一位计算
                result=x;        //有，保持
            }else{
                result=x-1;    //没有， -1
            }
        }
        return result;
    }
};