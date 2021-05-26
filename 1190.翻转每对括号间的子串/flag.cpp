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