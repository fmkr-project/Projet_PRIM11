#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "direction.h"
#include "bucketmanager.h"

int main(int argc, char *argv[])
    {
    if (argc != 2)
	{
	fprintf(stderr, "use : %s < [file.ipi]\n", argv[0]);
	exit(2);
	}
    char *path = argv[1];

    FILE *file = fopen(path, "r");
    if (file == NULL)
	{
	perror("fopen");
	exit(8);
	}

    // Obtain canvas size
    int size = 0;
    
    char buffer[256];
    fgets(buffer, 256, file);
    sscanf(buffer, "%d", &size);

    
    // Cursor position
    int curx = 0; int cury = 0;
    // Last marked position
    int lastx = 0; int lasty = 0;
    // Cursor direction
    dirn direc = 'E';



    rot(&direc, 1);

    // Buckets
    cstack cbucket = new_cstack(char2col('n'));
    cstack_sub(&cbucket);
    ripolin(&cbucket, char2col('n'));
    printf("%d\n", cstack_len(cbucket));



    return 0;
    }
