long HUGE = 4000000001;

int main() {
  int *my_huge_array = new int[HUGE];
  for (int i = 0; i < HUGE; i++)
    my_huge_array[i] = 17;

  return 0;
}

