// https://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006

#include "fsa.h"
#include "ANSI-color-codes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

void fsa_init(FixedSizeAllocator* allocator) {
    allocator -> allocated_memory_exp = 16; // 64kb
    allocator -> free_blocks = 1 << allocator -> allocated_memory_exp;
    allocator -> initilized_blocks = 0;
    allocator -> data = malloc(allocator -> free_blocks);
    allocator -> head = allocator -> data;
    assert(allocator -> data);
}

MemoryBlock* fsa_alloc(FixedSizeAllocator* allocator) {
    MemoryBlock* ret;

    if(!allocator -> free_blocks) {
        #if defined(DEBUG)
            printf("Out of memory, reallocating!\n");
        #endif // DEBUG

        allocator -> free_blocks += 1 << (allocator -> allocated_memory_exp);
        allocator -> allocated_memory_exp++;
        allocator -> data = realloc(allocator -> data, 1 << allocator -> allocated_memory_exp);
    }

    if (allocator -> initilized_blocks < (1 << allocator -> allocated_memory_exp)) {
        allocator -> data[allocator -> initilized_blocks].next = &allocator -> data[allocator -> initilized_blocks + 1];
        allocator -> initilized_blocks++;
    }

    ret = allocator -> head;
    allocator -> free_blocks--;
    allocator -> head = allocator -> head -> next;

    return ret;
}

void fsa_free(FixedSizeAllocator* allocator, MemoryBlock* ptr) {
    ptr -> next = allocator -> head;
    allocator -> head = ptr;
    allocator -> free_blocks++;
}

void fsa_destroy(FixedSizeAllocator* allocator)  {
    free(allocator -> data);
    memset(allocator, 0, sizeof(*allocator));
}

void fsa_print_cell(FixedSizeAllocator* allocator, u64 i) {
    char* color = YEL;
    char* purpose = "Data";
    MemoryBlock* head = allocator -> head;
    MemoryBlock* block = &allocator -> data[i];

    if(i >= 1 << allocator -> allocated_memory_exp) {
        printf("Unallocated\n");
        return;
    }

    if(allocator -> initilized_blocks == i){
        color = MAG;
        purpose = "End of memory";
    }
    else if(allocator -> head == block){
        color = GRN;
        purpose = "Head";
    }
    else if(i >= allocator -> initilized_blocks) {
        purpose = "Uninitilized";
        color = reset;
    }
    else while(head != &allocator -> data[allocator -> initilized_blocks]) {
        if(head == &allocator -> data[i]) {
            color = GRN;
            purpose = "Bookkeeping";
            break;
        }

        head = head -> next;
    }


    printf("%sBlock[%ld] @ %p: {%d, %d, %d, %d, %d, %d, %d, %d} Next: %p  %s\n" reset,
        color,
        i,
        block,
        allocator -> data[i].children[0],
        allocator -> data[i].children[1],
        allocator -> data[i].children[2],
        allocator -> data[i].children[3],
        allocator -> data[i].children[4],
        allocator -> data[i].children[5],
        allocator -> data[i].children[6],
        allocator -> data[i].children[7],
        allocator -> data[i].next,
        purpose
    );
}

void fsa_print_state(FixedSizeAllocator* allocator) {
	printf("free: %ld \t init: %ld \t head: %p\n",
        allocator -> free_blocks,
        allocator -> initilized_blocks,
        allocator -> head
    );
}

void fsa_print_cells(FixedSizeAllocator* allocator, u64 start, u64 count) {
	fsa_print_state(allocator);
	for (int i = start; i < start + count; i++)
		fsa_print_cell(allocator, i);
	putchar('\n');
}

void fsa_test(FixedSizeAllocator* allocator) {
	MemoryBlock* indices[3];

	printf("===ALLOCATOR TEST===\n");

	printf("Initial state:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[0] = fsa_alloc(allocator);
	indices[0] -> data = 123;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[1] = fsa_alloc(allocator);
	indices[1] -> data = 727;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[2] = fsa_alloc(allocator);
	indices[2] -> data = 1337;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);

	fsa_free(allocator, indices[0]);
	printf("Free:\n");
	fsa_print_cells(allocator, 0, 5);

	fsa_free(allocator, indices[2]);
	printf("Free:\n");
	fsa_print_cells(allocator, 0, 5);

	indices[2] = fsa_alloc(allocator);
	indices[2] -> data = 0xFF;
	printf("Alloc:\n");
	fsa_print_cells(allocator, 0, 5);
}