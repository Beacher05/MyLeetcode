class Trie {
private:
 vector<Trie*> children;       //一个字典树的节点应该有对应的26个字母的子树
 bool isEnd;                   // 表示为最后一个节点
 Trie* searchWithPre(string word){             // 将搜索的公共部分提取出来，返回指定字符串的最后的字符的节点地址
      Trie* cur=this;
        for(char ch:word){
            int index=ch-'a';
            if(cur->children[index]==nullptr)       // 没有找到对应的子树，说明找不到，返回空
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
            int index=ch-'a';      //计算对应子树的索引
            if(cur->children[index]==nullptr)    // 没有则创建
                cur->children[index]=new Trie();
            cur=cur->children[index];   // 进入对应子树
        }
        cur->isEnd=true;    //坐标记
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