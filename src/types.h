#if !defined(TYPES_H)
#define TYPES_H

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __uint128_t u128;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef __int128_t i128;

typedef float  f32;
typedef double f64;

typedef enum VOXEL_IDS {
    VOXEL_FIRST = 0,
    VOXEL_COUNT = 1024,
} VOXEL_IDS;

typedef union MemoryBlock {
    u16 children[8];
    u128 data;
    struct {
        MemoryBlock* next;
        MemoryBlock* unused;
    };
    struct {
        u8 r, g, b;
    } voxel_info;
} MemoryBlock;

#endif // TYPES_H
