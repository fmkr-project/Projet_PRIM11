#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "direction.h"
#include "bucketmanager.h"
#include "layer.h"
#include "cursor.h"
#include "parser.h"
#include "debug.h"


int verbose = 0;

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
    pos cur; cur.x = 0, cur.y = 0;
    // Last marked position
    pos last; last.x = 0; last.y = 0;
    // Cursor direction
    dirn direc = 'E';



    rot(&direc, 'a');

    // Buckets
    cstack cbucket = new_cstack(char2col('n'));
    sink(&cbucket);
    astack abucket = new_astack(0);
    deop(&abucket);

    lstack layers = blankstack(size);
    ladd(&layers, blank(size), size);
    ladd(&layers, blank(size), size);
    printf("%d layer(s)\n",nofl(layers));



    
    ripolin(&cbucket, char2col('n'));
    printf("%d\n", cstack_len(cbucket));
    parse("rhorpuuuokznbwbrwbrbwbrw", size, &cur, &last, &direc, &cbucket, &abucket, &layers);
    printf("%d\n", cstack_len(cbucket));
    pixel d = avpix(cbucket, abucket);
    printcolor(d.col);
    
    return 0;
    }

// TODO : verbose mode
