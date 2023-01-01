#ifndef __TYPES
#define __TYPES

// Color component
typedef unsigned char
comp;

// Color
typedef struct color
    {
    comp r;
    comp g;
    comp b;
    } color;

// Alpha value
typedef comp
alpha;

// Pixel struct
typedef struct pixel
    {
    color col;
    alpha al;
    } pixel;


// Position struct
typedef struct pos
    {
    int x;
    int y;
    } pos;

#endif
