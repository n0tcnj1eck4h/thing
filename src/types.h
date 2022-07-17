#if !defined(TYPES_H)
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>

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

typedef enum VOXEL_ID {
    VOXEL_FIRST = 0,
    VOXEL_AIR = 0,
    VOXEL_COUNT = 1024,
} VOXEL_ID;

typedef union MemoryBlock {
    u128 data;
    u16 children[8];
    struct {
        union MemoryBlock* next;
        union MemoryBlock* unused;
    };
} MemoryBlock;

#endif // TYPES_H
