/* 
 * Simple example code that illustrates capacity misses. 
 * 
 * @author: Apan Qasem 
 * @date: 03/31/21
 */
#include<stdlib.h>
#include<stdio.h>

/* number of times task is to be repeated */
#define N 100 

int main(int argc, char *argv[]) {
  float **a, **b;

  /* get array dimensions from command-line */
  int dim = atoi(argv[1]);

  /* memory allocation */
  a = (float **) malloc(sizeof(float *) * dim);
  b = (float **) malloc(sizeof(float *) * dim);
  
  int i,j,k;
  for (i = 0; i < dim; i++) {
    a[i] = (float *) malloc(sizeof(float) * dim);
    b[i] = (float *) malloc(sizeof(float) * dim);
  }
  
  /* initialization */
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++) { 
      a[i][j] = 2.3;
      b[i][j] = 1.7;
    }

  float scale = 0.17;
  /* sweep over arrays A and B, N times; working set = size of arrays A and B
     if working set > cache capacity, then will observe capacity misses in every iteration */ 
  for (k = 0; k < N; k++)
    for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	a[i][j] = b[i][j] * scale;


  printf("a[17][17] = %3.2f\n",a[17][17]);

  return 0;

}
