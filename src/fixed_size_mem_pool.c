// https://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006

#include "fixed_size_mem_pool.h"
#include "stdio.h"
#include "stdlib.h"
#include "ANSI-color-codes.h"

#define CAPACITY (1 << 16)
#define DATA_SIZE sizeof(Node)

union BlockPublic* mem;

static struct {
    u64 free_blocks;
    u64 initilized_blocks;
    Index head;
    Block data[CAPACITY];
} mem_pool;


void mem_pool_init(){
    mem = (union BlockPublic*)mem_pool.data;
    mem_pool.head = 0;
    mem_pool.free_blocks = CAPACITY;
    mem_pool.initilized_blocks = 0;
}

Index mem_pool_alloc() {
    Index ret;

    #if defined(DEBUG)
        if(!mem_pool.free_blocks) {
            printf("Out of memory!\n");
            exit(1);
        }
    #endif

    if (mem_pool.initilized_blocks < CAPACITY ) {
        Index i = mem_pool.initilized_blocks;
        mem_pool.data[i].index = mem_pool.initilized_blocks + 1;
        mem_pool.initilized_blocks++;
    }

    ret = mem_pool.head;
    mem_pool.free_blocks--;
    mem_pool.head = mem_pool.data[mem_pool.head].index;

    return ret;
}

void mem_pool_free(Index idx) {
    mem_pool.data[idx].index = mem_pool.head;
    mem_pool.head = idx;
    mem_pool.free_blocks++;
}

void print_memory_cell(Index i) {
    char* color = YEL;
    char* purpose = "Data";
    Index head = mem_pool.head;

    if(mem_pool.initilized_blocks == i){
        color = MAG;
        purpose = "End of memory";
    }
    else if(mem_pool.head == i){
        color = GRN;
        purpose = "Head";
    }
    else if(i >= mem_pool.initilized_blocks) {
        purpose = "Uninitilized";
        color = reset;
    }
    else while(head != mem_pool.initilized_blocks) {
        if(head == i) {
            color = GRN;
            purpose = "Bookkeeping";
            break;
        }

        head = mem_pool.data[head].index;
    }


    printf("%sNode[%d]: {%d, %d, %d, %d, %d, %d, %d, %d} \t Index[%d]: %d %s\n" reset,
        color,
        i,
        mem_pool.data[i].node.children[0],
        mem_pool.data[i].node.children[1],
        mem_pool.data[i].node.children[2],
        mem_pool.data[i].node.children[3],
        mem_pool.data[i].node.children[4],
        mem_pool.data[i].node.children[5],
        mem_pool.data[i].node.children[6],
        mem_pool.data[i].node.children[7],
        i, 
        mem_pool.data[i].index,
        purpose
    );
}

void print_memory_state() {
	printf("free: %ld \t init: %ld \t head: %d\n",
        mem_pool.free_blocks,
        mem_pool.initilized_blocks,
        mem_pool.head
    );
}

void print_memory_cells(Index start, Index count) {
	print_memory_state();
	for (int i = start; i < start + count; i++)
		print_memory_cell(i);
	putchar('\n');
}
