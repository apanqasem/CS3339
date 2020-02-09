#include<stdio.h>
#include<limits.h>

int main() {
 
  /* memory space taken up by different forms of integer data */
  printf("Memory space taken up different integer data types in C++\n\n");
  printf("\tchar = %lu Bytes\n", sizeof(char));
  printf("\tshort = %lu Byets\n", sizeof(short));
  printf("\tint = %lu Bytes\n", sizeof(int));
  printf("\tunsigned int = %lu Bytes\n", sizeof(unsigned int));
  printf("\tlong = %lu Bytes\n", sizeof(long));
  printf("\tlong long = %lu Bytes\n\n", sizeof(long long));

  /* amount of memory occupied by a pointer */
  printf("Memory space taken up by a pointer data type\n\n");
  printf("\tint* = %lu Bytes\n\n", sizeof(int *));

  /* range of values that can be represented with different integer data types */
  printf("Range of values that can be represented with integer data types\n\n");
  printf("\tMAX_INT = %d\n", INT_MAX);
  printf("\tMAX_UINT = %u\n", UINT_MAX);
  printf("\tMAX_LONG = %lu\n", LONG_MAX);
  printf("\tMAX_LONG_LONG = %lld\n\n", LONG_LONG_MAX);
  return 0;
}

/* 
 *
 *  1. Will this code compile?
 *
 *  2. What does the sizeof() function return? Have you ever had to use it?
 *
 *  3. From a programmer's perspective, what is the difference between int and long?
 *
 *  4. From a programmer's perspective, what is the difference between long and long long?
 *
 *  5. Write down what you expect from each line of output. 
 *
 */
