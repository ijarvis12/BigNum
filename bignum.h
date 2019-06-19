#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class BigNum{
  public:
    unsigned long int length;
    short *digits;
    BigNum();
    BigNum(const string& num);
    BigNum(unsigned long int num);
    BigNum operator +(const BigNum& a, const BigNum& b);
    BigNum operator -(const BigNum& a, const BigNum& b);
    BigNum operator *(const BigNum& a, const BigNum& b);
    ostream& operator <<(ostream& os, const BigNum& a);
    BigNum pow(const BigNum& a, unsigned long int n);
};

BigNum::BigNum(){
  this->length = 1;
  this->digits[0] = 0;
};

BigNum::BigNum(const string& num){
  this->length = num.length();
  for(unsigned long int i=num.length()-1; i>=0; i--){
    this->digits[i] = stoi(num);
  }
};

BigNum::BigNum(unsigned long int num){
  string x = to_string(num);
  BigNum a = BigNum(x);
  this->digits = a.digits;
  this->length = a.length;
};

BigNum operator +(const BigNum& a, const BigNum& b){
  BigNum c = BigNum();
  unsigned long int j;
  for(unsigned long int i=0; i<a.length; i++){
    c.digits[i] = a.digits[i] + b.digits[i];
    j = i;
    while(c.digits[j] > 9){
      c.digits[j] -= 10;
      j++;
      c.digits[j] += 1;
    }
    if(a.length > b.length){
      c.length = a.length;
    }
    else if(i > j){
      c.length = i + 1;
    }
    else{
      c.length = j + 1;
    }
  }
  return c;
};

// Can only do subtraction that ends with a positive number
BigNum operator -(const BigNum& a, const BigNum& b){
  if(b.length > a.length){
    return BigNum();
  }
  else if(b.length == a.length && b.digits[b.length-1] > a.digits[a.length-1]){
    return BigNum();
  }
  BigNum c = a;
  for(unsigned long int i=0; i<b.length; i--){
    c.digits[i] -= b.digits[i];
    /* Much work to
     * be done */
  }
  return c;
};

// Use peasant multiplication
// https://en.wikipedia.org/wiki/Ancient_Egyptian_multiplication
BigNum operator *(const BigNum& a, const BigNum& b){
  if(a.length == 1 && a.digits[0] == 0){
    return BigNum();
  }
  else if(b.length == 0 && b.digits[0] == 0){
    return BigNum();
  }
  BigNum c = a;
  while(){
    /* Fill in the algorithm */
  }
  return BigNum();
};

ostream& operator <<(ostream& os, const BigNum& a){
  for(unsigned long int i=a.length-1; i>=0; i--){
    os << a.digits[i];
  }
  return os;
};

// Can only exponentiate postive integers
BigNum pow(const BigNum& a, unsigned long int n){
  BigNum x = BigNum("1");
  if(b == 0){
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
}
