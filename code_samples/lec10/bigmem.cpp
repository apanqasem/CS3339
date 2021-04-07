const long HUGE = 4000000001;

int main() {
  int *my_huge_array = new int[HUGE];
  for (long i = 0; i < HUGE; i++)
    my_huge_array[i] = 17;
}

