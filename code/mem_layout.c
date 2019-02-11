/* 
 * This program illustrates how program data and code is laid out in memory
 * 
 * Edit the program to print out the memory addresses for the following 
 * 
 *  1. Base address of global array x
 *  2. Address of second element in global array x 
 *  3. Address of local variable i in main() 
 *  4. Address of local variable y in main() 
 *  5. Beginning address of malloc's array y
 *  6. Address of second element of malloc's array y
 *  7. Address of local variable i in foo()
 *  8. Address of parameter p in foo()
 *  9. Address of bar()  
 * 
 *
 * Examine the output and try to answer the following questions 
 * 
 * 1. What is the difference between (1) and (2)? What is the difference between (5) and (6)? 
 *     Are these numbers reasonable? Why?
 * 2. What is the difference between (1) and (5)? Why?
 * 3. What is the difference between (4) and (5)? Why?
 * 4. What is the difference between (7) and (8)? Why?
 * 5. What is the difference between (3) and (7)? Why?
 */ 


#include<stdio.h>
#include<stdlib.h>

#define N 100

double x[N];

void bar(int x) {
  return;
}

void foo(int p) {
  int i;
  for (i = 1; i <= N; i++) {
    x[i] = p * x[i - 1] + 3;
  }
  bar(p); 
}
 

int main() {
  
  int i;
  for (i = 0; i < N; i++) {
    x[i] = i;
  }
    
  int *y = (int *) malloc(sizeof(int) * N);

  y[17] = 17;
  foo(y[17]);

  fprintf(stdout, "global x = %lu\n", (void *) &x);
  
  return 0;
}
