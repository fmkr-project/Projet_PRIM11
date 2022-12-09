#include <assert.h>

void updatexy(pos* cur, int size, dirn d)
// @requires cur is a valid pointer to a position, d is a valid dirn
    {
    assert ((cur != NULL));
    assert ((d == 'N') || (d == 'E') || (d == 'S') || (d == 'W'));
    switch (d)
	{
	case 'N':
	    (*cur).y = (((*cur).y)-1) % size; break;
	case 'E':
	    (*cur).x = (((*cur).x)+1) % size; break;
	case 'S':
	    (*cur).y = (((*cur).y)+1) % size; break;
	case 'W':
	    (*cur).x = (((*cur).x)-1) % size; break;
	}
    }
