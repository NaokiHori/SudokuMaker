#include "general.h"

// try to fill the value at the given position (index = indices[cnt]) randomly
static int fill_at (
    size_t * nsols,
    size_t * vals,
    const size_t nitems,
    const size_t * indices,
    const size_t cnt
) {
  if (nitems == cnt) {
    // new solution is found
    *nsols += 1;
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
      fill_at(nsols, vals, nitems, indices, cnt + 1);
      // reset this cell and try to assign another value
      vals[index] = 0;
    }
  }
  // no valid applicant, this Sudoku does not have an answer
  // go back stack in the reversed order
  return 1;
}

// check number of solutions of the given sudoku
int count_nsols (
    const size_t * vals,
    size_t * nsols
) {
  size_t nitems = 0;
  size_t * indices = NULL;
  if (0 != find_nonzero_indices(vals, &nitems, &indices)) {
    return 1;
  }
  // all filled, do nothing and report success
  if (0 == nitems) {
    // of course unique solution
    *nsols = 1;
    return 0;
  }
  size_t * copied_vals = my_malloc(BOARD_SIZE * BOARD_SIZE * sizeof(size_t));
  for (size_t index = 0; index < BOARD_SIZE * BOARD_SIZE; index++) {
    copied_vals[index] = vals[index];
  }
  int retval = fill_at(nsols, copied_vals, nitems, indices, 0);
  my_free(indices);
  my_free(copied_vals);
  return retval;
}

