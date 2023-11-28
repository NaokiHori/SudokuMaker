#include "general.h"

int create_a_puzzle (
    size_t * vals
) {
  // decide order to visit
  size_t indices[BOARD_SIZE * BOARD_SIZE] = {0};
  for (size_t n = 0; n < BOARD_SIZE * BOARD_SIZE; n++) {
    indices[n] = n;
  }
  shuffle(BOARD_SIZE * BOARD_SIZE, indices);
  for (size_t n = 0; n < BOARD_SIZE * BOARD_SIZE; n++) {
    // pick up one cell
    const size_t index = indices[n];
    const size_t val = vals[index];
    // tentatively set the value to 0
    vals[index] = 0;
    // see the number of solutions
    size_t nsols = 0;
    count_nsols(vals, &nsols);
    // if multiple answers exist, push back the original value
    if (1 != nsols) {
      vals[index] = val;
    }
  }
  return 0;
}

