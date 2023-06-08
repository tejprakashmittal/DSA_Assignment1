#include<iostream>
#include<sstream>
using namespace std;

int calculate(string s) {
        stringstream ss("+" + s);
        char op;
        int n, last, ans = 0;
        while (ss >> op >> n) {
            cout<<n<<" ";
            if (op == '+' || op == '-') {
                n = op == '+' ? n : -n;
                ans += n;
            } else {
                n = op == '*' ? last * n : last / n;
                ans = ans - last + n; // simulate a stack by recovering last values
            }
            last = n;
        }
        return ans;
}
 int main(){
   cout<<calculate("2+32*5-6");
 }