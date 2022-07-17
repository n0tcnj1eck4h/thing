#include "octree.h"
#include "renderer.h"
#include "global.h"


MemoryBlock* idx_to_ptr(Octree* octree, u16 idx) {
    return &octree -> allocator -> data[idx - octree -> reserved_indices];
}

u16 ptr_to_idx(Octree* octree, MemoryBlock* ptr) {
    return ((size_t)((size_t)ptr - (size_t)octree -> allocator -> data)) / sizeof(MemoryBlock) + octree -> reserved_indices;
}

void octree_init(Octree* octree, FixedSizeAllocator* allocator) {
    octree -> allocator = allocator;
    octree -> head = fsa_alloc(allocator);
    octree -> head -> data = 0; 
}

void octree_draw(Octree* octree, MemoryBlock* head, mat4 transform) {
	rederer_draw_cube_lines(transform);

	for(u8 i = 0; i < 8; i++) {
        u16 index = head -> children[i];

        if(index == VOXEL_AIR) // Air
            continue;

        mat4 transform_next;
        glm_mat4_copy(transform, transform_next);
        glm_scale_uni(transform_next, 0.5f);
        glm_translate(transform_next, (vec3){i & 1, (i >> 1) & 1, (i >> 2) & 1});

        if(index >= octree -> reserved_indices) {
            MemoryBlock* child = idx_to_ptr(octree, head -> children[i]);
            renderer_set_draw_color(GLM_VEC3_ZERO);
            octree_draw(octree, child, transform_next);
        }
        else {
            renderer_set_draw_color(global.palette[head -> children[i]]);
            rederer_draw_cube(transform_next);
        }
	}
}

void octree_set_block(Octree* octree, MemoryBlock* origin, u64 path, u8 depth, VOXEL_ID id) {
    u8 child_index = path % 8;
    u16 child_data = origin -> children[child_index];

    if(child_data == id) return;

    if(depth > 0) {
        if(child_data < octree -> reserved_indices) {
            MemoryBlock* new_child = fsa_alloc(octree -> allocator);

            for (size_t i = 0; i < 8; i++) {
                new_child -> children[i] = child_data;
            }

            origin -> children[child_index] = ptr_to_idx(octree, new_child);

            octree_set_block(octree, new_child, path / 8, depth - 1, id);
        }
        else {
            MemoryBlock* new_origin = idx_to_ptr(octree, child_data);
            octree_set_block(octree, new_origin, path / 8, depth - 1, id);
        }
    }
    else {
        origin -> children[child_index] = id;
    }
}

/*
void octree_add_child(Octree* octree, MemoryBlock* parent, u8 child_index, VOXEL_ID voxel_id) {
	if (parent -> children[child_index] >= octree -> reserved_indices) 
        return;

    parent -> children[child_index] = voxel_id;
}

void octree_kill_children(Octree* octree, MemoryBlock* parent) {
	for(u8 i = 0; i < 8; i++) {
		if(parent -> children[i] >= octree -> reserved_indices) {
            MemoryBlock* child = idx_to_ptr(octree, parent -> children[i]);
			octree_kill_children(octree, child);
			fsa_free(octree -> allocator, child);
		}
        parent -> children[i] = VOXEL_AIR;
	}
}*/