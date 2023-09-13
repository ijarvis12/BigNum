#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const unsigned long int WORD_SIZE = 1000000000;
const char WORD_LEN = 9;

class BigInt{
  private:
    bool is_negative; // true (1) = negative, false (0) = postitive
    vector<long int> digits;
  public:
    //Constructors
    BigInt();
    BigInt(const string& num);
    BigInt(const long int num);
    //Deconstructor
    ~BigInt();
    //Setters
    void setNegative(const bool b);
    void setDigit(const unsigned long int digit, const long int x);
    //Getters
    bool ifNegative() const;
    long int getDigit(const unsigned long int digit) const;
    //Vector API
    unsigned long int size() const;
    void resize(const unsigned long int x);
    void push_back(const long int x);
    void pop_back();
    long int back() const;
    //Operators
    BigInt operator =(const BigInt& a);
};

BigInt operator +(const BigInt& first, const BigInt& second);
BigInt operator -(const BigInt& first, const BigInt& second);
BigInt operator *(const BigInt& first, const BigInt& second);
BigInt operator /(const BigInt& first, const BigInt& second);
BigInt operator %(const BigInt& first, const BigInt& second);

//Constructors
BigInt::BigInt(){
  this->is_negative = false;
  this->resize(0);
};

BigInt::BigInt(const string& strnum){
  this->resize(0);
  string num = "";
  if(strnum.substr(0,1).compare("-") == 0){
    this->is_negative = true;
    num = strnum.substr(1,strnum.length()-1);
  }
  else {
    this->is_negative = false;
    num = strnum;
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

BigInt::BigInt(const long int num){
  string x = to_string(num);
  *this = BigInt(x);
};

//Deconstructor
BigInt::~BigInt(){
  this->is_negative = false;
  this->digits.clear();
};

//Setters
void BigInt::setNegative(const bool b){
  this->is_negative = b;
}

void BigInt::setDigit(const unsigned long int digit, const long int x){
  this->digits[digit] = x;
};

//Getters
bool BigInt::ifNegative() const {
  return this->is_negative;
}

long int BigInt::getDigit(const unsigned long int digit) const {
  return this->digits[digit];
};

//Vector API
unsigned long int BigInt::size() const {
  return this->digits.size();
};

void BigInt::resize(const unsigned long int x){
  this->digits.resize(x);
};

void BigInt::push_back(const long int x){
  this->digits.push_back(x);
};

void BigInt::pop_back(){
  this->digits.pop_back();
};

long int BigInt::back() const {
  return this->digits.back();
};

//Operators
ostream& operator <<(ostream& os, const BigInt& a){
  if(a.ifNegative()) os << "-";
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

bool operator <(const BigInt& first, const BigInt& second){
  if( (!first.ifNegative() && !second.ifNegative()) || (first.ifNegative() && second.ifNegative()) ){
    if(second.size() < first.size()) return false;
    else if(second.size() == first.size() && second.back() <= first.back()) return false;
    else return true;
  }
  else if(!first.ifNegative() && second.ifNegative()) return false;
  else return true;
}

bool operator >(const BigInt& first, const BigInt& second){
  return !(first < second);
}

BigInt BigInt::operator =(const BigInt& a){
  this->is_negative = a.ifNegative();
  this->resize(a.size());
  for(unsigned long int i=0; i<a.size(); i++){
    this->setDigit(i,a.getDigit(i));
  }
  return *this;
};

BigInt operator +(const BigInt& first, const BigInt& second){
  if(first.ifNegative() && !second.ifNegative() && first > second){
    BigInt add1 = first;
    add1.setNegative(false);
    BigInt add2 = add1 - second;
    add2.setNegative(true);
    return add2;
  }
  else if(first.ifNegative() && !second.ifNegative() && first < second){
    BigInt add = first;
    add.setNegative(false);
    return second - add;
  }
  else if(first.ifNegative() && !second.ifNegative()) return BigInt("0");
  else if(!first.ifNegative() && second.ifNegative() && first > second){
    BigInt add = second;
    add.setNegative(false);
    return first - add;
  }
  else if(!first.ifNegative() && second.ifNegative() && first < second){
    BigInt add1 = second;
    add1.setNegative(false);
    BigInt add2 = add1 - first;
    add2.setNegative(true);
    return add2;
  }
  else if(!first.ifNegative() && second.ifNegative()) return BigInt("0");
  else if(first.ifNegative() && second.ifNegative()){
    BigInt add1 = first;
    BigInt add2 = second;
    add1.setNegative(false);
    add2.setNegative(false);
    BigInt add3 = add1 + add2;
    add3.setNegative(true);
    return add3;
  }
  BigInt addition = first;
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

BigInt operator -(const BigInt& first, const BigInt& second){
  if(first.ifNegative() && !second.ifNegative() && first > second){
    BigInt sub1 = first;
    sub1.setNegative(false);
    BigInt sub2 = sub1 - second;
    sub2.setNegative(true);
    return sub2;
  }
  else if(first.ifNegative() && !second.ifNegative() && first < second){
    BigInt sub = first;
    sub.setNegative(false);
    return second - sub;
  }
  else if(first.ifNegative() && !second.ifNegative()) return BigInt("0");
  else if(!first.ifNegative() && second.ifNegative()){
    BigInt sub = second;
    sub.setNegative(false);
    return first + sub;
  }
  else if(first.ifNegative() && second.ifNegative()){
    BigInt sub = second;
    return sub - first;
  }
  BigInt subtract = first;
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
BigInt operator *(const BigInt& first, const BigInt& second){
  if(second.back() == 0) return BigInt("0");
  else if(first.back() == 0) return BigInt("0");
  else if(second.size() == 1 && second.getDigit(0) == 1 && !second.ifNegative()) return first;
  else if(second.size() == 1 && second.getDigit(0) == 1 && second.ifNegative()){
    BigInt prod = first;
    prod.setNegative(true);
    return prod;
  }
  else if(first.size() == 1 && first.getDigit(0) == 1 && !first.ifNegative()) return second;
  else if(first.size() == 1 && first.getDigit(0) == 1 && first.ifNegative()){
    BigInt prod = second;
    prod.setNegative(true);
    return prod;
  }
  else if(first.ifNegative() && second.ifNegative()){
    BigInt prod1 = first;
    BigInt prod2 = second;
    prod1.setNegative(false);
    prod2.setNegative(false);
    return prod1 * prod2;
  }
  else if(first.ifNegative() && !second.ifNegative()){
    BigInt prod1 = first;
    prod1.setNegative(false);
    BigInt prod2 = prod1 * second;
    prod2.setNegative(true);
    return prod2;
  }
  else if(!first.ifNegative() && second.ifNegative()){
    BigInt prod1 = second;
    prod1.setNegative(false);
    BigInt prod2 = first * prod1;
    prod2.setNegative(true);
    return prod2;
  }
  BigInt product = BigInt();
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

BigInt operator /(const BigInt& first, const BigInt& second){
  if(second.back() == 0) return BigInt("0");
  else if(first.back() == 0) return BigInt("0");
  else{
    BigInt f = first;
    BigInt zero = BigInt("0");
    BigInt one = BigInt("1");
    BigInt counter = BigInt("0");
    while(f > zero){
      f = f - second;
      counter = counter + one;
    }
    return counter;
  }
};

BigInt operator %(const BigInt& first, const BigInt& second){
  if(second.back() == 0) return BigInt("0");
  else if(first.back() == 0) return BigInt("0");
  else if(second.size() == 1 && second.getDigit(0) == 1) return BigInt("0");
  else{
    BigInt f = first;
    BigInt zero = BigInt("0");
    while(f > zero) f = f - second;
    if(f < zero) f = f + second;
    return f;
  }
};

// Can only exponentiate postive n powers, but BigInt a can be negative
BigInt pow(const BigInt& a, const unsigned long int n){
  if(n == 0){
    return BigInt("1");
  }
  BigInt x = a;
  BigInt y = BigInt("1");
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
