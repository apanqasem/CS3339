/* 
 * (naive) parallel implementation of quicksort algorithm 
 * Program is meant to be used for class project in CS3339: Computer Architectere
 *
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 04/02/20 
 */


#include<iostream>
#include<omp.h>

using namespace std; 

const int VAL_RANGE = 1024;

/*
 * partition array for quicksort
 *     - move pivot to far right
 *     - accumulate values smaller than pivot to the left
 */
int partition(double values[], int left, int right, int pivotIndex) {
  int pivotValue = values[pivotIndex];
  swap(values[pivotIndex],values[right]);  // Move pivot to end
  int storeIndex = left;
  for(int i = left; i < right; i++) {
    if (values[i] < pivotValue) {
      swap(values[i],values[storeIndex]);
      storeIndex++;
    }
  }
  swap(values[storeIndex],values[right]);  // Move pivot to its final place
  return storeIndex;
}

/* 
 * recursive quicksort 
 */ 
int quickSort(double values[], int left, int right) {
  if (left < right) {
    int pivotIndex = (left + right)/2;
    
    int pivotNewIndex = partition(values, left, right, pivotIndex);
    // recurse in parallel 
    #pragma parallel {
    int num = omp_get_thread_num();
    if (num % 2)
      quickSort(values, left, pivotNewIndex - 1);
    else 
      quickSort(values, pivotNewIndex + 1, right);
   }
}

/* 
 * display array contents 
 */

void display(double values[], long long N) {
  for (int i = 0; i < N; i++)
    cout << values[i] << " ";
  cout << endl;
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    printf("usage: \n");
    printf("       ./quicksort N threads\n");
    exit(0);
  }
  
  long long N = atoi(argv[1]);
  unsigned threads = atoi(argv[2]);

  // number of threads to be used in the parallel run 
  omp_set_num_threads(threads);
  
  double *values = (double *) malloc(sizeof(double) * N);

  for (int i = 0; i < N; i++) 
    values[i] = rand() / (double) (RAND_MAX/VAL_RANGE);

  
  quickSort(values, 0, N - 1);

  cout << "results = " << values[N-1] << endl;
  
  return 0;
}

 
