#include<stdio.h>
#include<limits.h>

int main() {

  int x;
  printf("char = %lu\n", sizeof(char));
  printf("short = %lu\n", sizeof(short));
  printf("int = %lu\n", sizeof(int));
  printf("unsigned int = %lu\n", sizeof(unsigned int));
  printf("long = %lu\n", sizeof(long));
  printf("int* = %lu\n", sizeof(int *));
  printf("long long = %lu\n", sizeof(long long));
  printf("MAX_INT = %d\n", INT_MAX);
  printf("MAX_LONG = %lu\n", LONG_MAX);
  //  printf("MAX_LONG = %lld\n", LONG_LONG_MAX);
  return 0;
}


