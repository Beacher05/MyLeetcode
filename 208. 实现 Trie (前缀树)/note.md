#### 208. 实现 Trie (前缀树)

#### https://leetcode-cn.com/problems/implement-trie-prefix-tree/

Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。



依题意可知，前缀树的每个节点应该有一个大小为26的数组，来存放26个作为子树的下一个字母，为了减少对26个子树是否为空的判断，最好在节点中加入一个标识来标识最后一个字母。

同时，为了将26个字母开头的树联合为一棵树而不是森林，应将根节点置空（各类前缀树都应如此）。

前缀树的基本逻辑是：将字符串拆为各个字符，在创建或寻找指定字符串时，用这一个一个的字符由浅到深的创建或进入对应字符的子树。



```cpp
class Trie {
private:
 vector<Trie*> children;       //一个字典树的节点应该有对应的26个字母的子树
 bool isEnd;                   // 表示为最后一个节点
 Trie* searchWithPre(string word){             // 将搜索的公共部分提取出来，返回指定字符串的最后的字符的节点地址
      Trie* cur=this;
        for(char ch:word){
            int index=ch-'a';   //
            if(cur->children[index]==nullptr)
                return nullptr;
            cur=cur->children[index];
        }
        return cur;
 }
public:
    /** Initialize your data structure here. */
    Trie():children(26),isEnd(false) {      // 节点初始化方式

    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {          
        Trie* cur=this;
        for(char ch:word){
            int index=ch-'a';
            if(cur->children[index]==nullptr)
                cur->children[index]=new Trie();
            cur=cur->children[index];
        }
        cur->isEnd=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* node = searchWithPre(word);
        return node!=nullptr&&node->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return searchWithPre(prefix)!=nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

