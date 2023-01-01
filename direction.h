#include <stdio.h>
#include <assert.h>

typedef char dirn;

void rot(dirn *d, char way)
// @requires d is a valid pointer to a direction, way matches [ah]
// @assigns d
// @ensures the cursor rotates 90° clockwise or c/clockwise
    {
    assert ((way == 'a') || (way == 'h'));
    switch (way)
	{
	case 'a':
	    // C/Clockwise
	    switch (*d)
		{
		case 'N':
		    *d = 'W'; break;
		case 'E':
		    *d = 'N'; break;
		case 'S':
		    *d = 'E'; break;
		default:
		    *d = 'S'; break;
		};
	    break;
	case 'h':
	    // Clockwise
	    switch (*d)
		{
		case 'N':
		    *d = 'E'; break;
		case 'E':
		    *d = 'S'; break;
		case 'S':
		    *d = 'W'; break;
		default:
		    *d = 'N'; break;
		};
	    break;
	}
    }
