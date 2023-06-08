#include<iostream>
#include <sstream>
using namespace std;

struct tpl{
    string quot,remain;
};

long long int toLongInt(string str){
    stringstream sst(str);
    long long int x=0;
    sst>>x;
    return x;
}

bool powTens(string& str){
    if (str[0] != '1')
        return false;
    for (auto i = 1; i < str.size(); i++)
    {
        if (str[i] != '0')
            return false;
    }
    return true;
}

void leftTrim(string& str) {
    size_t i = 0;
    for (; i < str.size(); i++)
        if (str[i] != '0')
            break;

    if (i == str.size())
        str = "0";
    else
        str = str.substr(i);
}

bool isEqual(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
 
    if (n1 < n2 || n2 < n1)
        return false;
 
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return false;
        else if (str1[i] > str2[i])
            return false;
 
    return true;
}

bool isGreater(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
 
    if (n1 > n2)
        return true;
    if (n2 > n1)
        return false;
 
    for (int i = 0; i < n1; i++)
        if (str1[i] > str2[i])
            return true;
        else if (str1[i] < str2[i])
            return false;
 
    return false;
}

bool isLess(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
 
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
 
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
 
    return false;
}

string multiply(string num1, string num2) {
        if(num1=="0" || num2=="0") return "0";
        int m=num1.size(),n=num2.size();
        int res[m+n];
        for(int o=0;o<m+n;o++) res[o]=0;
        int i=m-1,j=n-1,pf=0,k=m+n-1,carry=0;
        
        for(;j>=0;j--){
            k=m+n-1;
            k-=pf++;
            for(i=m-1;i>=0;i--){
                int prod=(num2[j]-'0')*(num1[i]-'0')+carry+res[k];
                res[k--]=prod%10;
                carry=prod/10;
            }
            if(carry) res[k]=carry;
            carry=0;
        }
        if(carry) res[k]=carry;
        string str;
        int p=0;
        if(res[p]) str+=res[p]+'0';
        p++;
        for(;p<m+n;p++) {
            str+=res[p]+'0';
        }
        return str;
    }
string addStrings(string num1, string num2) {
        if(num1=="0" ||num2=="0") return max(num1,num2);
        int m=num1.size(),n=num2.size();
        int res[max(m,n)+1];
        for(int i=0;i<max(m,n)+1;i++) res[i]=0;
        int carry=0,i=m-1,j=n-1,k=max(m,n),add;
        while(i>=0 && j>=0){
            add=(num1[i]-'0')+(num2[j]-'0')+carry;
            res[k--]=add%10;
            carry=add/10;
            i--;j--;
        }
        if(i || j){
            auto x=max(i,j);
            if(x==i)
            {
                while(x>=0){
                    add=num1[x]-'0' + carry;
                    res[k--]=add%10;
                    carry=add/10;
                    x--;
                }
            }
            else{
                while(x>=0){
                    add=num2[x]-'0' + carry;
                    res[k--]=add%10;
                    carry=add/10;
                    x--;
                }
            }
        }
        if(carry)
        res[k]+=carry;
        string str;
        int p=0;
        if(!res[p]) p=1;
        for(;p<max(m,n)+1;p++) str+=res[p]+'0';
        return str;
    }
string sub(string a,string b){
    int m=a.size(),n=b.size();
    int res[max(m,n)];
    for(int i=0;i<max(m,n);i++) res[i]=0;
    int i=m-1,j=n-1,k=max(m,n)-1,borrow=0,sub,ai;
    
    while(i>=0 && j>=0){
       sub=(a[i]-'0') - (b[j]-'0') - borrow;
       if(sub<0)
       {
          sub+=10;
          borrow=1;
       }
       else borrow=0;
       res[k]=sub;
       i--;j--;k--;
    }
    while(i>=0)
    {
      sub=(a[i]-'0')-borrow;
      if(sub<0){
          borrow=1;
          sub+=10;
      }
      else
      borrow=0;
      res[k]=sub;
      i--;k--;
    }
    string str;
    int p=0;
    while(!res[p]) p++;
    for(;p<max(m,n);p++) str+=res[p]+'0';
    if(str.size()==0) str+='0';
    return str;
}
string div(string s1,string s2){
    string count="0";
    while(isGreater(s1,s2)){
        s1=sub(s1,s2);
        count=addStrings(count,"1");
    }
    if(isEqual(s1,s2)) count=addStrings(count,"1");
    return count;
}

