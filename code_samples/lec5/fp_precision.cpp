/* 
 * This program illustrates issues associated with floating-point representation
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 02/08/22
 * 
 * 
 * 1. Study the code. What is the expected output? 
 * 2. Compile and run the code. Is the output what you expected? 
 * 3. Can you identify the bug? (use your knowledge of FP representation from Lec 5)
 * 4. Fix the bug. 
 */

#include<iostream>

using namespace std; 

const float LOOP_BOUND = 1e+08;               // hundred million 
const unsigned long PRINT_INTERVAL = 1e+06;   // one million

int main(int argc, char *argv[]) {

  unsigned i = 0; 
  unsigned j = 0;
  while (i  <= LOOP_BOUND) {
    // print counter value every millionth iteration
    if (j % PRINT_INTERVAL == 0)
      cout << i << endl;
    i++;
    j++;
  }

  return 0;
}
