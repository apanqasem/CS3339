/* 
 * Example of loop blocking to mitigate capacity misses. 
 * 
 * @author: Apan Qasem 
 * @date: 03/31/21
 */
#include<stdlib.h>
#include<stdio.h>

/* number of times task is to be repeated */
#define N 1000 

int main(int argc, char *argv[]) {
  float **a, **b;
  
  /* get array dimensions from command-line */
  int dim = atoi(argv[1]);

  /* get block size from command-line; should be selected so that working set fits in cache  */
  int BLOCK = atoi(argv[2]);

  /* memory allocation */
  a = (float **) malloc(sizeof(float *) * dim);
  b = (float **) malloc(sizeof(float *) * dim);

  int i,j,k;
  for (i = 0; i < dim; i++)  {
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
  /* tiled sweep over a and b */
  int jj;
  for (j = 0; j < dim; j = j + BLOCK)
    for (k = 0; k < N; k++)
      for (i = 0; i < dim; i++)
	for (jj = j; jj < (j + BLOCK); jj++) 
	  a[i][jj] = b[i][jj] * scale;
   
  printf("a[17][17] = %3.2f\n",a[17][17]);

  return 0;

}
