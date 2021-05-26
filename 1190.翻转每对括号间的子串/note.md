#### [1190. 反转每对括号间的子串]

#### [(https://leetcode-cn.com/problems/reverse-substrings-between-each-pair-of-parentheses/)

符号匹配的问题是栈的强项，因此自然而然的就想起用一个字符串栈来保存当前的括号对之前的字符串的内容，详细看代码注释。

## 方法1、栈

```cpp
class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> stk;        //字符串栈用于保存当前的括号对之前的字符串的内容
        string res;
        for(char ch:s){
            if(ch=='('){
                stk.push(res);   //进入新的一层，将旧的一层保存到栈中 
                res="";
            }else if(ch==')'){     // 本层结束，进行相应操作
                reverse(res.begin(),res.end());   // 翻转本层
                res=stk.top()+res;                // 与上层拼接
                stk.pop();                      // 拼接完上层，弹出上层内容
            }else{
                res.push_back(ch);        // 普通字符则构成本层的子串
            }
        }
        return res;             // 最外一层即为结果
    }
};

```

这个属于符号匹配的通用解法，即使用栈来保存嵌套外层的信息，在内层结束后，从栈顶取出外传的信息。进行对应操作，形成新的内层，以此类推，直到栈空。

时间复杂度：O(n^2); 

空间复杂度： O(n);

## 方法2：标记法

注意到字符串的操作是翻转，那么可以通过改变遍历的顺序。来生成新的字符串。观察到，当遇到一个括号时，可以从与之匹配的括号开始，反方向遍历，直到遇到另一个括号或者到末尾。

```cpp
class Solution {
public:
    string reverseParentheses(string s) {
        int n=s.size();
        stack<int> stk;    //用一个栈来辅助记录匹配的括号
        vector<int> kh(n);  //记录匹配的括号和其下标，也可以用 map<int,int> kh;
        for(int i=0;i<n;i++){
            if(s[i]=='('){
                stk.push(i);
            }else if(s[i]==')'){
                kh[i]=stk.top();            
                kh[stk.top()]=i;
                stk.pop();
            }
        }
        string res=""; //结果初始化为空
        int step=1,index=0;  //从0开始，向右遍历
        while(index<n){
            if(s[index]=='('||s[index]==')'){   //遇到括号跳，换向
                index=kh[index];
                step=-step;
            }else{
                res.push_back(s[index]);    // 收集结果
            }
            index+=step;    //移动
        }
        return res;   //返回结果
    }
};
```

时间复杂度：O(n); 

空间复杂度： O(n);