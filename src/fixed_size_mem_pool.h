#if !defined(FIXED_SIZE_MEM_POOL_H)
#define FIXED_SIZE_MEM_POOL_H

#include "types.h"

union BlockPublic
{
    Node node;
    Leaf leaf;
};

extern union BlockPublic* mem;

void mem_pool_init();
Index mem_pool_alloc();
void mem_pool_free(Index);
void print_memory_cell(Index i);
void print_memory_state();
void print_memory_cells(Index start, Index count);

#endif // FIXED_SIZE_MEM_POOL_H
