

#include "usedtypes.h"

//// Color bucket type definition
typedef struct colit* cstack;
typedef struct colit
    {
    color top;
    cstack next;
    } colit;

cstack new_cstack(color c)
// @requires c is a valid color
// @assigns a new color stack
// @ensures NA
    {
    cstack res = malloc(sizeof(colit));
    res->top = c;
    res->next = NULL;
    return res;
    }

void cstack_sub(cstack *cs)
    {
    *cs = (*cs)->next;
    }

int cstack_isnull(cstack cs)
    {
    if (cs == NULL) return 1; else return 0;
    }

int cstack_len(cstack cs)
    {
    int res = 0;
    while (cstack_isnull(cs) != 1)
	{
	res++;
	cs = cs->next;
	}
    return res;
    }

//// Available operations on color buckets
color char2col(char id)
// Converts a letter from the set [nrgbymcw] into its color equivalent
    {
    color res; res.r = 0; res.g = 0; res.b = 0;
    if ((id == 'r') || (id == 'y') || (id == 'm') || (id == 'w')) res.r = 255;
    if ((id == 'g') || (id == 'y') || (id == 'c') || (id == 'w')) res.g = 255;
    if ((id == 'b') || (id == 'm') || (id == 'c') || (id == 'w')) res.b = 255;
    return res;
    }

void ripolin(cstack *cb, color c)
    {
    cstack ns = new_cstack(char2col('n'));
    ns->top = c;
    ns->next = *cb;
    *cb = ns;
    }
