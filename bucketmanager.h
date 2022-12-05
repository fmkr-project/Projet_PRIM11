#include <assert.h>

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
// @assigns a new color stack with the color c on top
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

//// Alpha bucket type definition
typedef struct alpit* astack;
typedef struct alpit
    {
    alpha top;
    astack next;
    } alpit;

astack new_astack(alpha a)
// @requires a is a valid alpha value
// @assigns a new alpha stack with the alpha a on top
// @ensures NA
    {
    astack res = malloc(sizeof(alpit));
    res->top = a;
    res->next = NULL;
    return res;
    }

void astack_sub(astack *as)
    {
    *as = (*as)->next;
    }

int astack_isnull(astack as)
    {
    if (as == NULL) return 1; else return 0;
    }

int astack_len(astack as)
    {
    int res = 0;
    while (astack_isnull(as) != 1)
	{
	res++;
	as = as->next;
	}
    return res;
    }


//// Available operations on color buckets
color char2col(char id)
// Converts a letter from the set [bcgmnrwy] into its color equivalent
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

void sink(cstack *cb)
    {
    while (*cb != NULL) cstack_sub(cb);
    }


//// Available operations on alpha buckets
alpha char2alp(char id)
// Converts a letter from the set [ot] into its alpha equivalent
    {
    assert ((id == 't') || (id == 'o'));
    alpha res;
    if (id == 't') res = 0;
    if (id == 'o') res = 255;
    return res;
    }

void cover(astack *ab, alpha a)
    {
    astack ns = new_astack(0);
    ns->top = a;
    ns->next = *ab;
    *ab = ns;
    }

void deop(astack *ab)
    {
    while (*ab != NULL) astack_sub(ab);
    }
