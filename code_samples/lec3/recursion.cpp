#include<iostream>

using std::cout;
using std::cerr;
using std::endl;

unsigned recursive_sum_even (int n) {
  if (n == 0)
    return 0;
  else
    return n + recursive_sum_even(n - 2);
}


int main(int argc, char*argv[]) {

  if (argc < 2) {
    cerr << "Usage: " << endl;
    cerr << "   ./recursive_sum_even integer" << endl;
    exit(0);
  }

  int n = atoi(argv[1]);
  int result = recursive_sum_even(n);
  cout << "Sum = " << result << endl;
  return 0;

}
