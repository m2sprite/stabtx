#define local_persist static
#define global static
#define internal static

typedef uint8_t u8;
typedef int32_t s32;
typedef s32 b32;
typedef float f32;

#define ArrayCount(arr) (sizeof((arr)) / (sizeof((arr)[0])))
#define Kilobytes(number) ((number)*1024ull)
#define Megabytes(number) (Kilobytes(number) * 1024ull)
#define Gigabytes(number) (Megabytes(number) * 1024ull)
#define Terabytes(number) (Gigabytes(number) * 1024ull)

#include <string.h>
#define MEMORYZERO(p,z) memset((p), 0, (z))
#define MEMORYZEROSTRUCT(p) MEMORYZERO((p), sizeof(*(p)))
#define MEMORYZEROARRAY(p) MEMORYZERO((p), sizeof(p))
#define MEMORYZEROTYPED(p,c) MEMORYZERO((p), sizeof(*(p))*(c))

#define EvalPrintKey(x) printf("%s %d %b\n", #x ,x.halfTransitionCount, x.isEndedDown);
