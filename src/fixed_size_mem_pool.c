// https://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006

#include "fixed_size_mem_pool.h"
#include "ANSI-color-codes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

void fsa_init(FixedSizeAllocator* allocator) {
    allocator -> allocated_memory_exp = 16; // 64kb
    allocator -> free_blocks = 1 << allocator -> allocated_memory_exp;
    allocator -> initilized_blocks = 0;
    allocator -> head = 0;
    allocator -> data = malloc(allocator -> free_blocks);
    assert(allocator -> data);
}

Index fsa_alloc(FixedSizeAllocator* allocator) {
    Index ret;

    if(!allocator -> free_blocks) {
        #if defined(DEBUG)
            printf("Out of memory, reallocating!\n");
        #endif // DEBUG

        allocator -> free_blocks += 1 << (allocator -> allocated_memory_exp);
        allocator -> allocated_memory_exp++;
        allocator -> data = realloc(allocator -> data, 1 << allocator -> allocated_memory_exp);
    }

    if (allocator -> initilized_blocks < (1 << allocator -> allocated_memory_exp)) {
        Index i = allocator -> initilized_blocks;
        allocator -> data[i].index = allocator -> initilized_blocks + 1;
        allocator -> initilized_blocks++;
    }

    ret = allocator -> head;
    allocator -> free_blocks--;
    allocator -> head = allocator -> data[allocator -> head].index;

    return ret;
}

void fsa_free(FixedSizeAllocator* allocator, Index idx) {
    allocator -> data[idx].index = allocator -> head;
    allocator -> head = idx;
    allocator -> free_blocks++;
}

void fsa_destroy(FixedSizeAllocator* allocator)  {
    free(allocator -> data);
    memset(allocator, 0, sizeof(*allocator));
}

void fsa_print_cell(FixedSizeAllocator* allocator, Index i) {
    char* color = YEL;
    char* purpose = "Data";
    Index head = allocator -> head;

    if(i >= 1 << allocator -> allocated_memory_exp) {
        printf("Unallocated\n");
        return;
    }

    if(allocator -> initilized_blocks == i){
        color = MAG;
        purpose = "End of memory";
    }
    else if(allocator -> head == i){
        color = GRN;
        purpose = "Head";
    }
    else if(i >= allocator -> initilized_blocks) {
        purpose = "Uninitilized";
        color = reset;
    }
    else while(head != allocator -> initilized_blocks) {
        if(head == i) {
            color = GRN;
            purpose = "Bookkeeping";
            break;
        }

        head = allocator -> data[head].index;
    }


    printf("%sNode[%d]: {%d, %d, %d, %d, %d, %d, %d, %d} \t Index[%d]: %d %s\n" reset,
        color,
        i,
        allocator -> data[i].node.children[0],
        allocator -> data[i].node.children[1],
        allocator -> data[i].node.children[2],
        allocator -> data[i].node.children[3],
        allocator -> data[i].node.children[4],
        allocator -> data[i].node.children[5],
        allocator -> data[i].node.children[6],
        allocator -> data[i].node.children[7],
        i, 
        allocator -> data[i].index,
        purpose
    );
}

void fsa_print_state(FixedSizeAllocator* allocator) {
	printf("free: %ld \t init: %ld \t head: %d\n",
        allocator -> free_blocks,
        allocator -> initilized_blocks,
        allocator -> head
    );
}

void fsa_print_cells(FixedSizeAllocator* allocator, Index start, Index count) {
	fsa_print_state(allocator);
	for (int i = start; i < start + count; i++)
		fsa_print_cell(allocator, i);
	putchar('\n');
}

void fsa_test(FixedSizeAllocator* allocator) {
	Index indices[3];

	printf("===ALLOCATOR TEST===\n");

	printf("Initial state:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[0] = fsa_alloc(allocator);
	allocator -> data[indices[0]].leaf.data[0] = 123;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[1] = fsa_alloc(allocator);
	allocator -> data[indices[1]].leaf.data[0] = 727;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[2] = fsa_alloc(allocator);
	allocator -> data[indices[2]].leaf.data[0] = 1337;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);

	fsa_free(allocator, indices[0]);
	printf("Free:\n");
	fsa_print_cells(allocator, 0, 5);

	fsa_free(allocator, indices[2]);
	printf("Free:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[2] = fsa_alloc(allocator);
	allocator -> data[indices[2]].leaf.data[0] = 0xFF;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);
}