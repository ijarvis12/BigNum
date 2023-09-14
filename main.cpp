#include <iostream>
#include "bigdecimal.h"
using namespace std;

int main(){
  //Initializer Tests
  cout << "Initializer Tests for BigInt" << endl;

  BigInt i1 = BigInt();
  cout << i1 << endl;

  BigInt i2 = BigInt("-12345678901234567890");
  cout << i2 << endl;

  BigInt i3 = BigInt(-1234567890);
  cout << i3 << endl;

  cout << endl << "Initializer Tests for BigDecimal" << endl;

  BigDecimal i4 = BigDecimal();
  cout << i4 << endl;

  BigDecimal i5 = BigDecimal("-0.00123456789");
  cout << i5 << endl;

  BigDecimal i6 = BigDecimal("-123456.789");
  cout << i6 << endl;

  BigDecimal i7 = BigDecimal("1234567890000");
  cout << i7 << endl;

  cout << endl;

  //Operator Tests
  cout << "Operator Tests for BigInt" << endl;

  BigInt t1 = BigInt("999999999") + BigInt("1");
  cout << t1 << endl;

  BigInt t2 = BigInt("1000000000") - BigInt("999999999");
  cout << t2 << endl;

  BigInt t3 = BigInt("9999999999") * BigInt("333");
  cout << t3 << endl;

  BigInt t4 = BigInt("9999999999") / BigInt("-3333333");
  cout << t4 << endl;

  BigInt t5 = BigInt("9999999999999999") % BigInt("-3333333333");
  cout << t5 << endl;

  BigInt t6 = pow(BigInt("2"), 36);
  cout << t6 << endl;

  cout << endl << "Operator Tests for BigDecimal" << endl;

  BigDecimal t7 = BigDecimal("0.1") + BigDecimal("0.01");
  cout << t7 << endl;

  BigDecimal t8 = BigDecimal("0.1") - BigDecimal("0.01");
  cout << t8 << endl;

  BigDecimal t9 = BigDecimal("0.00625") * BigDecimal("0.002");
  cout << t9 << endl;

  BigDecimal t10 = BigDecimal("1") / BigDecimal("16");
  cout << t10 << endl;

  BigDecimal t11 = BigDecimal("36") % BigDecimal("2");
  cout << t11 << endl;

  BigDecimal t12 = pow(BigDecimal("0.1"), 36);
  cout << t12 << endl;

  return 0;
}
