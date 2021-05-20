#### 692. 前K个高频单词

#### https://leetcode-cn.com/problems/top-k-frequent-words/

## 方法1：哈希表

这道题的第一反应是使用一个哈希表记录各个单词出现的次数，之后再根据这个进行排序，排序完再剪切出前k个，即为结果。

详细见代码注释

```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string,int> smap;   
        for(string str:words){
            smap[str]++;
        }      //统计各单词出现次数
        vector<string> res;
        for(pair<string,int>p:smap)  {
            res.emplace_back(p.first);
        }     // 使用生成的map而不是原来的vector是为了去重
        sort(res.begin(),res.end(),
        [&](string &a,string &b)->bool{return smap[a]==smap[b]?a<b:smap[a]>smap[b];}
        );// 使用lamda来自定义排序规则，出现次数相同的按字典序排，不同的次数大的在前，[&]表示传引用，用到了smap。 
        res.resize(k);   //裁剪
        return res;
    }
};
```

时间复杂度：O(l \times n + l \times m \log m)O(l×n+l×mlogm)，其中 nn 表示给定字符串序列的长度，ll 表示字符串的平均长度，mm 表示实际字符串种类数。我们需要 l \times nl×n 的时间将字符串插入到哈希表中，以及 l \times m \log ml×mlogm 的时间完成字符串比较（最坏情况下所有字符串出现频率都相同，我们需要将它们两两比较）。

空间复杂度：O(l \times m)O(l×m)，其中 ll 表示字符串的平均长度，mm 表示实际字符串种类数。哈希表和生成的排序数组空间占用均为 O(l \times m)O(l×m)。

需要复习lamda的语法。

## 方法二：优先队列

定义：priority_queue<Type, Container, Functional>
Type 就是数据类型，Container 就是容器类型（Container必须是用数组实现的容器，比如vector,deque等等，但不能用 list。STL里面默认用的是vector），Functional 就是比较的方式。

当需要用自定义的数据类型时才需要传入这三个参数，使用基本数据类型时，只需要传入数据类型，默认是大顶堆。

根据自己定义的比较方式，将字符串放进一个优先队列中，队列的前K个即为结果。（方法一是插完再排，方法二是边插边排）

```cpp
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
```

时间复杂度：O(l \times n + m \times l \log k)O(l×n+m×llogk)，其中 nn 表示给定字符串序列的长度，mm 表示实际字符串种类数，ll 表示字符串的平均长度。我们需要 l \times nl×n 的时间将字符串插入到哈希表中，以及每次插入元素到优先队列中都需要 l \log kllogk 的时间，共需要插入 mm 次。

空间复杂度：O(l \times (m + k))O(l×(m+k))，其中 ll 表示字符串的平均长度，mm 表示实际字符串种类数。哈希表空间占用为 O(l \times m)O(l×m)，优先队列空间占用为 O(l \times k)O(l×k)。

