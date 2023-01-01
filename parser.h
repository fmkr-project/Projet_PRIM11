#include <regex.h>

void uniparse(char ltr, int size, pos* cur, pos* last, dirn* d, cstack* cb, astack* ab, lstack* ls)
    {
    // Cast of ltr into a char*
    char* str_of_ltr = calloc(2, sizeof(char));
    str_of_ltr[0] = ltr;
    str_of_ltr[1] = '\0';
    
    regex_t expr;

    // Is ltr associated with an action ? (debug purpose only)
    /*  regcomp(&expr, "[nrgbymcwtoivhaplfsej]", 0);
    if (regexec(&expr, str_of_ltr, 0, NULL, 0) != 0)
	fprintf(stderr, "NOTICE: the letter %s is unused.\n", str_of_ltr);
    else
	fprintf(stderr, "NOTICE: parsing letter %s...\n", str_of_ltr);
    fflush(stderr);
*/
    
    // Colors regex
    regcomp(&expr, "[bcgmnrwy]", 0);
    if (regexec(&expr, str_of_ltr, 0, NULL, 0) == 0)
	ripolin(cb, char2col(ltr));

    // Alpha regex
    regcomp(&expr, "[ot]", 0);
    if (regexec(&expr, str_of_ltr, 0, NULL, 0) == 0)
	cover(ab, char2alp(ltr));

    // Rotation regex
    regcomp(&expr, "[ah]", 0);
    if (regexec(&expr, str_of_ltr, 0, NULL, 0) == 0)
	rot(d, ltr);

    // Non-regex actions
    if (ltr == 'p') *last = *cur;
    if (ltr == 'v') updatexy(cur, size, *d);
    if (ltr == 'i') { sink(cb); deop(ab); }
    if (ltr == 's') ladd(ls, blank(size), size);
    if (ltr == 'l') pline(&((*ls)->top), *cb, *ab, *last, *cur);
    if (ltr == 'e') lmerge(ls, size);
    if (ltr == 'j') lcut(ls, size);
    if (ltr == 'f') fillall(*cur, &((*ls)->top), *cb, *ab);
    
    regfree(&expr);
    }

void parse(char* line, int size, pos* cur, pos* last, dirn* d, cstack* cb, astack* ab, lstack* ls)
// @requires line will not be freed
    {
    while (*line != '\0')
	{
	uniparse(*line, size, cur, last, d, cb, ab, ls);
	line++;
	}
    }
