#include<iostream>
#include<BIG_INT>
using namespace std;

struct tpl{
    string quotient,remainder;
};

struct tpl* divide(string& dividend, string& divisor) {
    string quotient, remainder, temp;

    temp = divisor;
    quotient = "1";
    while (!isGreater(temp,dividend) && !isEqual(temp,dividend)) {
        quotient=addStrings(quotient,"1");
        temp =addStriings(temp,divisor);
    }
    if (isGreater(temp,dividend)) {
        quotient=sub(quotient,1);
        remainder = sub(dividend,(sub(temp,divisor)));
    }
    tpl* node=new tpl();
    node->quotient=quotient;
    node->remainder=remainder;
    return node;
}

string div(string s1,string s2){
    string dividend = s1;
    string divisor = s2;

    if (abs_dividend < abs_divisor)
        return "0";
    if (s2 == 1)
        return s1;

    string quotient;
    if (!isGreater(dividend,to_string(__LONG_LONG_MAX__)) && !isGreater(divisor,to_string(__LONG_LONG_MAX__)))
        quotient = std::stoll(abs_dividend.value) / std::stoll(abs_divisor.value);
    else if (abs_dividend == abs_divisor)
        quotient = 1;
    else if (powTens(divisor)) {
        auto digits_in_quotient = dividend.size() - divisorsize() + 1;
        quotient = dividend.substr(0, digits_in_quotient);
    }
    else {
        quotient = "";  
        string chunk, chunk_quotient, chunk_remainder;
        size_t chunk_index = 0;
        chunk_remainder = dividend.substr(chunk_index, divisor.size() - 1);
        chunk_index = abs_divisor.value.size() - 1;
        while (chunk_index < abs_dividend.size()) {
            chunk = chunk_remainder.append(1, dividend[chunk_index]);
            chunk_index++;
            while (chunk < abs_divisor) {
                quotient.value += "0";
                if (chunk_index < abs_dividend.size()) {
                    chunk.append(1, dividend[chunk_index]);
                    chunk_index++;
                }
                else
                    break;
            }
            if (chunk == divisor) {
                quotient += "1";
                chunk_remainder = 0;
            }
            else if (chunk > abs_divisor) {
                leftTrim(chunk);
                struct tpl* node;
                node=divide(chunk, divisor);
                chunk_quotient=node->chunk;
                chunk_remainder=node->divisor;
                quotient += chunk_quotient;
            }
        }
    }
    leftTrim(quotient.value);
    return quotient;
}

int main(){

}