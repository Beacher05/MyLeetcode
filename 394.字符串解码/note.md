#### [394. 字符串解码]

#### [(https://leetcode-cn.com/problems/decode-string/)

这道题经典的括号匹配问题，就是用栈来保存外层的内容，当退出内层时与栈顶进行处理，变为新的内层，详细看代码。

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<int> snum;     //数字栈，用于存储内层字符串的个数
        stack<string> sstr;  //字符串栈，存储外层字符串
        string res="";      //初始化
        int num=0,n=s.size();
        for(int i=0;i<n;++i){
            if(s[i]<='9'&&s[i]>='0'){          //记录数字，注意数字有可能>9,所以要这么去
                 num=num*10+s[i]-'0';
            }else if((s[i]<='z'&&s[i]>='a')||(s[i]<='Z'&&s[i]>='A')){       // 记录字符于字符串中
                res.push_back(s[i]);
            }else if(s[i]=='['){          // 进入内层
                snum.push(num);
                sstr.push(res);         // 记录外层信息
                res="";
                num=0;                // 复位信息
            }else if(s[i]==']'){          // 离开内层
                int time =snum.top();
                string temp=sstr.top();    // 对应的操作
                while(time--){
                    temp.append(res);
                }
                res=temp;
                snum.pop();sstr.pop();     //弹出该层的信息
            }
        }
        return res;          // 返回结果
    }
};
```

