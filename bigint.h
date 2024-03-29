#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long int WORD_SIZE = 1000000000;
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
//More operators
BigInt operator +(const BigInt& first, const BigInt& second);
BigInt operator -(const BigInt& first, const BigInt& second);
BigInt operator *(const BigInt& first, const BigInt& second);
BigInt operator /(const BigInt& first, const BigInt& second);
BigInt operator %(const BigInt& first, const BigInt& second);
BigInt pow(const BigInt& a, const unsigned long int& n);
BigInt pow(const BigInt& a, const BigInt& n);

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
    num = strnum.substr(1,strnum.length()-1); //yes it is just len - 1
  }
  else {
    this->is_negative = false;
    num = strnum;
  }
  if(num.length() > WORD_LEN){
    for(long int i=num.length()-WORD_LEN; i>0; i-=WORD_LEN){
      this->push_back(stoul(num.substr(i,WORD_LEN)));
    }
    char mod = (num.length() % WORD_LEN);
    if(mod != 0){
      this->push_back(stoul(num.substr(0,mod)));
    }
    else{
      this->push_back(stoul(num.substr(0,WORD_LEN)));
    }
  }
  else{
    this->push_back(stoul(num));
  }
  while(this->back() == 0 && this->size() > 1) this->pop_back(); //for BigDecimal initialization sanity check
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
  unsigned long int before_x = this->digits.size();
  this->digits.resize(x);
  if(before_x < x) for(unsigned long int i=before_x; i<this->digits.size(); i++) this->digits[i] = 0;
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
  if( (!first.ifNegative()) && (!second.ifNegative()) ){
    if(first.size() > second.size()) return false;
    else if(first.size() == second.size() && first.back() >= second.back()) return false;
    else return true;
  }
  else if( first.ifNegative() && second.ifNegative() ){
    if(first.size() < second.size()) return false;
    else if(first.size() == second.size() && first.back() <= second.back()) return false;
    else return true;
  }
  else if( (!first.ifNegative()) && second.ifNegative() ) return false;
  else return true;
}

bool operator >(const BigInt& first, const BigInt& second){
  if( (!first.ifNegative()) && (!second.ifNegative()) ){
    if(first.size() < second.size()) return false;
    else if(first.size() == second.size() && first.back() <= second.back()) return false;
    else return true;
  }
  else if( first.ifNegative() && second.ifNegative() ){
    if(first.size() > second.size()) return false;
    else if(first.size() == second.size() && first.back() >= second.back()) return false;
    else return true;
  }
  else if( (!first.ifNegative()) && second.ifNegative() ) return false;
  else return true;
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
  BigInt add_first = first;
  BigInt add_second = second;
  add_first.setNegative(false);
  add_second.setNegative(false);
  if(first.ifNegative() && (!second.ifNegative()) && add_first > add_second){
    BigInt addition = add_first - add_second;
    addition.setNegative(true);
    return addition;
  }
  else if(first.ifNegative() && (!second.ifNegative()) && add_first < add_second) return add_second - add_first;
  else if(first.ifNegative() && (!second.ifNegative())) return BigInt("0");
  else if((!first.ifNegative()) && second.ifNegative() && add_first > add_second) return add_first - add_second;
  else if((!first.ifNegative()) && second.ifNegative() && add_first < add_second){
    BigInt addition = add_second - add_first;
    addition.setNegative(true);
    return addition;
  }
  else if((!first.ifNegative()) && second.ifNegative()) return BigInt("0");
  else if(first.ifNegative() && second.ifNegative()){
    BigInt addition = add_first + add_second;
    addition.setNegative(true);
    return addition;
  }
  BigInt addition = add_first;
  for(unsigned long int i=0; i<add_second.size(); i++){
    if(i > addition.size()-1) addition.push_back(0);
    addition.setDigit(i, addition.getDigit(i) + add_second.getDigit(i));
    unsigned long int j=i;
    while(addition.getDigit(j) > (WORD_SIZE - 1)){
      addition.setDigit(j, addition.getDigit(j) - WORD_SIZE);
      if(j+1 > (addition.size() - 1)) addition.push_back(1);
      else addition.setDigit(j+1, addition.getDigit(j+1) + 1);
      j++;
    }
  }
  return addition;
};

