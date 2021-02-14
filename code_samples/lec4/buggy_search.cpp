#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;

const int NUMS = 100;
const int RAND_RANGE_POPULATION = 20;
const int RAND_RANGE_SEARCH = 100;

int main() {

  std::vector<int> nums;
  srand(time(0));
  
  for (unsigned i = 0; i < NUMS; i++) {
    int num = rand() % RAND_RANGE_POPULATION;
    nums.push_back(num);
  }

  int num_to_search = rand() % RAND_RANGE_SEARCH;

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

