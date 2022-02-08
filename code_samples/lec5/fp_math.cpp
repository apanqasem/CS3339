/* 
 * This program illustrates issues associated with floating-point representation
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 02/08/22
 * 
 * 
 * 1. Study the code. What is the expected output? 
 * 2. Compile and run the code. Is the output what you expected? 
 * 3. Can you explain why we are getting this output? (use your knowledge of FP representation from Lec 5)
 */

#include<iostream>

using namespace std; 

int main() {

  float x = -1e+14;
  float y = 1e+14;
  float z = 1.00; 

  cout << x + y + z << endl;
  cout << (x + y) + z << endl;
  cout << x + (y + z) << endl;

  return 0;

}