BigInt operator -(const BigInt& first, const BigInt& second){
  BigInt sub_first = first;
  BigInt sub_second = second;
  sub_first.setNegative(false);
  sub_second.setNegative(false);
  if(first.ifNegative() && (!second.ifNegative())){
    BigInt subtract = sub_first + sub_second;
    subtract.setNegative(true);
    return subtract;
  }
  else if((!first.ifNegative()) && second.ifNegative()) return sub_first + sub_second;
  else if(first.ifNegative() && second.ifNegative() && sub_first > sub_second){
    BigInt subtract = sub_first - sub_second;
    subtract.setNegative(true);
    return subtract;
  }
  else if(first.ifNegative() && second.ifNegative() && sub_first < sub_second) return sub_second - sub_first;
  else if((!first.ifNegative()) && (!second.ifNegative()) && sub_first < sub_second){
    BigInt subtract = sub_second - sub_first;
    subtract.setNegative(true);
    return subtract;
  }
  BigInt subtract = sub_first;
  for(unsigned long int i=0; i<sub_second.size(); i++){
    subtract.setDigit(i, subtract.getDigit(i) - sub_second.getDigit(i));
    unsigned long int j=i;
    while(subtract.getDigit(j) < 0){
      subtract.setDigit(j, subtract.getDigit(j) + WORD_SIZE);
      subtract.setDigit(j+1, subtract.getDigit(j+1) - 1);
      j++;
    }
  }
  while(subtract.back() == 0 && subtract.size() > 1) subtract.pop_back();
  return subtract;
};

// Use long multiplcation
//https://en.wikipedia.org/wiki/Multiplication_algorithm
BigInt operator *(const BigInt& first, const BigInt& second){
  if(second.back() == 0) return BigInt("0");
  else if(first.back() == 0) return BigInt("0");
  else if(second.size() == 1 && second.getDigit(0) == 1 && (!second.ifNegative())) return first;
  else if(second.size() == 1 && second.getDigit(0) == 1 && second.ifNegative()){
    BigInt prod = first;
    prod.setNegative(true);
    return prod;
  }
  else if(first.size() == 1 && first.getDigit(0) == 1 && (!first.ifNegative())) return second;
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
  else if(first.ifNegative() && (!second.ifNegative())){
    BigInt prod1 = first;
    prod1.setNegative(false);
    BigInt prod2 = prod1 * second;
    prod2.setNegative(true);
    return prod2;
  }
  else if((!first.ifNegative()) && second.ifNegative()){
    BigInt prod1 = second;
    prod1.setNegative(false);
    BigInt prod2 = first * prod1;
    prod2.setNegative(true);
    return prod2;
  }
  BigInt product = BigInt("0");
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
  while(product.back() == 0 && product.size() > 1) product.pop_back();
  return product;
};

BigInt operator /(const BigInt& first, const BigInt& second){
  if(second.back() == 0) return BigInt("0");
  else if(first.back() == 0) return BigInt("0");
  else{
    BigInt f = first;
    f.setNegative(false);
    BigInt s = second;
    s.setNegative(false);
    BigInt zero = BigInt("0");
    BigInt one = BigInt("1");
    BigInt counter = zero;
    BigInt ten = BigInt("10");
    BigInt i = ten;
    BigInt si = s;
    BigInt limit = si - one;
    while(one < i){
      si = s;
      i = one;
      while(f > si*ten){
        si = si * ten;
        i = i * ten;
      }
      limit = si - one;
      while(f > limit){
        f = f - si;
        counter = counter + i;
      }
    }
    if(first.ifNegative() && second.ifNegative()) return counter;
    else if(first.ifNegative() || second.ifNegative()) counter = counter * BigInt("-1");
    return counter;
  }
};

BigInt operator %(const BigInt& first, const BigInt& second){
  BigInt zero = BigInt("0");
  if(second.back() == 0) return zero;
  else if(first.back() == 0) return zero;
  else if(second.size() == 1 && second.getDigit(0) == 1) return zero;
  else{
    BigInt f = first;
    f.setNegative(false);
    BigInt s = second;
    s.setNegative(false);
    BigInt one = BigInt("1");
    BigInt ten = BigInt("10");
    BigInt i = ten;
    BigInt si = s;
    BigInt limit = si - one;
    while(one < i){
      si = s;
      i = one;
      while(f > si*ten){
        si = si * ten;
        i = i * ten;
      }
      limit = si - one;
      while(f > limit) f = f - si;
    }
    if(first.ifNegative()) f = f * BigInt("-1");
    return f;
  }
};

// Can only exponentiate postive n powers, but BigInt a can be negative
BigInt pow(const BigInt& a, const unsigned long int& n){
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

//Remember n must be positive
BigInt pow(const BigInt& a, const BigInt& n){
  BigInt one = BigInt("1");
  if(n.size() == 1 && n.back() == 0){
    return one;
  }
  BigInt x = a;
  BigInt y = one;
  BigInt z = n;
  BigInt mod = one;
  BigInt two = BigInt("2");
  while(z > one){
    mod = z % two;
    if(mod.size() == 1 && mod.back() == 0){
      x = x * x;
      z = z / two;
    }
    else{
      y = x * y;
      x = x * x;
      z = (z - one) / two;
    }
  }
  return x * y;
};
