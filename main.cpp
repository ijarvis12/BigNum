#include <iostream>
#include "bignum.h"
using namespace std;

int main(){
  //Initializer Tests
  BigNum i1 = BigNum();
  cout << i1 << endl;

  BigNum i2 = BigNum("1010101010");
  cout << i2 << endl;

  BigNum i3 = BigNum(1000000100);
  cout << i3 << endl;

  cout << endl;

  //Operator Tests
  BigNum t1 = BigNum("999999999") + BigNum("1");
  cout << t1 << endl;

  BigNum t2 = BigNum("1000000000") - BigNum("999999999");
  cout << t2 << endl;

  BigNum t3 = BigNum("9999999999") * BigNum("333");
  cout << t3 << endl;

  BigNum t4 = pow(BigNum("2"),36);
  cout << t4 << endl;

  BigNum t5 = BigNum("9999999999") / BigNum("333");
  cout << t5 << endl;

  BigNum t6 = BigNum("9999999999999999") % BigNum("3333333333");
  cout << t6 << endl;

  return 0;
}
