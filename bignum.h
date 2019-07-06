#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigNum{
  public:
    vector<short int> digits;
    BigNum();
    BigNum(const string& num);
    BigNum(unsigned long int num);
    ~BigNum();
    BigNum operator +(const BigNum& a);
    BigNum operator -(const BigNum& a);
    //BigNum operator *(const BigNum& a, const BigNum& b);
};

BigNum::BigNum(){
  this->digits.reserve(0);
};

BigNum::BigNum(const string& num){
  for(unsigned long int i=num.length()-1; i>0; i--){
    this->digits.push_back(stoi(num.substr(i,1)));
  }
  this->digits.push_back(stoi(num.substr(0,1)));
};

BigNum::BigNum(unsigned long int num){
  string x = to_string(num);
  BigNum a = BigNum(x);
  this->digits = a.digits;
};

BigNum::~BigNum(){
  this->digits.clear();
};

BigNum BigNum::operator +(const BigNum& a){
  BigNum c = BigNum();
  unsigned long int j;
  for(unsigned long int i=0; i<a.digits.size(); i++){
    if(c.digits.size() <= i){
      c.digits.push_back(a.digits[i] + this->digits[i]);
    }
    else{
      c.digits[i] += a.digits[i] + this->digits[i];
      j = i;
      while(c.digits[j] > 9){
        c.digits[j] -= 10;
        if(j >= c.digits.size()){
          c.digits.push_back(1);
        }
        else{
          c.digits[j+1] += 1;
        }
        j++;
      }
    }
  }
  return c;
};


// Can only do subtraction that ends with a positive number, for now
BigNum BigNum::operator -(const BigNum& a){
  if(this->digits.size() < a.digits.size()){
    return BigNum();
  }
  else if(this->digits.size() == a.digits.size() && this->digits.back() < a.digits.back()){
    return BigNum();
  }
  unsigned long int j;
  for(unsigned long int i=0; i<this->digits.size(); i--){
    this->digits[i] -= a.digits[i];
    j = i;
    while(this->digits[j] < 0){
      this->digits[j+1] -= 1;
      this->digits[j] += 10;
      j++;
    }
  }
  while(this->digits.back() == 0){
    this->digits.pop_back();
  }
  return *this;
};

/*// Use peasant multiplication
// https://en.wikipedia.org/wiki/Ancient_Egyptian_multiplication
BigNum BigNum::operator *(const BigNum& a){
  if(a.digits.back() == 0){
    return BigNum();
  }
  else if(this->digits.back() == 0){
    return BigNum();
  }
  BigNum c = a;
  while(){
    // Fill in the algorithm
  }
  return *this;
};*/

ostream& operator <<(ostream& os, const BigNum& a){
  if(a.digits.size() > 0){
    for(unsigned long int i=a.digits.size()-1; i>0; i--){
      os << a.digits[i];
    }
    os << a.digits[0];
  }
  else{
    os << "err:size 0";
  }
  return os;
};

/*// Can only exponentiate postive integers
BigNum pow(const BigNum& a, unsigned long int n){
  BigNum x = BigNum("1");
  if(n == 0){
    return x;
  }
  BigNum y = BigNum("1");
  while(n > 1){
    if(n % 2 == 0){
      x = x * x;
      n /= 2;
    }
    else{
      y = x * y;
      x = x * x;
      n = (n - 1) / 2
    }
  }
  return x * y;
}*/
