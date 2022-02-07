#include<iostream>

using std::cout;
using std::endl;

int main() {

  for (unsigned i = 0; i < 4300000000; i++) {
    if (i % 100000000 == 0) 
      cout << i << endl;
  }
  return 0;
}
