#include<iostream>

const int N = 100;

using namespace std;

int squared(int x, int* &result_loc) {
  int result = x * x;
  result_loc = &result;
  cout << (unsigned long) result_loc << ": ";
  cout << *result_loc << endl;
  return 0;
}

int squared_other(int x, int* &result_loc) {
  int result;
  cout << (unsigned long) &result << ": ";
  cout << result << endl;
  result = x * x;
  result_loc = &result;
  return 0;
}


int main() {

  int *result;
  int error_code = squared(4, result);  
  cout << (unsigned long) result << ": ";
  cout << *result << endl;

  error_code = squared_other(3, result);  
  cout << (unsigned long) result << ": ";
  cout << *result << endl;
  
  return 0;
}
