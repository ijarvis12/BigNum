#include <iostream>
#include "bignum.h"
using namespace std;

int main(){
  //Initializer Tests
  BigNum i1 = BigNum();
  cout << i1 << endl;

  BigNum i2 = BigNum("1010101010");
  cout << i2 << endl;

  BigNum i3 = BigNum(1000000100);
  cout << i3 << endl;

  cout << endl;

  //Operator Tests
  BigNum t1 = BigNum("999999999") + BigNum("1");
  cout << t1 << endl;

  BigNum t2 = BigNum("100000000") - BigNum("99999999");
  cout << t2 << endl;

  BigNum t3 = BigNum("999999999") * BigNum("333");
  cout << t3 << endl;

  BigNum t4 = pow(BigNum("2"),30);
  cout << t4 << endl;

  BigNum t5 = BigNum("999999999") / BigNum("333");
  cout << t5 << endl;

  BigNum t6 = BigNum("999999999") % BigNum("333");
  cout << t6 << endl;

  return 0;
}
ijarvis12@penguin:~$ cat bignum.h
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const unsigned long int WORD_SIZE = 100000000;

class BigNum{
  private:
    vector<long int> digits;
  public:
    //Constructors
    BigNum();
    BigNum(const string& num);
    BigNum(const unsigned long int num);
    //Deconstructor
    ~BigNum();
    //Setter
    void setDigit(const unsigned long int digit, const long int x);
    //Getter
    long int getDigit(const unsigned long int digit) const;
    //Vector API
    unsigned long int size() const;
    void resize(const unsigned long int x);
    void push_back(const long int x);
    void pop_back();
    long int back() const;
    //Operators
    BigNum operator =(const BigNum& a);
    BigNum operator +(const BigNum& a);
    BigNum operator -(const BigNum& a);
    BigNum operator *(const BigNum& a);
    BigNum operator /(const BigNum& a);
    BigNum operator %(const BigNum& a);
};

//Constructors
BigNum::BigNum(){
  this->resize(0);
};

BigNum::BigNum(const string& num){
  if(num.length() > 15){
    for(unsigned long int i=num.length()-8; i>7; i-=8){
      this->push_back(stoi(num.substr(i,8)));
    }
    char mod = (num.length() % 8);
    if(mod != 0){
      this->push_back(stoi(num.substr(0,mod)));
    }
    else{
      this->push_back(stoi(num.substr(0,8)));
    }
  }
  else{
    this->push_back(stoi(num));
  }
};

BigNum::BigNum(const unsigned long int num){
  string x = to_string(num);
  *this = BigNum(x);
};

//Deconstructor
BigNum::~BigNum(){
  this->digits.clear();
};

//Setter
void BigNum::setDigit(const unsigned long int digit, const long int x){
  this->digits[digit] = x;
};

//Getter
long int BigNum::getDigit(const unsigned long int digit) const {
  return this->digits[digit];
};

//Vector API
unsigned long int BigNum::size() const {
  return this->digits.size();
};

void BigNum::resize(const unsigned long int x){
  this->digits.resize(x);
};

void BigNum::push_back(const long int x){
  this->digits.push_back(x);
};

void BigNum::pop_back(){
  this->digits.pop_back();
};

long int BigNum::back() const {
  return this->digits.back();
};

//Operators
ostream& operator <<(ostream& os, const BigNum& a){
  if(a.size() > 0){
    if(a.size() > 1){
      os << a.back();
      string x = "";
      char x_len = 0;
      for(unsigned long int i=a.size()-2; i>0; i--){
        x = to_string(a.getDigit(i));
        x_len = x.length();
        for(char j=8; j>x_len; j--){
          x = "0" + x;
        }
        os << x;
      }
      x = to_string(a.getDigit(0));
      x_len = x.length();
      for(char j=8; j>x_len; j--){
        x = "0" + x;
      }
      os << x;
    }
    else{
      os << a.getDigit(0);
    }
  }
  else{
    os << "err:size 0";
  }
  return os;
};

BigNum BigNum::operator =(const BigNum& a){
  this->resize(a.size());
  for(unsigned long int i=0; i<a.size(); i++){
    this->setDigit(i,a.getDigit(i));
  }
  return *this;
};

