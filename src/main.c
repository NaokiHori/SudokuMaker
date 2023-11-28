#include <stdio.h>
#include <stdlib.h>
#include "general.h"

static int print (
    const char tag[],
    const size_t * vals
) {
  puts(tag);
  for (size_t n = 0; n < BOARD_SIZE * BOARD_SIZE; n++) {
    const size_t val = vals[n];
    if (0 == val) {
      printf("  ");
    } else {
      printf("%2zu", val);
    }
    printf(BOARD_SIZE - 1 == n % BOARD_SIZE ? "\n" : " ");
  }
  return 0;
}

int main (
    int argc,
    char * argv[]
) {
  const unsigned seed = 1 == argc ? 1 << 12 : strtol(argv[1], NULL, 10);
  printf("seed: %u\n", seed);
  srand(seed);
  size_t vals[BOARD_SIZE * BOARD_SIZE] = {0};
  if (0 != find_one_solution(vals)) {
    puts("ERROR: failed to create a filled board");
    return 1;
  }
  print("answer:", vals);
  create_a_puzzle(vals);
  print("question:", vals);
  size_t nsols = 0;
  count_nsols(vals, &nsols);
  if (1 != nsols) {
    printf("ERROR: %zu answers exist:\n", nsols);
    return 1;
  }
  return 0;
}

