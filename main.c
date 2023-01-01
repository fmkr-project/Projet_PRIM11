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
// Flushs str to stdout
    {
    printf("%s", str); fflush(stdout);
    }

int main(int argc, char *argv[])
    {
    // Argument check
    char* out; char* path; FILE* file;
    switch (argc)
	{
	case 1:
	    // Read on stdin, output into default file
	    out = "./out.ppm";
	    file = stdin;
	    break;
	case 2:
	    // Read on given argument, output into default file
	    out = "./out.ppm";
	    path = argv[1];
	    file = fopen(path, "r");
	    break;
	case 3:
	    // Read and output on given arguments
	    out = argv[2];
	    path = argv[1];
	    file = fopen(path, "r");
	    break;
	default:
	    // Too much args
	    fprintf(stderr, "use : %s\nuse : %s in.ipi\nuse : %s in.ipi out.ppm\n", argv[0], argv[0], argv[0]);
	    exit(10);
	    break;
	}

    // Max stack size override (for big canvases)
    struct rlimit stacksize;
    stacksize.rlim_cur = RLIM_INFINITY; stacksize.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_STACK, &stacksize);

    // File not found exception
    if (file == NULL)
	{
	perror("fopen");
	exit(8);
	}

    // Obtain .ipi file size
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
    // Layer stack
    lstack layers = blankstack(size);

    // Read until EOF
    while (fgets(data,commands,file) != NULL)
	{
	parse(data, size, &cur, &last, &direc, &cbucket, &abucket, &layers);
	}

    export(out, layers, size);
    
    return 0;
    }
