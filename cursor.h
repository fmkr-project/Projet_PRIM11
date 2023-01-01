#include <assert.h>

void updatexy(pos* cur, int size, dirn d)
// @requires cur is a valid pointer to a position, d is a valid dirn
    {
    assert ((cur != NULL));
    switch (d)
	{
	case 'N':
	    (*cur).y = (*cur).y - 1; break;
	case 'E':
	    (*cur).x = (*cur).x + 1; break;
	case 'S':
	    (*cur).y = (*cur).y + 1; break;
	case 'W':
	    (*cur).x = (*cur).x - 1; break;
	default:
	    fprintf(stderr, "NOTICE: direction does not match regex [NESW].\n");
	    break;
	}
    if ((*cur).x < 0) (*cur).x += size;
    if ((*cur).y < 0) (*cur).y += size;
    if ((*cur).x >= size) (*cur).x -= size;
    if ((*cur).y >= size) (*cur).y -= size;
    }
