#include <string.h>

void export(char* path, lstack ls, int size)
    {
    FILE* out = fopen(path, "w");
    if (out == NULL)
	{
	perror("fopen");
	exit(50);
	}

    // PPM header
    char* buf = "P3\n";
    char buf2[255];
    fwrite(buf, sizeof(char), 3, out);
    
    // Image size
    sprintf(buf2, "%d %d\n255\n", size, size);
    fwrite(buf2, sizeof(char), strlen(buf2), out);

    // Image contents
    for (int i = 0; i < size; i++)
	{
	for (int j = 0; j < size; j++)
	    {
	    pixel curpix = ls->top.pixs[j][i];
	    sprintf(buf2, "%d %d %d\n", curpix.col.r, curpix.col.g, curpix.col.b);
	    fwrite(buf2, sizeof(char), strlen(buf2), out);
	    }
	}
    }
