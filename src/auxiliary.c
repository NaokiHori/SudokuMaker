#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include "general.h"

void * my_malloc (
    const size_t size
) {
  errno = 0;
  void * ptr = malloc(size);
  if (NULL == ptr) {
    perror("");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void my_free (
    void * ptr
) {
  free(ptr);
}

// return a shuffled vector of vals
int shuffle (
    const size_t nitems,
    size_t * vals
) {
  size_t * indices = my_malloc(nitems * sizeof(size_t));
  bool * used = my_malloc(nitems * sizeof(bool));
  size_t * copied_vals = my_malloc(nitems * sizeof(size_t));
  for (size_t n = 0; n < nitems; n++) {
    indices[n] = 0;
    used[n] = false;
    copied_vals[n] = vals[n];
  }
  // decide order
  for (size_t n = 0; n < nitems; n++) {
    const size_t r = rand() % (nitems - n);
    for (size_t cnt = 0, m = 0; m < nitems; m++) {
      if (used[m]) {
        continue;
      }
      if (r == cnt) {
        used[m] = true;
        indices[n] = m;
        break;
      }
      cnt += 1;
    }
  }
  // shuffle
  for (size_t n = 0; n < nitems; n++) {
    vals[n] = copied_vals[indices[n]];
  }
  // clean-up
  my_free(used);
  my_free(indices);
  my_free(copied_vals);
  return 0;
}

// check if the current array is a valid Sudoku
//   and assign the new value when I find it is
int check_and_assign (
    size_t * vals,
    const size_t index,
    const size_t val
) {
  const size_t i = index / BOARD_SIZE;
  const size_t j = index % BOARD_SIZE;
  // check overlap for the same row
  for (size_t ii = 0; ii < BOARD_SIZE; ii++) {
    if (i == ii) {
      continue;
    }
    if (val == vals[ii * BOARD_SIZE + j]) {
      return 1;
    }
  }
  // check overlap for the same column
  for (size_t jj = 0; jj < BOARD_SIZE; jj++) {
    if (j == jj) {
      continue;
    }
    if (val == vals[i * BOARD_SIZE + jj]) {
      return 1;
    }
  }
  // check overlap for the same block
  const size_t imin = BLOCK_SIZE * (i / BLOCK_SIZE);
  const size_t jmin = BLOCK_SIZE * (j / BLOCK_SIZE);
  for (size_t jj = jmin; jj < jmin + BLOCK_SIZE; jj++) {
    for (size_t ii = imin; ii < imin + BLOCK_SIZE; ii++) {
      if (i == ii && j == jj) {
        continue;
      }
      if (val == vals[ii * BOARD_SIZE + jj]) {
        return 1;
      }
    }
  }
  vals[index] = val;
  return 0;
}

int find_nonzero_indices (
    const size_t * vals,
    size_t * nitems,
    size_t ** indices
) {
  // find all non-zero indices
  *nitems = 0;
  for (size_t index = 0; index < BOARD_SIZE * BOARD_SIZE; index++) {
    if (0 == vals[index]) {
      *nitems += 1;
    }
  }
  // make a to-be-filled list
  *indices = my_malloc(*nitems * sizeof(size_t));
  for (size_t index = 0, cnt = 0; index < BOARD_SIZE * BOARD_SIZE; index++) {
    if (0 == vals[index]) {
      (*indices)[cnt] = index;
      cnt += 1;
    }
  }
  return 0;
}

