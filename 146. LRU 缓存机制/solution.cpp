struct DlinkedNode{
    DlinkedNode* pre;
    DlinkedNode* next;
    int key;
    int val;
    DlinkedNode():pre(nullptr),next(nullptr),key(0),val(0){};
    DlinkedNode(int _key,int _val):pre(nullptr),next(nullptr),key(_key),val(_val){};
};  //自定义的双向链表，其中的数据为键和值。
class LRUCache {
private:
    map<int,DlinkedNode*> cache;   // 用于记录对应的键和节点的地址
    DlinkedNode* dummyH;
    DlinkedNode* dummyD;          // 虚拟的头尾节点，用来记录顺序，减少讨论
    int size;                    // 当前大小
    int capsize;                 // 设置的大小
  void moveToHead(DlinkedNode* node){
      DelNode(node);           
      addToHead(node);             // 移动到头节点，相当于删除节点再重新从头插
  }
  void addToHead(DlinkedNode* node){
      node->next=dummyH->next;          
      node->pre=dummyH;          // 先设定插入节点的前后指针，此时对链表无影响
      dummyH->next->pre=node;
      dummyH->next=node;         // 再修改原来的链表 先是前，再是后
  }
  void DelNode(DlinkedNode* node){
      node->next->pre=node->pre;
      node->pre->next=node->next;    // 直接节点前后节点的指针的指向，从而改变链表。
      //此时该节点仍然存在，没有被析构，依然存在哈希表中，只是不在链表里了。
  }
  DlinkedNode* removeTail(){
      DlinkedNode* tmp=dummyD->pre;
      DelNode(tmp);
      return tmp;          // 从尾移除，说明要完全析构
  }
public:
    LRUCache(int capacity) :capsize(capacity),size(0){
        dummyH=new DlinkedNode();
        dummyD=new DlinkedNode();
        dummyH->next=dummyD;
        dummyD->next=dummyH;   // 容量，头尾指针初始化
    }
    int get(int key) {
        if(cache.count(key)==0)
          return -1;            // 当前键值不存在
        else{
         DlinkedNode* cur = cache[key];      // 从哈希表中找到对应的节点
        moveToHead(cache[key]);             // 移到头
        return cache[key]->val;            // 返回值
          }
    }
    
    void put(int key, int value) {
        if(cache.count(key)==0){           // 新的键
             DlinkedNode* cur = new DlinkedNode(key,value);
             cache[key]=cur;
             addToHead(cur);             //头插
             size++;
             if(size>capsize){             // 超出最大容量，析构尾端的节点
            DlinkedNode* ToDel = removeTail();
            cache.erase(ToDel->key);
            delete ToDel;
            size--;
            }
        }
        else{
            DlinkedNode* cur = cache[key];   // 旧的键，更新值
            cur->val=value;
            moveToHead(cur);            // 移到头
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */