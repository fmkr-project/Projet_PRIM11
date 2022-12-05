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


// Buckets & layers
typedef struct layer* lstack;
typedef struct layer
    {
    int size;
    pixel **colors;
    alpha **alphas;
    } layer;
