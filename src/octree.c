#include "octree.h"
#include <string.h>

void octree_init(Octree* octree) {
    octree -> idx = mem_pool_alloc();
    memset(&mem[octree -> idx], 0, sizeof(Node));
}
