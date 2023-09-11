#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const unsigned long int WORD_SIZE = 1000000000;
const char WORD_LEN = 9;

class BigNum{
  private:
    bool sign; // true (1) = negative, false (0) = postitive
    vector<long int> digits;
  public:
    //Constructors
    BigNum();
    BigNum(const string& num);
    BigNum(const long int num);
    //Deconstructor
    ~BigNum();
    //Setters
    void setSign(const bool b);
    void setDigit(const unsigned long int digit, const long int x);
    //Getters
    bool getSign() const;
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
  this->sign = false;
  this->resize(0);
};

BigNum::BigNum(const string& strnum){
  this->resize(0);
  string num = "";
  if(strnum.substr(0,1).compare("-") == 0){
    this->sign = true;
    strnum.copy(num,strnum.length()-1,1);
  }
  else {
    this->sign = false;
    strnum.copy(num,strnum.length(),0);
  }
  if(num.length() > WORD_LEN){
    for(long int i=num.length()-WORD_LEN; i>0; i-=WORD_LEN){
      this->push_back(stoi(num.substr(i,WORD_LEN)));
    }
    char mod = (num.length() % WORD_LEN);
    if(mod != 0){
      this->push_back(stoi(num.substr(0,mod)));
    }
    else{
      this->push_back(stoi(num.substr(0,WORD_LEN)));
    }
  }
  else{
    this->push_back(stoi(num));
  }
};

BigNum::BigNum(const long int num){
  string x = to_string(num);
  *this = BigNum(x);
};

//Deconstructor
BigNum::~BigNum(){
  this->sign = false;
  this->digits.clear();
};

//Setters
void BigNum::setSign(const bool b){
  this->sign = b;
}

void BigNum::setDigit(const unsigned long int digit, const long int x){
  this->digits[digit] = x;
};

//Getters
bool BigNum::getSign() const {
  return this->sign;
}

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
  if(a.getSign()) os << "-";
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

bool operator <(const BigNum& a, const BigNum b){
  if( (!a.getSign() && !b.getSign()) || (a.getSign() && b.getSign()) ){
    if(b.size() < a.size()) return false;
    else if(b.size() == a.size() && b.back() <= a.back()) return false;
    else return true;
  }
  else if(!a.getSign() && b.getSign()) return false;
  else return true;
}

bool operator >(const BigNum& a, const BigNum b){
  return !(a < b);
}

BigNum BigNum::operator =(const BigNum& a){
  this->sign = a.getSign();
  this->resize(a.size());
  for(unsigned long int i=0; i<a.size(); i++){
    this->setDigit(i,a.getDigit(i));
  }
  return *this;
};

