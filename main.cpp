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
  cout << endl << t1 << endl;

  //BigNum t2 = BigNum("10000") - BigNum("9999");
  //cout << t2 << endl;

  //BigNum x = pow(BigNum("2"),10000);
  //cout << x << endl;

  return 0;
}
