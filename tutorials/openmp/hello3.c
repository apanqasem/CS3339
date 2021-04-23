#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char* argv[]) {
  omp_set_num_threads(4);

#pragma omp parallel 
  { 
    printf("Hello World\n");
    printf("Goodbye World!\n");
  }
  return 0;
}
