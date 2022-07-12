#if !defined(OCTREE_H)
#define OCTREE_H

#include "fixed_size_mem_pool.h"

typedef struct Octree {
    Index idx;
} Octree;

void octree_init(Octree*);


#endif // OCTREE_H
