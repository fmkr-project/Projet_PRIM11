// Simple data structures
typedef unsigned char
comp;

typedef struct color
    {
    comp r;
    comp g;
    comp b;
    } color;

typedef comp
alpha;

typedef struct pixel
    {
    color col;
    alpha al;
    } pixel;


// Chained lists (stacks)
typedef struct istack
    {
    int top;
    struct istack *next;
    } istack;


typedef struct astack
    {
    alpha top;
    struct astack *next;
    } astack;

// Buckets & layers
typedef struct layer
    {
    int size;
    pixel **contents;
    } layer;
