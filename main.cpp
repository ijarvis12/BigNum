#include <iostream>
#include "bignum.h"
using namespace std;

int main(){
  //Initializer Tests
  BigNum i1 = BigNum();
  cout << i1 << endl;

  BigNum i2 = BigNum("10101010");
  cout << i2 << endl;

  BigNum i3 = BigNum(1000000100);
  cout << i3 << endl;

  //Operator Tests
  BigNum t1 = BigNum("2222") + BigNum("9999");
  cout << t1 << endl;

  BigNum t2 = BigNum("10000") - BigNum("9999");
  cout  << t2 << endl;

  BigNum t3 = BigNum("99999") * BigNum("333");
  cout << t3 << endl;

  BigNum t4 = pow(BigNum("2"),20);
  cout << t4 << endl;

  return 0;
}
