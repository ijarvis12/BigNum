#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const unsigned long int WORD_SIZE = 1000000000;
const char WORD_LEN = 9;

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
  this->resize(0);
  if(num.length() > (WORD_LEN*2 - 1)){
    for(unsigned long int i=num.length()-WORD_LEN; i>(WORD_LEN-1); i-=WORD_LEN){
      this->push_back(stol(num.substr(i,WORD_LEN)));
    }
    char mod = (num.length() % WORD_LEN);
    if(mod != 0){
      this->push_back(stol(num.substr(0,mod)));
    }
    else{
      this->push_back(stol(num.substr(0,WORD_LEN)));
    }
  }
  else{
    this->push_back(stol(num));
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
        for(char j=WORD_LEN; j>x_len; j--){
          x = "0" + x;
        }
        os << x;
      }
      x = to_string(a.getDigit(0));
      x_len = x.length();
      for(char j=WORD_LEN; j>x_len; j--){
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
          addition.setDigit(j+1,addition.getDigit(j+1)+1);
        }
      }
      if(addition.getDigit(j+1) < WORD_SIZE){
        break;
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
      if(subtract.getDigit(j+1) > -1){
        break;
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
  BigNum division = BigNum();
  division.resize(this->size());
  double b,c,carry = 0;
  for(unsigned long int i=this->size()-1; i>0; i--){
    b = this->getDigit(i)/(a.getDigit(i)+a.getDigit(i)*carry);
    carry = modf(b,&c);
    division.setDigit(i,c);
    carry *= WORD_SIZE;
  }
  b = this->getDigit(0)/(a.getDigit(0)+a.getDigit(0)*carry);
  carry = modf(b,&c);
  division.setDigit(0,c);
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
