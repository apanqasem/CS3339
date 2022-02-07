#include<iostream>

const int DATA_SIZE_A = 1000;
const int DATA_SIZE_B = 1000000;

int main() {

  int *A = new int(DATA_SIZE_A);
  int *B = new int(DATA_SIZE_B);

  for (int i = 0; i < DATA_SIZE_A; i++)
    A[i] = i + 17;

  for (int i = 0; i < DATA_SIZE_B; i++)
    B[i] = A[i];
  
  return 0;
}
