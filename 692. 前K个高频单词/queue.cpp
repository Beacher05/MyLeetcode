class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> cnt;
        for (auto& word : words) {
            cnt[word]++;                 //统计出现次数
        }
        auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;  //自定义比较方式，使得队头是出现次数最少的
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> que(cmp);  //声明队列
        for (auto& it : cnt) {
            que.emplace(it);
            if (que.size() > k) {   // 只需记录前K个
                que.pop();
            }
        }
        vector<string> ret(k);
        for (int i = k - 1; i >= 0; i--) {
            ret[i] = que.top().first;     // 从头逆序输出结果到vector中
            que.pop();
        }
        return ret;
    }
};