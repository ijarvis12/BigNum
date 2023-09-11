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
    bool isNegative() const;
    long int getDigit(const unsigned long int digit) const;
    //Vector API
    unsigned long int size() const;
    void resize(const unsigned long int x);
    void push_back(const long int x);
    void pop_back();
    long int back() const;
    //Operators
    BigNum operator =(const BigNum& a);
    BigNum operator +(const BigNum& first, const BigNum& second);
    BigNum operator -(const BigNum& first, const BigNum& second);
    BigNum operator *(const BigNum& first, const BigNum& second);
    BigNum operator /(const BigNum& first, const BigNum& second);
    BigNum operator %(const BigNum& first, const BigNum& second);
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
bool BigNum::isNegative() const {
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
  if(a.isNegative()) os << "-";
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

bool operator <(const BigNum& first, const BigNum& second){
  if( (!first.isNegative() && !second.isNegative()) || (first.isNegative() && second.isNegative()) ){
    if(second.size() < first.size()) return false;
    else if(second.size() == first.size() && second.back() <= first.back()) return false;
    else return true;
  }
  else if(!first.isNegative() && second.isNegative()) return false;
  else return true;
}

bool operator >(const BigNum& first, const BigNum second){
  return !(first < second);
}

BigNum BigNum::operator =(const BigNum& a){
  this->sign = a.isNegative();
  this->resize(a.size());
  for(unsigned long int i=0; i<a.size(); i++){
    this->setDigit(i,a.getDigit(i));
  }
  return *this;
};

BigNum BigNum::operator +(const BigNum& first, const BigNum& second){
  if(first.isNegative() && !second.isNegative() && first > second){
    BigNum add1 = first;
    first.setSign(false);
    BigNum add2 = add1 - second;
    add2.setSign(true);
    return add2;
  }
  else if(first.isNegative() && !second.isNegative() && first < second){
    BigNum add = first;
    add.setSign(false);
    return second - add;
  }
  else if(first.isNegative() && !second.isNegative()) return BigNum("0");
  else if(!first.isNegative() && second.isNegative() && first > second){
    BigNum add = second;
    add.setSign(false);
    return first - add;
  }
  else if(!first.isNegative() && second.isNegative() && first < second){
    BigNum add1 = second;
    add1.setSign(false);
    BigNum add2 = add1 - first;
    add2.setSign(true);
    return add2;
  }
  else if(!first.isNegative() && second.isNegative()) return BigNum("0");
  else if(first.isNegative() && second.isNegative()){
    BigNum add1 = first;
    BigNum add2 = second;
    add1.setSign(false);
    add2.setSign(false);
    BigNum add3 = add1 + add2;
    add3.setSign(true);
    return add3;
  }
  BigNum addition = first;
  for(unsigned long int i=0; i<second.size(); i++){
    if(i > addition.size()-1){
      addition.push_back(0);
    }
    addition.setDigit(i, addition.getDigit(i) + second.getDigit(i));
    for(unsigned long int j=i; j<addition.size(); j++){
      while(addition.getDigit(j) > (WORD_SIZE - 1)){
        addition.setDigit(j, addition.getDigit(j) - WORD_SIZE);
        if(j+1 > (addition.size() - 1)){
          addition.push_back(1);
        }
        else{
          addition.setDigit(j+1, addition.getDigit(j+1) + 1);
        }
      }
      if(addition.getDigit(j+1) < WORD_SIZE){
        break;
      }
    }
  }
  return addition;
};

BigNum BigNum::operator -(const BigNum& first, const BigNum& second){
  if(first.isNegative() && !second.isNegative() && first > second){
    BigNum sub1 = first;
    sub1.setSign(false);
    BigNum sub2 = sub1 - second;
    sub2.setSign(true);
    return sub2;
  }
  else if(first.isNegative() && !second.isNegative() && first < second){
    BigNum sub1 = first;
    sub1.setSign(false);
    BigNum sub2 = second - sub1;
    return sub2;
  }
  else if(first.isNegative() && !second.isNegative()) return BigNum("0");
  else if(!first.isNegative() && second.isNegative()){
    BigNum sub = second;
    sub.setSign(false);
    return first + sub;
  }
  else if(first.isNegative() && second.isNegative()){
    BigNum sub = a;
    return sub - first;
  }
  BigNum subtract = first;
  for(unsigned long int i=0; i<second.size(); i++){
    subtract.setDigit(i, subtract.getDigit(i)-second.getDigit(i));
    for(unsigned long int j=i; j<subtract.size()-1; j++){
      while(subtract.getDigit(j) < 0){
        subtract.setDigit(j, subtract.getDigit(j) + WORD_SIZE);
        subtract.setDigit(j+1, subtract.getDigit(j+1) - 1);
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
BigNum BigNum::operator *(const BigNum& first, const BigNum& second){
  if(second.back() == 0) return BigNum("0");
  else if(first.back() == 0) return BigNum("0");
  else if(second.size() == 1 && second.getDigit(0) == 1 && !second.isNegative()) return first;
  else if(second.size() == 1 && second.getDigit(0) == 1 && second.isNegative()){
    BigNum prod = first;
    prod.setSign(true);
    return prod;
  }
  else if(first.size() == 1 && first.getDigit(0) == 1 && !first.isNegative()) return second;
  else if(first.size() == 1 && first.getDigit(0) == 1 && first.isNegative()){
    BigNum prod = second;
    prod.setSign(true);
    return prod;
  }
  else if(first.isNegative() && second.isNegative()){
    BigNum prod1 = first;
    BigNum prod2 = second;
    prod1.setSign(false);
    prod2.setSign(false);
    return prod1 * prod2;
  }
  else if(first.isNegative() && !second.isNegative()){
    BigNum prod1 = first;
    prod1.setSign(false);
    BigNum prod2 = prod1 * second;
    prod2.setSign(true);
    return prod2;
  }
  else if(!first.isNegative() && second.isNegative()){
    BigNum prod1 = second;
    prod1.setSign(false);
    BigNum prod2 = first * prod1;
    prod2.setSign(true);
    return prod2;
  }
  BigNum product = BigNum();
  product.resize(first.size()+second.size());
  unsigned long int carry;
  for(unsigned long int b_i=0; b_i<second.size(); b_i++){
    carry = 0;
    for(unsigned long int a_i=0; a_i<first.size(); a_i++){
      product.setDigit(a_i+b_i, product.getDigit(a_i+b_i)+carry+first.getDigit(a_i)*second.getDigit(b_i));
      carry = (unsigned long int)(product.getDigit(a_i+b_i) / WORD_SIZE);
      product.setDigit(a_i+b_i, product.getDigit(a_i+b_i) % WORD_SIZE);
    }
    product.setDigit(b_i+first.size(),carry);
  }
  while(product.back() == 0){
    product.pop_back();
  }
  return product;
};

//BigNum second must be smaller and second.size() == 1
BigNum BigNum::operator /(const BigNum& first, const BigNum& second){
  BigNum division = new BigNum("0");
  if(second.back() == 0) return division;
  else if(first.back() == 0) return division;
  else if(second.size() > 1) return first;
  else if(second.getDigit(0) == 1 && !second.isNegative()) return first;
  else if(second.getDigit(0) == 1 && second.isNegative()){
    BigNum div = first;
    div.setSign(!div.isNegative());
    return div;
  }
  else if(second.back() > first.back() && first.size() == 1) return division;
  division.resize(first.size());
  double b,c,carry = 0;
  for(unsigned long int i=first.size()-1; i>0; i--){
    b = first.getDigit(i)/second.getDigit(0)+carry;
    carry = modf(b,&c);
    division.setDigit(i,c);
    carry *= WORD_SIZE;
  }
  b = first.getDigit(0)/second.getDigit(0)+carry;
  carry = modf(b,&c);
  division.setDigit(0,c);
  while(division.back() == 0 && division.size() > 1){
    division.pop_back();
  }
  if(first.isNegative() && second.isNegative()) division.setSign(false);
  else if(first.isNegative() || second.isNegative()) division.setSign(true);
  return division;
};

// BigNum second must be smaller and second.size() == 1
BigNum BigNum::operator %(const BigNum& first, const BigNum& second){
  BigNum modulo = new BigNum("0");
  if(second.back() == 0) return modulo;
  else if(first.back() == 0) return modulo;
  else if(second.size() > 1) return first;
  else if(second.getDigit(0) == 1) return modulo;
  else if(first.size() == 1 && second.back() > first.back()) return first;
  double b,c,carrymod = 0;
  for(unsigned long int i=first.size()-1; i>0; i--){
    b = first.getDigit(i)/second.getDigit(0)+carrymod;
    carrymod = modf(b,&c);
    carrymod *= WORD_SIZE;
  }
  b = first.getDigit(0)/second.getDigit(0)+carrymod;
  carrymod = modf(b,&c);
  modulo.setDigit(0,(long unsigned int)round(carrymod*second.getDigit(i)));
  while(modulo.back() == 0 && modulo.size() > 1){
    modulo.pop_back();
  }
  if(first.isNegative()) modulo.setSign(true);
  return modulo;
};

// Can only exponentiate postive n powers, but BigNum a can be negative
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
