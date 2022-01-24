/* 
 * This program illustrates integer arithmetic overflow
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 09/20/21 
 */

#include<iostream>
#include<limits>

using namespace std;

int main() {

  int myLargeInt = 2147483647;

  cout << myLargeInt++ << endl;
  cout << myLargeInt << endl;
  cout << --myLargeInt << endl;
  
  return 0;
  
}
