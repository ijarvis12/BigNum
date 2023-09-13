#include <iostream>
#include "bigint.h"
using namespace std;

int main(){
  //Initializer Tests
  BigInt i1 = BigInt();
  cout << i1 << endl;

  BigInt i2 = BigInt("-12345678901234567890");
  cout << i2 << endl;

  BigInt i3 = BigInt(-1234567890);
  cout << i3 << endl;

  cout << endl;

  //Operator Tests
  BigInt t1 = BigInt("999999999") + BigInt("1");
  cout << t1 << endl;

  BigInt t2 = BigInt("1000000000") - BigInt("999999999");
  cout << t2 << endl;

  BigInt t3 = BigInt("9999999999") * BigInt("333");
  cout << t3 << endl;

  BigInt t4 = BigInt("9999999999") / BigInt("3333333");
  cout << t4 << endl;

  BigInt t5 = BigInt("9999999999999999") % BigInt("3333333333");
  cout << t5 << endl;

  BigInt t6 = pow(BigInt("2"),36);
  cout << t6 << endl;

  return 0;
}
