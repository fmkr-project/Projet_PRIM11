#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>

#include "direction.h"
#include "bucketmanager.h"
#include "layer.h"
#include "cursor.h"
#include "parser.h"
#include "export.h"

// Debug functions
void _debug(char* str)
// Simple function with debugger-like behaviour
    {
    printf("%s", str); fflush(stdout);
    }
	   
int verbose = 0;

int main(int argc, char *argv[])
    {
    if (argc != 2)
	{
	fprintf(stderr, "use : %s < [file.ipi]\n", argv[0]);
	exit(2);
	}

    
    struct rlimit stacksize;
    stacksize.rlim_cur = RLIM_INFINITY; stacksize.rlim_max = RLIM_INFINITY;

    setrlimit(RLIMIT_STACK, &stacksize);
    
    char* path = argv[1];
    char* out = "./out.ppm";

    FILE *file = fopen(path, "r");
    if (file == NULL)
	{
	perror("fopen");
	exit(8);
	}

    // Obtain IPI file size
    long commands = 0;
    fseek(file, 0, SEEK_END);
    commands = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Obtain canvas size
    int size = 0;
    
    char buffer[256];
    fgets(buffer, 256, file);
    sscanf(buffer, "%d", &size);

    // Obtain IPI data
    char data[commands];
    
    // Cursor position
    pos cur; cur.x = 0, cur.y = 0;
    // Last marked position
    pos last; last.x = 0; last.y = 0;
    // Cursor direction
    dirn direc = 'E';
    // Buckets
    cstack cbucket = new_cstack(char2col('n'));
    sink(&cbucket);
    astack abucket = new_astack(0);
    deop(&abucket);
    
    lstack layers = blankstack(size);

    while (fgets(data,commands,file) != NULL)
	{
	parse(data, size, &cur, &last, &direc, &cbucket, &abucket, &layers);
	}

    export(out, layers, size);
    
    return 0;
    }

// TODO : verbose mode
