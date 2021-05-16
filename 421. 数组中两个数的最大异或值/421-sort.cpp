class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        sort(nums.begin(), nums.end());      //排序
        int n = nums.size();
        long long maxValue = 0;
        for (int i = n -1; i >= 1; i--) {
            for (int j = i -1; j >= 0; j--) {
                if ((long long)(nums[i]) + nums[j] < maxValue) {             //剪枝操作
                    break;
                }
                maxValue = max(maxValue, (long long)(nums[i] ^ nums[j]));
            }
        }
        return maxValue;

    }
};