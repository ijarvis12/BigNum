#include <iostream>
#include <string>
#include <cmath>
#include "bigint.h"
using namespace std;

class BigDecimal{
  private:
    BigInt value;
    BigInt scale;
  public:
    BigDecimal();
    BigDecimal(const string& num);
    BigDecimal(const double& num);
    BigDecimal(const BigInt& v, const BigInt& s);
    ~BigDecimal();
    void trim();
    unsigned long int precision();
    //Getters
    BigInt getValue() const;
    BigInt getScale() const;
    //Setters
    void setValue(const BigInt& a);
    void setScale(const BigInt& a);
    //Operators
    BigDecimal operator =(const BigDecimal& a);
};

//More operators
BigDecimal operator +(const BigDecimal& first, const BigDecimal& second);
BigDecimal operator -(const BigDecimal& first, const BigDecimal& second);
BigDecimal operator *(const BigDecimal& first, const BigDecimal& second);
BigDecimal operator /(const BigDecimal& first, const BigDecimal& second);
BigDecimal operator %(const BigDecimal& first, const BigDecimal& second);
BigDecimal pow(const BigDecimal& a, const unsigned long int n);
BigDecimal pow(const BigDecimal& a, const BigInt& n);

BigDecimal::BigDecimal(){
  this->value = BigInt("0");
  this->scale = BigInt("0");
};

BigDecimal::BigDecimal(const string& num){
  string strnum = num;
  unsigned long int dec_pos = strnum.find('.', 0);
  bool is_negative = false;
  if(strnum.substr(0,1) == "-"){
    is_negative = true;
    strnum = strnum.substr(1,strnum.length());
    dec_pos -= 1;
  }
  if(dec_pos > 0 && dec_pos < strnum.length()){
    unsigned long int s = strnum.length() - dec_pos - 1;
    strnum = strnum.substr(0,dec_pos) + strnum.substr(dec_pos+1,strnum.length());
    while(strnum.substr(0,1) == "0") strnum = strnum.substr(1,strnum.length());
    if(is_negative) strnum = "-" + strnum;
    this->value = BigInt(strnum);
    this->scale = BigInt(s);
  }
  else if(dec_pos == 0){
    if(is_negative) *this = BigDecimal("-0" + strnum);
    else *this = BigDecimal("0" + strnum);
  }
  else{
    if(is_negative) this->value = BigInt("-" + strnum);
    else this->value = BigInt(strnum);
    this->scale = BigInt("0");
  }
};

BigDecimal::BigDecimal(const double& num){
  *this = BigDecimal(to_string(num));
};

BigDecimal::BigDecimal(const BigInt& v, const BigInt& s){
  this->value = v;
  this->scale = s;
};

BigDecimal::~BigDecimal(){
  this->value = BigInt();
  this->scale = BigInt();
};

void BigDecimal::trim(){
  BigInt one = BigInt("1");
  BigInt ten = BigInt("10");
  BigInt remainder = this->value % ten;
  while(remainder.size() == 1 && remainder.back() == 0){
    this->value = this->value / ten;
    this->scale = this->scale - one;
    remainder = this->value % ten;
  }
};

unsigned long int BigDecimal::precision(){
  string val = "";
  BigInt v = this->value;
  while(v.size() > 0){
    val += to_string(v.back());
    v.pop_back();
  }
  return val.length();
};

//Getters
BigInt BigDecimal::getValue() const {
  return this->value;
}

BigInt BigDecimal::getScale() const {
  return this->scale;
}

//Setters
void BigDecimal::setValue(const BigInt& a){
  this->value = a;
};

void BigDecimal::setScale(const BigInt& a){
  this->scale = a;
};

//Operators
BigDecimal BigDecimal::operator =(const BigDecimal& a){
  this->value = a.getValue();
  this->scale = a.getScale();
  return *this;
};

ostream& operator <<(ostream& os, const BigDecimal& a){
  BigDecimal bd = a;
  BigInt v = bd.getValue();
  BigInt s = bd.getScale();
  BigInt zero = BigInt("0");
  BigInt one = BigInt("1");
  string val = "";
  if(v.ifNegative()){
    os << "-";
  }
  while(v.size() > 0){
    val += to_string(v.back());
    v.pop_back();
  }
  BigInt prec = BigInt(to_string(bd.precision()));
  if(s > prec){
    os << "0.";
    BigInt counter = s - prec;
    while(counter > zero){
      os << "0";
      counter = counter - one;
    }
    os << val;
  }
  else if(s > zero){
    BigInt limit = prec - s;
    if(limit > zero){
      for(BigInt i=zero; i<limit; i=i+one){
        os << val.front();
        val = val.substr(1,val.length());
      }
    }
    else{
      os << val.front();
      val = val.substr(1,val.length());
    }
    os << "." << val;
  }
  else os << val;
  return os;
};