string fact(string str){ 
   string sum=str;
   while(!(isEqual(str,"1"))){
       str=sub(str,"1");
       sum=multiply(sum,str);
   }
   return sum;
}

string expo(string base,string exp){
    long long ex=0;
    string res="1";
    stringstream sst(exp);
    sst>>ex;
    for(long long int i=0;i<ex;i++){
         res=multiply(res,base);
    }
  return res;
}

string gcd(string a,string b){
    if(isEqual(a,b)) return a;

   string max,min;
   if(isGreater(a,b)) {max=a;min=b;}
   else {
       max=b;min=a;
   }

   while(!(isEqual(max,"0")) && !(isEqual(min,"0"))){
       max=sub(max,min);
       if(isGreater(min,max)){
          string temp;
          temp=min;
          min=max;
          max=temp;
       } 
   }
   if(isGreater(max,min)) return max;
  return min;
}

struct tpl* divide(string& divide, string& diviso) {
    string rem, quo, temp;

    temp = diviso;quo = "1";
    while (!isGreater(temp,divide) && !isEqual(temp,divide)) {
        quo=addStrings(quo,"1");
        temp =addStrings(temp,diviso);
    }
    if (isGreater(temp,divide)) {
        quo=sub(quo,"1");
        rem = sub(divide,(sub(temp,diviso)));
    }
    tpl* node=new tpl();
    node->quot=quo;
    node->remain=rem;
    return node;
}

string div1(string s1,string s2){
    string dividend = s1, divisor = s2;

    if (!isGreater(dividend,divisor) && !isEqual(dividend,divisor))
        return "0";
    if (isEqual(s2,"1"))
        return s1;

    string quot;
    if (!isGreater(dividend,to_string(__LONG_LONG_MAX__)) && !isGreater(divisor,to_string(__LONG_LONG_MAX__)))
        quot = to_string(toLongInt(dividend) / toLongInt(divisor));
    else if (isEqual(dividend,divisor))
        quot = 1;
    else if (powTens(divisor)) {
        auto dig_quot = dividend.size() - divisor.size() + 1;
        quot = dividend.substr(0, dig_quot);
    }
    else {
        string cq,c, cr;
        quot = "";  
        size_t ci = 0;
        cr = dividend.substr(ci, divisor.size() - 1);
        ci = divisor.size() - 1;
        while (ci < dividend.size()) {
            c = cr.append(1, dividend[ci]);
            ci++;
            while (isLess(c,divisor)) {
                quot += "0";
                if (ci < dividend.size()) {
                    c.append(1, dividend[ci]);
                    ci++;
                }
                else
                    break;
            }
            if (c == divisor) {
                cr = "0";
                quot += "1";
            }
            else if (isGreater(c,divisor)) {
                leftTrim(c);
                struct tpl* node;
                node=divide(c, divisor);
                cq=node->quot;
                cr=node->remain;
                quot += cq;
            }
        }
    }
    leftTrim(quot);
    return quot;
}


string mod(string s1,string s2){
    string divid = s1, divis = s2;     //for dividend  and for divisor

    if (divis == "1" or divis == divid)
        return "0";

    string remain;
    if (!isGreater(divid,to_string(__LONG_LONG_MAX__)) && !isGreater(divis,to_string(__LONG_LONG_MAX__)))
        remain = to_string(toLongInt(divid) % toLongInt(divis));
    else if (!isGreater(divid,divis) && !isEqual(divid,divis))
        remain = divid;
    else if (powTens(s2)){ 
        size_t nozs = s2.size() - 1;
        remain= divid.substr(divid.size() - nozs);
    } 
    else {
        string quot = div1(divid,divis);
        remain =sub(divid , multiply(quot,divis));
    }
    leftTrim(remain);
    return remain;
}

