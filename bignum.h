#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigNum{
  private:
    vector<short int> digits;
  public:
    //Constructors
    BigNum();
    BigNum(const string& num);
    BigNum(const unsigned long int num);
    //Deconstructor
    ~BigNum();
    //Setter
    void setDigit(const unsigned long int digit, const short int x);
    //Getter
    short int getDigit(const unsigned long int digit) const;
    //Vector API
    unsigned long int size() const;
    void resize(const unsigned long int x);
    void push_back(const int x);
    void pop_back();
    short int back() const;
    //Operators
    BigNum operator =(const BigNum& a);
    BigNum operator +(const BigNum& a);
    BigNum operator -(const BigNum& a);
    BigNum operator *(const BigNum& a);
};

//Constructors
BigNum::BigNum(){
  this->resize(0);
};

BigNum::BigNum(const string& num){
  for(unsigned long int i=num.length()-1; i>0; i--){
    this->push_back(stoi(num.substr(i,1)));
  }
  this->push_back(stoi(num.substr(0,1)));
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
void BigNum::setDigit(const unsigned long int digit, const short int x){
  this->digits[digit] = x;
};

//Getter
short int BigNum::getDigit(const unsigned long int digit) const {
  return this->digits[digit];
};

//Vector API
unsigned long int BigNum::size() const {
  return this->digits.size();
};

void BigNum::resize(const unsigned long int x){
  this->digits.resize(x);
};

void BigNum::push_back(const int x){
  this->digits.push_back(x);
};

void BigNum::pop_back(){
  this->digits.pop_back();
};

short int BigNum::back() const {
  return this->digits.back();
};

//Operators
BigNum BigNum::operator =(const BigNum& a){
  this->digits = a.digits;
  return *this;
};

BigNum BigNum::operator +(const BigNum& a){
  BigNum c = BigNum();
  unsigned long int j;
  for(unsigned long int i=0; i<a.size(); i++){
    if(c.size() <= i){
      c.push_back(a.getDigit(i) + this->getDigit(i));
      j = i;
      while(c.getDigit(j) > 9){
        c.setDigit(j,c.getDigit(j)-10);
        if(j+1 >= c.size()){
          c.push_back(1);
          break;
        }
        else{
          c.setDigit(j+1,c.getDigit(j+1)+1);
          j++;
        }
      }
    }
    else{
      c.setDigit(i,c.getDigit(i)+a.getDigit(i)+this->getDigit(i));
      j = i;
      while(c.getDigit(j) > 9){
        c.setDigit(j,c.getDigit(j)-10);
        if(j+1 >= c.size()){
          c.push_back(1);
          break;
        }
        else{
          c.setDigit(j+1,c.getDigit(j+1)+1);
          j++;
        }
      }
    }
  }
  return c;
};


// Can only do subtraction that ends with a positive number, for now
BigNum BigNum::operator -(const BigNum& a){
  if(this->size() < a.size()){
    return BigNum("0");
  }
  else if(this->size() == a.size() && this->back() < a.back()){
    return BigNum("0");
  }
  unsigned long int j;
  for(unsigned long int i=0; i<this->size(); i++){
    this->setDigit(i,this->getDigit(i)-a.getDigit(i));
    j = i;
    while(this->getDigit(j) < 0){
      this->setDigit(j+1,this->getDigit(j+1)-1);
      this->setDigit(j,this->getDigit(j)+10);
      j++;
    }
  }
  while(this->back() == 0){
    this->pop_back();
  }
  return *this;
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
  unsigned short int carry;
  for(unsigned long int b_i=0; b_i<a.size(); b_i++){
    carry = 0;
    for(unsigned long int a_i=0; a_i<this->size(); a_i++){
      product.setDigit(a_i+b_i,product.getDigit(a_i+b_i)+carry+this->getDigit(a_i)*a.getDigit(b_i));
      carry = (unsigned short int)(product.getDigit(a_i+b_i) / 10);
      product.setDigit(a_i+b_i,product.getDigit(a_i+b_i)%10);
    }
    product.setDigit(b_i+this->size(),carry);
  }
  while(product.back() == 0){
    product.pop_back();
  }
  return product;
};

ostream& operator <<(ostream& os, const BigNum& a){
  if(a.size() > 0){
    for(unsigned long int i=a.size()-1; i>0; i--){
      os << a.getDigit(i);
    }
    os << a.getDigit(0);
  }
  else{
    os << "err:size 0";
  }
  return os;
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
