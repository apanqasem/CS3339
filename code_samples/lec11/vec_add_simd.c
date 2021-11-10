/* 
 * Vector-addition: Adds elements in two double-precision vectors and stores the result in another vector
 * 
 * Demo of OpenMP simd directive
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#include <omp.h>

#define REPS 1000

double t0;

/* inline timer with micro-second precision */
double mysecond() {
  struct timeval tp;
  struct timezone tzp;
  int i;
  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int main(int argc, char *argv[]) {
  
  int num_threads;
  if (argc < 3) {
    fprintf(stderr, "Usage: ./sum_reduce M N\n");
    fprintf(stderr, "    M = size of vectors\n");
    fprintf(stderr, "    N = number of threads\n");
    exit(0);
  }

  int M = atoi(argv[1]);  // size of vectors 
  int N = atoi(argv[2]);  // number of OpenMP threads

  double*a, *b, *c;
  a = (double*) malloc(sizeof(double) * M);
  b = (double*) malloc(sizeof(double) * M);
  c = (double*) malloc(sizeof(double) * M);
  
  int i, j, k;
  for (i = 0; i < M; i++) {
    a[i] = i; 
    b[i] = i * 3.14; 
  }

  omp_set_num_threads(N);

  double sum = 0;
  t0 = mysecond();
  for (j = 0; j < REPS; j++) {
#pragma omp simd
    for (i = 0; i < M; i++)
	c[i] =  a[i] + b[i];
  }
  t0 = (mysecond() - t0) * 1.e3;

  fprintf(stdout, "result = %4.3f\n", c[M-1]);
  fprintf(stdout, "parallel loop = %3.2f ms\n", t0);

  return 0;

}
