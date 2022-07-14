#if !defined(FSA_H)
#define FSA_H

#include "types.h"

union BlockPublic
{
    Node node;
    Leaf leaf;
};

typedef struct FixedSizeAllocator {
    u64 allocated_memory_exp;
    u64 free_blocks;
    u64 initilized_blocks;
    Index head;
    Block* data;
} FixedSizeAllocator;

void fsa_init(FixedSizeAllocator* allocator);
Index fsa_alloc(FixedSizeAllocator* allocator);
void fsa_free(FixedSizeAllocator* allocator, Index index);
void fsa_destroy(FixedSizeAllocator* allocator);
void fsa_print_cell(FixedSizeAllocator* allocator, Index i);
void fsa_print_state(FixedSizeAllocator* allocator);
void fsa_print_cells(FixedSizeAllocator* allocator, Index start, Index count);
void fsa_test(FixedSizeAllocator* allocator);

#endif // FSA_H