string gcd1(string no1, string no2){

    if (no1 == "0")
        return no2; 

    if (no2 == "0")
        return no1;  

    string rem = no2;
    while (rem != "0") {
        rem = mod(no1,no2);
        no1 = no2;   
        no2 = rem;  
    }

    return no1;
}

// STack implementation for char input
struct stNode
{
    char data;
    struct stNode* link;
};
 
struct stNode* top;
void push(char data)
{
    struct stNode* temp;
    temp = new stNode();
    temp->data = data;
    temp->link = top;
    top = temp;
}

int isEmpty()
{
    return (top == NULL);
}

char peek()
{
    if (!isEmpty())
        return top->data;
    else
        return -1;
}
 
void pop()
{
    struct stNode* temp;

    if (top != NULL)
    {
        temp = top;
        top = top->link;
        temp->link = NULL;
    }
}

//stack implementation for string input
struct stackNode
{
    string data;
    struct stackNode* link;
};
 
struct stackNode* top2;
void push2(string data)
{
    struct stackNode* temp;
    temp = new stackNode();
    temp->data = data;
    temp->link = top2;
    top2 = temp;
}

int isEmpty2()
{
    return (top2 == NULL);
}

string peek2()
{
    if (!isEmpty2())
        return top2->data;
    else
        return "error";
}
 
void pop2()
{
    struct stackNode* temp;
    if(top2 != NULL)
    {
        temp = top2;
        top2 = top2->link;
        temp->link = NULL;
    }
}

string evaluate(string s){
    //cout<<s;
    string str="";
    int i=0;
    for(;i<s.size();i++){
        if(!isdigit(s[i])){
           if(str!="") {
               //cout<<str<<" ";
               push2(str);
               //cout<<peek2()<<" ";
               str="";
           }
          if(s[i]==' ') continue;
          string x="",y="";
          if(!isEmpty2()){
              y=peek2();
              pop2();
          }
          if(!isEmpty2()){
              x=peek2();
              pop2();
          }
          //cout<<x<<" "<<y<<endl;
          if(s[i]=='*') push2(multiply(x,y));
          else if(s[i]=='/') push2(div1(x,y));
          else if(s[i]=='+') push2(addStrings(x,y));
          else if(s[i]=='-') push2(sub(x,y));
        }
        else str+=s[i];
    }
    //cout<<stk.size()<<endl;
    if(isEmpty2()) return str;
    return peek2();
}

string postfix(string s){
    int arr[256]={0};
    arr['*']=2;arr['/']=2;arr['+']=1;arr['-']=1;
    string str="";
    int i=0;
    for(;i<s.size();i++){
        if(s[i]=='x') s[i]='*';
        if(!isdigit(s[i])){
            if(s[i]==' ') continue;
            str+=' ';
            if(isEmpty()) push(s[i]);
            else{
                while(!isEmpty() && arr[s[i]] <= arr[peek()]){
                    str+=peek();
                    pop();
                }
                push(s[i]);
            }
        }
        else{
            str+=s[i];
        }
    }
    while(!isEmpty()){
        str+=peek();
        pop();
    }
    return str;
}

string calc(string s) {
        string str=postfix(s);
        //cout<<str;
        return evaluate(str);
}

int main(){
    //cout<<addStrings(multiply("99893271223","9203232392"),sub("32789123","4874223"));
    int type;
    cin>>type;
    if(type==1){
        string s1,s2;
        cin>>s1>>s2;
        cout<<expo(s1,s2)<<endl;
    }
    else if(type==2){
        string s1,s2;
        cin>>s1>>s2;
        cout<<gcd1(s1,s2)<<endl;
    }
    else if(type ==3){
        string s1;
        cin>>s1;
        cout<<fact(s1)<<endl;
    }
    else if(type==4){
        string s1;
        cin>>s1;
        cout<<calc(s1)<<endl;
    }
   /* switch(type){
        case 1 : cout<<expo("2","10000").size();break;
        case 2 : cout<<gcd1("12","8");break;
        case 3 : cout<<(div1(fact("1152"),fact("1151")));break;
        case 4 : cout<<calc("99893271223x9203232392+32789123-4874223");break;
        case 5 : cout<<div1("897987637959735253748949473","978");break;
        case 6 :cout<<mod("50","11");break;
    }*/
}