#include<stdlib.h>
#include<stdio.h>

#define DIMSIZE 30000

int main() {
  int **a;
  
  a = (int **) malloc(sizeof(int *) * DIMSIZE);
  
  int i, j;
  for (i = 0; i < DIMSIZE; i++) 
    a[i] = (int *) malloc(sizeof(int) * DIMSIZE);


  for (j = 0; j < DIMSIZE; j++) 
    for (i = 0; i < DIMSIZE; i++)
      a[i][j] = i + 17;


  
  return 0;

}
