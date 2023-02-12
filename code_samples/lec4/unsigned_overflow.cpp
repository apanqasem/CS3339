/* 
 * This program illustrates arithmetic overflow of unsigned integers
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 02/08/23
 * 
 * 
 * 1. Without running the code, guess the output of this code. 
 * 2. Compile and run the code and check answers. Did you guess correctly?
 * 3. What does it say about unsigned int storage?
 * 4. What does it say about overflow handling on your target architecture?? 
 */


#include<iostream>

using std::cout;
using std::endl;

int main() {

  unsigned max = 4294967295;
  unsigned min = 0;
  
  cout << "MAX = " << max + 1 << endl;
  cout << "MIN = " << min - 1 << endl;
  
  return 0;
}
