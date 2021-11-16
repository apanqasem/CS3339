#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#include <omp.h>

#define REPS 100

double t0;
double mysecond() {
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int main(int argc, char *argv[]) {
  float **a, **b;
  
  int M = atoi(argv[1]);
  int N = atoi(argv[2]);

  omp_set_num_threads(N);

  a = (float **) malloc(sizeof(float *) * M);
  b = (float **) malloc(sizeof(float *) * M);
  
  int i, j, k;
  for (i = 0; i < M; i++) {
    a[i] = (float *) malloc(sizeof(float) * M);
    b[i] = (float *) malloc(sizeof(float) * M);
  }

  for (j = 0; j < M; j++)
    for (i = 0; i < M; i++)
      b[i][j] = i + j;

  t0 = mysecond();
  //#pragma omp parallel for 
  for (int k = 0; k < REPS; k++) {
    for (int j = 0; j < M; j++) 
#pragma omp parallel for 
      for (int i = 0; i < M; i++)
        a[i][j] = b[i][j] * 17;
  }

  t0 = (mysecond() - t0) * 1.e3;

  /* print an arbirtrary value from the result array */
  printf("result = %3.2f\n", a[17][17]);
  printf("parallel loop = %3.2f ms\n", t0);

  return 0;

}