BigNum BigNum::operator +(const BigNum& a){
  if(this->getSign() && !a.getSign() && *this > a){
    this->setSign(false);
    BigNum addtion = *this - a;
    addition.setSign(true);
    return addtion;
  }
  else if(this->getSign() && !a.getSign() && *this < a){
    this->setSign(false);
    return a - *this;
  }
  else if(this->getSign() && !a.getSign()) return BigNum("0");
  else if(!this->getSign() && a.getSign() && *this > a){
    a.setSign(false);
    return *this - a;
  }
  else if(!this->getSign() && a.getSign() && *this < a){
    a.setSign(false);
    BigNum addition = a - *this;
    addition.setSign(true);
    return addtion;
  }
  else if(!this->getSign() && a.getSign()) return BigNum("0");
  else if(this->getSign() && a.getSign()){
    this->setSign(false);
    a.setSign(false);
    BigNum addition = *this + a;
    addition.setSign(true);
    return addtion;
  }
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

BigNum BigNum::operator -(const BigNum& a){
  if(this->getSign() && !a.getSign() && *this > a){
    this->setSign(false);
    BigNum subtract = *this - a;
    subtract.setSign(true);
    return subtract;
  }
  else if(this->getSign() && !a.getSign() && *this < a){
    this->setSign(false);
    BigNum subtract = a - *this;
    return subtract;
  }
  else if(this->getSign() && !a.getSign()) return BigNum("0");
  else if(!this->getSign() && a.getSign()){
    a.setSign(false);
    return *this + a;
  }
  else if(this->getSign() && a.getSign()){
    BigNum subtract = a;
    return subtract - *this;
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
  while(subtract.back() == 0 && subtract.size() > 1){
    subtract.pop_back();
  }
  return subtract;
};

// Use long multiplcation
//https://en.wikipedia.org/wiki/Multiplication_algorithm
BigNum BigNum::operator *(const BigNum& a){
  if(a.back() == 0) return BigNum("0");
  else if(this->back() == 0) return BigNum("0");
  else if(a.size() == 1 && a.getDigit(0) == 1 && !a.getSign()) return *this;
  else if(a.size() == 1 && a.getDigit(0) == 1 && a.getSign()){
    this->setSign(true);
    return *this;
  }
  else if(this->size() == 1 && this->getDigit(0) == 1 && !this->getSign()) return a;
  else if(this->size() == 1 && this->getDigit(0) == 1 && this->getSign()){
    a.setSign(true);
    return a;
  }
  else if(this->getSign() && a.getSign()){
    this->setSign(false);
    a.setSign(false);
    return *this * a;
  }
  else if(this->getSign() && !a.getSign()){
    this->setSign(false);
    BigNum product = *this * a;
    product.setSign(true);
    return product;
  }
  else if(!this->getSign() && a.getSign()){
    a.setSign(false);
    BigNum product = *this * a;
    product.setSign(true);
    return product;
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

//BigNum a must be smaller and a.size() == 1
BigNum BigNum::operator /(const BigNum& a){
  BigNum division = new BigNum("0");
  if(a.back() == 0) return division;
  else if(this->back() == 0) return division;
  else if(a.size() > 1) return *this;
  else if(a.getDigit(0) == 1 && !a.getSign()) return *this;
  else if(a.getDigit(0) == 1 && a.getSign()){
    this->setSign(true);
    return *this;
  }
  else if(a.back() > this->back() && this->size() == 1) return division;
  division.resize(this.size());
  double b,c,carry = 0;
  for(unsigned long int i=this->size()-1; i>0; i--){
    b = this->getDigit(i)/a.getDigit(0)+carry;
    carry = modf(b,&c);
    division.setDigit(i,c);
    carry *= WORD_SIZE;
  }
  b = this->getDigit(0)/a.getDigit(0)+carry;
  carry = modf(b,&c);
  division.setDigit(0,c);
  while(division.back() == 0 && division.size() > 1){
    division.pop_back();
  }
  if(this->getSign() && a.getSign()) division.setSign(false);
  else if(this->getSign() || a.getSign()) division.setSign(true);
  return division;
};

// BigNum a must be smaller and a.size() == 1
BigNum BigNum::operator %(const BigNum& a){
  BigNum modulo = new BigNum("0");
  if(a.back() == 0) return modulo;
  else if(this->back() == 0) return modulo;
  else if(a.size() > 1) return *this;
  else if(a.getDigit(0) == 1) return modulo;
  else if(this->size() == 1 && a.back() > this->back()) return *this;
  double b,c,carrymod = 0;
  for(unsigned long int i=this->size()-1; i>0; i--){
    b = this->getDigit(i)/a.getDigit(i)+carrymod;
    carrymod = modf(b,&c);
    carrymod *= WORD_SIZE;
  }
  b = this->getDigit(0)/a.getDigit(0)+carrymod;
  carrymod = modf(b,&c);
  modulo.setDigit(0,(long unsigned int)round(carrymod*a.getDigit(i)));
  while(modulo.back() == 0 && modulo.size() > 1){
    modulo.pop_back();
  }
  if(this->getSign()) modulo.setSign(true);
  return modulo;
};

// Can only exponentiate postive integers, but a can be negative
BigNum pow(const BigNum& a, const unsigned long int n){
  if(n == 0){
    return BigNum("1");
  }
  BigNum x = a;
  BigNum y = BigNum("1");
  unsigned long int z = n;
  while(z > 1){
    if(z % 2 == 0){
      x = x * x;
      z = (unsigned long int)(z / 2);
    }
    else{
      y = x * y;
      x = x * x;
      z = (unsigned long int)((z - 1) / 2);
    }
  }
  return x * y;
};
