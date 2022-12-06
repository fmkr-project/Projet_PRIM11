#include <regex.h>

void uniparse(char ltr)
    {
    char* str_of_ltr = calloc(2, sizeof(char));
    str_of_ltr[0] = ltr;
    str_of_ltr[1] = '\0';
    regex_t expr;
    
    // Colors regex
    regcomp(&expr, "[bcgmnrwy]", 0);
    if (regexec(&expr, str_of_ltr, 0, NULL, 0) == 0)
	printf("color !\n");

    // Alpha regex
    regcomp(&expr, "[ot]", 0);
    if (regexec(&expr, str_of_ltr, 0, NULL, 0) == 0)
	printf("alpha !\n");

    // Rotation regex
    regcomp(&expr, "[ah]", 0);
    if (regexec(&expr, str_of_ltr, 0, NULL, 0) == 0)
	printf("weeee !\n");

    // Non-regex actions


    regfree(&expr);
    }

void parse(char* line)
// @requires line will not be freed
    {
    while (*line != '\0')
	{
	uniparse(*line);
	line++;
	}
    }
