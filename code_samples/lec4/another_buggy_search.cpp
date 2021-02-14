#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;

const unsigned NUMS = 2.2e+9;
const unsigned NUM_RANDS = 1000;
const unsigned RAND_RANGE_POPULATION = 20;
const unsigned RAND_RANGE_SEARCH = 100;

int main() {

  int *nums = new int[NUMS];
  int *rands = new int[NUM_RANDS];
  srand(time(0));
  
  cout << "Generating rands..." << endl;
  for (unsigned i = 0; i < NUM_RANDS; i++) {
    int num = rand() % RAND_RANGE_POPULATION;
    rands[i] = num;
  }

  cout << "Copying ..." << endl;
  for (unsigned i = 0; i < NUMS; i = i + NUM_RANDS) {
    for (unsigned j = 0; j < NUM_RANDS; j++) {
      nums[i + j] = rands[j];
    }    
  }  
  int num_to_search = rand() % RAND_RANGE_SEARCH;

  cout << "Searching ..." << endl;
  bool found = false;
  int found_index = -1;
  for (int i = 0; i < NUMS; i++) {
    if (num_to_search == nums[i]) {
      found = true;
      found_index = i;
      break;
    }
  }

  if (found)
    cout << "Found " << num_to_search << " at position " << found_index << endl;
  else 
    cout << "Didn't find number: " << num_to_search << endl;

  return 0;
  
}

