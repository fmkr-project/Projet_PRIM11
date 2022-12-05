#include <assert.h>

void updatexy(int *x, int *y, int size, dirn d)
// @requires x and y are valid pointers to positions, d is a valid dirn
    {
    assert ((x != NULL) && (y != NULL));
    assert ((d == 'N') || (d == 'E') || (d == 'S') || (d == 'W'));
    switch (d)
	{
	case 'N':
	    *y = ((*y)-1) % size; break;
	case 'E':
	    *x = ((*x)+1) % size; break;
	case 'S':
	    *y = ((*y)+1) % size; break;
	case 'W':
	    *x = ((*x)-1) % size; break;
	}
    }

void flushcoords(int x, int y, int *markx, int *marky)
// @requires markx and marky are valid pointers to the marked position
    {
    assert ((markx != NULL) && (marky != NULL));
    *markx = x;
    *marky = y;
    }
