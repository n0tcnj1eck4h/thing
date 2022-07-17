#if !defined(OCTREE_H)
#define OCTREE_H

#include "types.h"
#include "fsa.h"
#include "cglm/mat4.h"

typedef struct Octree {
	MemoryBlock* head;
    FixedSizeAllocator* allocator;
    u64 reserved_indices;
} Octree;

void octree_init(Octree* octree, FixedSizeAllocator* allocator);
void octree_draw(Octree* octree, MemoryBlock* head, mat4 transform);
bool octree_set_block(Octree* octree, MemoryBlock* origin, u64 path, u8 depth, VOXEL_ID id);

#endif // OCTREE_H