BigNum BigNum::operator +(const BigNum& a){
  BigNum addition = *this;
  for(unsigned long int i=0; i<a.size(); i++){
    if(i > addition.size()-1){
      addition.push_back(0);
    }
    addition.setDigit(i,addition.getDigit(i)+a.getDigit(i));
    for(unsigned long int j=i; j<addition.size(); j++){
      while(addition.getDigit(j) > (WORD_SIZE - 1)){
        addition.setDigit(j,addition.getDigit(j)-WORD_SIZE);
        if(j+1 > addition.size()-1){
          addition.push_back(1);
        }
        else{
          addition.setDigit(i+1,addition.getDigit(i+1)+1);
        }
      }
    }
  }
  return addition;
};

// Can only do subtraction that ends with a positive number, for now
BigNum BigNum::operator -(const BigNum& a){
  if(this->size() < a.size()){
    return BigNum("0");
  }
  else if(this->size() == a.size() && this->back() < a.back()){
    return BigNum("0");
  }
  BigNum subtract = *this;
  for(unsigned long int i=0; i<a.size(); i++){
    subtract.setDigit(i,subtract.getDigit(i)-a.getDigit(i));
    for(unsigned long int j=i; j<subtract.size()-1; j++){
      while(subtract.getDigit(j) < 0){
        subtract.setDigit(j,subtract.getDigit(j)+WORD_SIZE);
        subtract.setDigit(j+1,subtract.getDigit(j+1)-1);
      }
    }
  }
  while(subtract.back() == 0){
    subtract.pop_back();
  }
  return subtract;
};

// Use long multiplcation
//https://en.wikipedia.org/wiki/Multiplication_algorithm
BigNum BigNum::operator *(const BigNum& a){
  if(a.back() == 0){
    return BigNum("0");
  }
  else if(this->back() == 0){
    return BigNum("0");
  }
  else if(a.size() == 1 && a.getDigit(0) == 1){
    return *this;
  }
  else if(this->size() == 1 && this->getDigit(0) == 1){
    return a;
  }
  BigNum product = BigNum();
  product.resize(this->size()+a.size());
  unsigned long int carry;
  for(unsigned long int b_i=0; b_i<a.size(); b_i++){
    carry = 0;
    for(unsigned long int a_i=0; a_i<this->size(); a_i++){
      product.setDigit(a_i+b_i,product.getDigit(a_i+b_i)+carry+this->getDigit(a_i)*a.getDigit(b_i));
      carry = (unsigned long int)(product.getDigit(a_i+b_i) / WORD_SIZE);
      product.setDigit(a_i+b_i,product.getDigit(a_i+b_i)%WORD_SIZE);
    }
    product.setDigit(b_i+this->size(),carry);
  }
  while(product.back() == 0){
    product.pop_back();
  }
  return product;
};

//BigNum a must be smaller
BigNum BigNum::operator /(const BigNum&  a){
  if(a.back() == 0){
    return BigNum();
  }
  else if(this->back() == 0){
    return BigNum("0");
  }
  else if(a.size() == 1 && a.getDigit(0) == 1){
    return *this;
  }
  else if(a.size() > this->size()){
    return BigNum("0");
  }
  else if(a.size() == this->size() && a.back() > this->back()){
    return BigNum("0");
  }
  BigNum division = BigNum("0");
  BigNum c = *this;
  while(c.size() >= a.size()){
    if(c.size() == a.size() && c.back() < a.back()){
      break;
    }
    c = c - a;
    division = division + BigNum("1");
  }
  return division;
};

// BigNum a must be smaller
BigNum BigNum::operator %(const BigNum& a){
  BigNum b = a;
  BigNum c = (*this / a);
  BigNum d = (b - c);
  return d;
};

// Can only exponentiate postive integers
BigNum pow(const BigNum& a, unsigned long int n){
  if(n == 0){
    return BigNum("1");
  }
  BigNum x = a;
  BigNum y = BigNum("1");
  while(n > 1){
    if(n % 2 == 0){
      x = x * x;
      n /= 2;
    }
    else{
      y = x * y;
      x = x * x;
      n = (unsigned long int)((n - 1) / 2);
    }
  }
  return x * y;
};
