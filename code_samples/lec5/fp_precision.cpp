#include<iostream>

using namespace std; 

const float LOOP_BOUND = 1e+08;               // hundred million 
const unsigned long PRINT_INTERVAL = 1e+06;   // one million

int main(int argc, char *argv[]) {

  unsigned long i = 0; 
  int j = 0;
  while (i  <= LOOP_BOUND) {
    // print counter value every millionth iteration
    if (j % PRINT_INTERVAL == 0)
      cout << i << endl;
    i++;
    j++;
  }

  return 0;
}
