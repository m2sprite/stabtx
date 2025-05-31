#define local_persist static
#define global static
#define internal static

typedef int32_t s32;
typedef s32 b32;
typedef float f32;

#define ArrayCount(arr) (sizeof((arr)) / (sizeof((arr)[0])))
#define Kilobytes(number) ((number)*1024ull)
#define Megabytes(number) (Kilobytes(number) * 1024ull)
#define Gigabytes(number) (Megabytes(number) * 1024ull)
#define Terabytes(number) (Gigabytes(number) * 1024ull)

#include <string.h>
#define MEMORYZERO(p,Z) memset((p), 0, (z))
#define MEMORYZEROSTRUCT(p) MemoryZero((p), sizeof(*(p)))
#define MEMORYZEROARRAY(p) MemoryZero((p), sizeof(p))
#define MEMORYZEROTYPED(p,c) MemoryZero((p), sizeof(*(p))*(c))
