// https://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006

#include "fixed_size_mem_pool.h"
#include "stdio.h"
#include "stdlib.h"

#define CAPACITY (1 << 16)
#define DATA_SIZE sizeof(Node)

Node* mem;

typedef union Block {
    Node node;
    Index index;
} Block;

static struct {
    u64 free_blocks;
    u64 initilized_blocks;
    Index head;
    Block data[CAPACITY];
} mem_pool;


void mem_pool_init(){
    mem = (Node*)mem_pool.data;
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

    if (mem_pool.initilized_blocks < CAPACITY) {
        mem_pool.data[mem_pool.initilized_blocks].index = mem_pool.initilized_blocks + 1;
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