void matchScales(BigDecimal& first, BigDecimal& second){
  BigInt s_first = first.getScale();
  BigInt s_second = second.getScale();
  if(s_first < s_second){
    first = first * pow(BigDecimal("10"), s_second - s_first);
    first.setScale(s_second);
  }
  else if(s_first > s_second){
    second = second * pow(BigDecimal("10"), s_first - s_second);
    first.setScale(s_first);
  }
};

BigDecimal operator +(const BigDecimal& first, const BigDecimal& second){
  BigDecimal f_add = first;
  BigDecimal s_add = second;
  matchScales(f_add, s_add);
  BigInt add_value = f_add.getValue() + s_add.getValue();
  BigDecimal addition = BigDecimal(add_value, f_add.getScale());
  return addition;
};

BigDecimal operator -(const BigDecimal& first, const BigDecimal& second){
  BigDecimal f_sub = first;
  BigDecimal s_sub = second;
  matchScales(f_sub, s_sub);
  BigInt sub_value = f_sub.getValue() - s_sub.getValue();
  BigDecimal subtraction = BigDecimal(sub_value, f_sub.getScale());
  return subtraction;
};

BigDecimal operator *(const BigDecimal& first, const BigDecimal& second){
  BigDecimal f = first;
  BigDecimal s = second;
  return BigDecimal((f.getValue()*s.getValue()), (f.getScale()+s.getScale()));
};

bool operator <(const BigDecimal& first, const BigDecimal& second){
  BigDecimal f = first;
  BigDecimal s = second;
  matchScales(f, s);
  return f.getValue() < s.getValue();
};

bool operator >(const BigDecimal& first, const BigDecimal& second){
  BigDecimal f = first;
  BigDecimal s = second;
  matchScales(f, s);
  return f.getValue() > s.getValue();
};

BigDecimal operator /(const BigDecimal& first, const BigDecimal& second){
  BigDecimal f_div = first;
  BigDecimal s_div = second;
  matchScales(f_div, s_div);
  BigInt f_div_v_f = f_div.getValue();
  BigInt s_div_v_f = s_div.getValue();
  f_div_v_f.setNegative(false);
  s_div_v_f.setNegative(false);
  if(f_div_v_f < s_div_v_f){
    unsigned long int max_prec = f_div.precision() + round(s_div.precision()*10/3);
    BigDecimal ten_pow = BigDecimal(pow(BigInt("10"), max_prec), BigInt("0"));
    BigDecimal f_div2 = f_div * ten_pow;
    BigInt div_v = f_div2.getValue() / s_div.getValue();
    BigInt div_s = f_div.precision() + BigDecimal(div_v, BigInt("0")).precision();
    return BigDecimal(div_v, div_s);
  }
  else if(f_div_v_f > s_div_v_f){
    BigInt div_v = f_div.getValue() / s_div.getValue();
    BigInt div_s = f_div.getScale();
    return BigDecimal(div_v, div_s);
  }
  else return BigDecimal("1");
};

BigDecimal operator %(const BigDecimal& first, const BigDecimal& second){
  BigDecimal zero = BigDecimal("0");
  BigInt zero_bint = BigInt("0");
  BigDecimal f = first;
  BigDecimal s = second;
  BigInt f_v = f.getValue();
  BigInt s_v = s.getValue();
  BigInt f_s = f.getScale();
  BigInt s_s = s.getScale();
  if(f_s > zero_bint) return zero;
  else if(s_s > zero_bint) return zero;
  BigInt mod_v = f_v % s_v;
  return BigDecimal(mod_v, zero_bint);
};

//n must be positive
BigDecimal pow(const BigDecimal& a, const unsigned long int n){
  BigDecimal one = BigDecimal("1");
  if(n == 0) return one;
  unsigned long int z = n;
  BigDecimal x = a;
  BigDecimal y = one;
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

//n must be positive
BigDecimal pow(const BigDecimal& a, const BigInt& n){
  BigDecimal one = BigDecimal("1");
  if(n.size() == 1 && n.back() == 0) return one;
  BigDecimal x = a;
  BigDecimal y = one;
  BigInt z = n;
  BigInt one_bint = BigInt("1");
  BigInt mod = one_bint;
  BigInt two_bint = BigInt("2");
  while(z > one_bint){
    mod = z % two_bint;
    if(mod.size() == 1 && mod.back() == 0){
      x = x * x;
      z = z / two_bint;
    }
    else{
      y = x * y;
      x = x * x;
      z = (z - one_bint) / two_bint;
    }
  }
  return x * y;
};
