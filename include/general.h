#if !defined(GENERAL_H)
#define GENERAL_H

#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 9
#define BLOCK_SIZE 3

extern void * my_malloc (
    const size_t size
);

extern void my_free (
    void * ptr
);

extern int shuffle (
    const size_t nitems,
    size_t * vals
);

extern int check_and_assign (
    size_t * vals,
    const size_t index,
    const size_t val
);

extern int find_nonzero_indices (
    const size_t * vals,
    size_t * nitems,
    size_t ** indices
);

extern int find_one_solution (
    size_t * vals
);

extern int create_a_puzzle (
    size_t * vals
);

extern int count_nsols(
    const size_t * vals,
    size_t * nsols
);

#endif // GENERAL_H
