/* 
 * This program illustrates how program data and code is laid out in memory
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 09/14/21 
 */


#include<iostream>
#include<iomanip>

using namespace std;


const int N = 100;

/* output formatting */
const int WIDTH_COL_ONE = 38;
const int WIDTH_COL_TWO = 16;


double x[N];

void bar(int x) {
  return;
}

void foo(int p) {
  int i;
  for (i = 1; i <= N; i++) 
    x[i] = p * x[i - 1] + 3;
  bar(p); 
}
 

int main() {
  
  int i;
  for (i = 0; i < N; i++) {
    x[i] = i;
  }
    
  int *y = new int[N];

  y[17] = 17;
  foo(y[17]);

  cout << left << setw(WIDTH_COL_ONE) << "Global array x: "
       << setw(WIDTH_COL_TWO) << right << (unsigned long) &x << endl;

  return 0;
}


/*
 * Edit the program to print out the memory addresses for the following 
 * 
 *  1. Beginning address of global array x [ this is done already ]
 *  2. Address of second element in global array x 
 *  3. Address of local variable i in main() 
 *  4. Address of local variable y in main() 
 *  5. Beginning address of malloc's array y
 *  6. Address of second element of malloc's array y
 *  7. Address of local variable i in foo()
 *  8. Address of parameter p in foo()
 *  9. Address of bar()  
 * 10. Address of cout()
 *
 * Examine the output and try to answer the following questions 
 * 
 * A. What is the difference between (1) and (2)? What is the difference between (5) and (6)? 
 *    Are these numbers reasonable? Why?
 * 
 * B. What is the difference between (1) and (5)? Why?
 * C. What is the difference between (4) and (5)? Why?
 * D. What is the difference between (7) and (8)? Why?
 * E. What is the difference between (3) and (7)? Why?
 */ 
