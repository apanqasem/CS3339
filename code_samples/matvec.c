#include<stdio.h>
#include<stdlib.h>

#define VAL_RANGE 1023

double dot_prod(double *x, double *y, int n) {
  double res = 0.0;
  int i;
  for (i = 0; i < n; i++)
      res += x[i] * y[i];
  return res;
}

void matrix_vector_mult(double **mat, double *vec, double *result, 
			long long rows, long long cols) { 
  int i;
  for (i = 0; i < rows; i++)
    result[i] = dot_prod(mat[i], vec, cols);
}

void display_matrix(const double **matrix, long long N) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) 
      printf("%3.4f ", matrix[i][j]);
    printf("\n");
  }
}
int main(int argc, char *argv[]) {

  double **matrix;
  double *vec;
  double *result;

  if (argc < 3) {
    printf("usage: \n");
    printf("       ./matvec N n\n");
    exit(0);
  }

  long long N = atoi(argv[1]);
  unsigned n = atoi(argv[2]);
  int i, j;


  matrix = (double **) malloc(sizeof(double *) * N);
  for (i = 0; i < N; i++)
    matrix[i] = (double *) malloc(sizeof(double) * N);


  vec = (double *) malloc(sizeof(double) * N);
  result = (double *) malloc(sizeof(double) * N);

  for (i = 0; i < N; i++) 
    for (j = 0; j < N; j++) 
      matrix[i][j] = rand() / (double) (RAND_MAX/VAL_RANGE);
     
  for (i = 0; i < N; i++)
    vec[i] = rand() / (double) (RAND_MAX/VAL_RANGE);
  
  for (i = 0; i < n; i++)
    matrix_vector_mult(matrix, vec, result, N, N);
  
  printf("%3.4f\n", result[N - 1]);

  return 0;
}
