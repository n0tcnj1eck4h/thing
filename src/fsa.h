#if !defined(FSA_H)
#define FSA_H

#include "types.h"

typedef struct FixedSizeAllocator {
    u64 allocated_memory_exp;
    u64 free_blocks;
    u64 initilized_blocks;
    MemoryBlock* head;
    MemoryBlock* data;
} FixedSizeAllocator;

void fsa_init(FixedSizeAllocator* allocator);
MemoryBlock* fsa_alloc(FixedSizeAllocator* allocator);
void fsa_free(FixedSizeAllocator* allocator, MemoryBlock* ptr);
void fsa_destroy(FixedSizeAllocator* allocator);
void fsa_print_cell(FixedSizeAllocator* allocator, u64 i);
void fsa_print_state(FixedSizeAllocator* allocator);
void fsa_print_cells(FixedSizeAllocator* allocator, u64 start, u64 count);
void fsa_test(FixedSizeAllocator* allocator);

#endif // FSA_H
