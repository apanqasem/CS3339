/* 
 * This program illustrates how program data and code is laid out in memory
 * 
 * @author: Apan Qasem 
 * @date: 02/06/22
 *
 * Edit the program to print out the memory addresses for the following (i.e., replace FILL_THIS_IN 
 * in the cout statements with C++ code to print out the appropriate address)
 * 
 *  1. Beginning address of global array x [ this is done already ]
 *  2. Address of second element in global array x 
 *  3. Address of local variable i in main() 
 *  4. Address of local variable y in main() 
 *  5. Beginning address of dynamic array y
 *  6. Address of second element of dynamic array y
 *  7. Address of local variable i in foo()
 *  8. Address of parameter p in foo()
 *  9. Address of bar()  
 * 10. Address of cout()
 * 
 * If you are unsure about the syntax of any of the items, just leave it and comment
 * and comment the corresponding cout statement 
 * 
 * Compile and run the code. Examine the output and try to answer the questions at the bottom. 
 */
#include<iostream>
#include<iomanip>

using namespace std;

const int N = 100;

/* output formatting */
const int WIDTH_COL_ONE = 38;
const int WIDTH_COL_TWO = 16;

/* global array */
double x[N];

void bar(int x) {
  return;
}

void foo(int p) {
  int i;
  cout << left << setw(WIDTH_COL_ONE) << "7. Local variable i in foo(): "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;
  cout << left << setw(WIDTH_COL_ONE) << "8. Paramemter p in foo(): "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;

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

  cout << left << setw(WIDTH_COL_ONE) << "1. Global array x: "
       << setw(WIDTH_COL_TWO) << right << (unsigned long) &x << endl;
  cout << left << setw(WIDTH_COL_ONE) << "2. Second element in global array x: "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN  << endl;
    
  cout << left << setw(WIDTH_COL_ONE) << "3. Local variable i in main(): "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;
  cout << left << setw(WIDTH_COL_ONE) << "4. Local variable y in main(): "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;

  cout << left << setw(WIDTH_COL_ONE) << "5. Start address of dynamic array y: "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;
  cout << left << setw(WIDTH_COL_ONE) << "6. Second element of dynamic array y: "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;
  
  foo(y[17]);

  cout << left << setw(WIDTH_COL_ONE) << "9. Address of bar(): "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;
  cout << left << setw(WIDTH_COL_ONE) << "10. Address of cout: "
       << setw(WIDTH_COL_TWO) << right << FILL_THIS_IN << endl;

  return 0;
}

/*
 *
 * Examine the output and try to answer the following questions 
 * 
 * A. What is the difference between (1) and (2)? What is the difference between (5) and (6)? 
 *    What does this tell us about memory allocation of different of data types? [ more on this in next class ]
 * B. What is the difference between (1) and (5)? What does this tell us about where x and y are allocated?
 * C. What is the difference between (4) and (5)? What does this tell us about allocation pointer y and array y?
 * D. What is the difference between (7) and (8)? What does this tell us about local vairable and parameter allocation? 
 * E. What is the difference between (3) and (7)? What does this tell us about memory allocation for functions?
 */ 


