/* 
 * This program illustrates program bugs integer representation
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 09/20/21 
 */

#include<iostream>
#include<vector>

using namespace std;

const int NUMS = 100;
const int RAND_RANGE_POPULATION = 20;
const int RAND_RANGE_SEARCH = 100;

int main() {

  std::vector<int> nums;
  srand(time(0));

  /* populate vector with random integers in the range 0..RAND_RANGE_POPULATION */
  for (unsigned i = 0; i < NUMS; i++) {
    int num = rand() % RAND_RANGE_POPULATION;
    nums.push_back(num);
  }

  /* will search for an integer in the range 0..RAND_RANGE_SEARCH  */
  int num_to_search = rand() % RAND_RANGE_SEARCH;
  cout << "Searching for ... " << num_to_search << endl;

  /* linear search in vector of integers */
  bool found = false;
  int found_index = -1;
  for (unsigned i = nums.size() - 1; i >= 0; i--) {
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

