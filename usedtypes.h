#ifndef __TYPES
#define __TYPES

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

typedef struct pos
    {
    int x;
    int y;
    } pos;

#endif
