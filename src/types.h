#if !defined(TYPES_H)
#define TYPES_H

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float  f32;
typedef double f64;

typedef u16 Index;

typedef struct Node {
    Index children[8];
} Node;

typedef struct Leaf {
    u64 data[2];
} Leaf;

typedef union Block {
    Node node;
    Leaf leaf;
    Index index;
} Block;

#endif // TYPES_H
