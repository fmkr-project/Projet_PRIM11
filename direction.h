#include <stdio.h>

typedef char dirn;

void rot(dirn *d, int way)
// @requires d is a valid pointer to a direction
// @assigns d
// @ensures the cursor rotates 90° clockwise or c/clockwise
    {
    switch (way)
	{
	case 1:
	    // C/Clockwise
	    switch (*d)
		{
		case 'N':
		    *d = 'W';
		    break;
		case 'E':
		    *d = 'N';
		    break;
		case 'S':
		    *d = 'E';
		    break;
		default:
		    *d = 'S';
		    break;
		};
	    break;
	case -1:
	    // Clockwise
	    switch (*d)
		{
		case 'N':
		    *d = 'E';
		    break;
		case 'E':
		    *d = 'S';
		    break;
		case 'S':
		    *d = 'W';
		    break;
		default:
		    *d = 'N';
		    break;
		};
	    break;
	default:
	    printf("way must be 1 or -1\n");
	    exit(5);
	}
    }
