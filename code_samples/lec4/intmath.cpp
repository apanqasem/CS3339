/* 
 * This program illustrates integer arithmetic overflow
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 02/08/22
 * 
 * 
 * 1. Without running the code, guess the output of this code. 
 * 2. Compile and run the code and check answers. Did you guess correctly?
 * 3. What does it say about the behavior of the ++ and -- operator?
 * 4. What does it say about int storage and overflow handling? 
 */

#include<iostream>
#include<limits>

using std::cout;
using std::endl;

int main() {

  int myLargeInt = 2147483647;

  cout << myLargeInt++ << endl;
  cout << myLargeInt << endl;
  cout << --myLargeInt << endl;
  
  return 0;
  
}
