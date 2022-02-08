/* 
 * This program illustrates program bugs in integer representation
 * 
 * @author: Apan Qasem <apan@txstate.edu>
 * @date: 02/08/22
 *
 * 1. Compile and run the code with a few different values. Do you see the bug?
 * 2. Study the code and identify the cause for this bug (use your understanding of 
 *    number representation from Lec 4)
 * 3. Fix the bug.
 */

#include<iostream>
#include<vector>

using std::cout;
using std::endl;

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

