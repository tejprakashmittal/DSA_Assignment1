#include<iostream>
using namespace std;
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
int main(){
     string str1="521436512436",str2="563217895";
     cout<<sub(str1,str2);
}