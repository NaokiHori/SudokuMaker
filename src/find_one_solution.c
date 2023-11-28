#include "general.h"

// try to fill the value at the given position (index = indices[cnt]) randomly
// NOTE: this function is invoked recursively,
//         whose maximum stack depth is nitems < BOARD_SIZE * BOARD_SIZE
static int fill_at (
    size_t * vals,
    const size_t nitems,
    const size_t * indices,
    const size_t cnt
) {
  if (nitems == cnt) {
    // already reached the end of the to-be-filled list
    return 0;
  }
  const size_t index = indices[cnt];
  // decide order of numbers to attempt
  size_t cands[BOARD_SIZE] = {0};
  for (size_t n = 0; n < BOARD_SIZE; n++) {
    cands[n] = n + 1;
  }
  shuffle(BOARD_SIZE, cands);
  for (size_t n = 0; n < BOARD_SIZE; n++) {
    if (0 == check_and_assign(vals, index, cands[n])) {
      // valid, move forward
      if (0 == fill_at(vals, nitems, indices, cnt + 1)) {
        // done, destroy all stack to report success
        return 0;
      } else {
        // reset this cell and try to assign another value
        vals[index] = 0;
      }
    }
  }
  // no valid applicant, this Sudoku does not have an answer
  // go back stack in the reversed order
  return 1;
}

int find_one_solution (
    size_t * vals
) {
  size_t nitems = 0;
  size_t * indices = NULL;
  if (0 != find_nonzero_indices(vals, &nitems, &indices)) {
    return 1;
  }
  // all filled, do nothing and report success
  if (0 == nitems) {
    return 0;
  }
  // make a to-be-filled list
  for (size_t index = 0, cnt = 0; index < BOARD_SIZE * BOARD_SIZE; index++) {
    if (0 == vals[index]) {
      indices[cnt] = index;
      cnt += 1;
    }
  }
  int retval = fill_at(vals, nitems, indices, 0);
  my_free(indices);
  return retval;
}

