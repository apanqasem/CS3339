/*
 * (naive) parallel implementation of RankSort algorithm 
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 04/02/20 
 */


#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define VAL_RANGE 1024

/* 
 * apply rank sort to values and place sorted values in sorted_values 
 */
void ranksort(double *values, long long N, double *sorted_values) {

  unsigned *ranks = (unsigned *) malloc(sizeof(unsigned) * N);
  // find ranks 
  int i, j;
  for(i = 0; i < N; i++) {
    for(j = 0; j < i; j++) {
      if(values[i] >= values[j])
	ranks[i]++;
      else
	ranks[j]++;
    }	
  }	

  // sort values
  #pragma omp parallel for 
  for(i = 0; i < N; i++)
    sorted_values[ranks[i]] = values[i];
  
  return;
}

void display(double *values, long long N) {
  int i;
  for(i = 0; i < N; i++)
    printf("%3.2f ", values[i]);
  printf("\n");			
  return;
}

int main(int argc, char* argv[]) {

  if (argc < 3) {
    printf("usage: \n");
    printf("       ./ranksort N threads\n");
    exit(0);
  }
  
  long long N = atoi(argv[1]);
  unsigned threads = atoi(argv[2]);

  
  // number of threads to be used in the parallel run 
  omp_set_num_threads(threads);

  double *values = (double *) malloc(sizeof(double) * N);
  double *sorted_values = (double *) malloc(sizeof(double) * N);

  for (int i = 0; i < N; i++) 
    values[i] = rand() / (double) (RAND_MAX/VAL_RANGE);

  ranksort(values, N, sorted_values);
  printf("result = %3.2f\n", sorted_values[N - 1]);
}
