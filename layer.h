// Layer definition
typedef struct layer
    {
    int size;
    pixel** pixs;
    } layer;

// Debug functions
void _spec(layer l, pos coords)
// Flushs pixel data at given coords
    {
    pixel hl = l.pixs[coords.x][coords.y];
    printf("Pixel at %d:%d : %d.%d.%d op%d\n", coords.x, coords.y, hl.col.r, hl.col.g, hl.col.b, hl.al); fflush(stdout);
    }

// Functions on layers
layer blank(int n)
// @assigns a new layer
// @ensures pixel data for all pixels is 0.0.0 op0
    {
    layer res;
    res.size = n;

    // Memory allocation to layer contents
    pixel** pixs = NULL;
    pixs = (pixel**) malloc(res.size * sizeof(pixel*));
    for (int h = 0; h < res.size; h++)
	pixs[h] = calloc(res.size, sizeof(pixel));

    // Memory initialisation
    for (int i = 0; i < res.size; i++)
	{
	for (int j = 0; j < res.size; j++)
	    {
	    pixs[i][j].col.r = 0; pixs[i][j].col.g = 0; pixs[i][j].col.b = 0;
	    pixs[i][j].al = 0;
	    }
	}
    res.pixs = pixs;
    return res;
    }

void pline(layer* l, cstack cb, astack ab, pos coords0, pos coords1)
// @requires coords0 and coords1 are valid for l's size
// @ensures a line is drawn on l between coords0 and coords1
    {
    int delx = coords1.x - coords0.x;
    int dely = coords1.y - coords0.y;
    int d; int s; pixel avp;
    if (abs(delx) > abs(dely)) d = abs(delx); else d = abs(dely);
    if (delx*dely > 0) s = 0; else s = 1;
    
    int x = coords0.x * d + (d-s)/2;
    int y = coords0.y * d + (d-s)/2;
    avp = avpix(cb,ab);
    for (int hl = 0; hl<d; hl++)
	{
	(*l).pixs[x/d][y/d].col = avp.col; (*l).pixs[x/d][y/d].al = avp.al;
	x += delx;
	y += dely;
	}
    (*l).pixs[coords1.x][coords1.y] = avp;
    }

// Position stack & fill procedure
/* UNUSED
typedef struct pel* pstack;
typedef struct pel
    {
    pos top;
    pstack next;
    } pel;

pstack pnew(pos coords)
    {
    pstack res = malloc(sizeof(pel));
    res->top = coords;
    res->next = NULL;
    return res;
    }

int plen(pstack ps)
    {
    int res = 0;
    while (ps != NULL)
	{
	res++;
	ps = ps->next;
	}
    return res;
    }

void ppush(pstack* ps, pos coords)
    {
    pstack hl = pnew(coords);
    hl->top = coords;
    hl->next = *ps;
    *ps = hl;
    }

pos ppop(pstack* ps)
    {
    pos res;
    if (*ps == NULL)
	{
	fprintf(stderr, "NOTICE: cannot pop from an empty stack. Defaulting to (0,0).");
	res.x = 0; res.y = 0;
	}
    else
	{
	res = (*ps)->top;
	*ps = (*ps)->next;
	}
    return res;
    }
*/

void fill(pos coords, pixel oldpix, pixel newpix, layer* l)
// @requires coords is valid for l's size
    {
    pos next = coords;
    
    if (peq(oldpix, newpix))
	{
	fprintf(stderr, "NOTICE: trying to fill with the same color.\n");
	return;
	}
    if (peq((*l).pixs[coords.x][coords.y], oldpix) == 1)
	{
	(*l).pixs[coords.x][coords.y] = newpix;
	if (coords.x > 0)
	    {
	    next.x--;
	    // ppush(ps, next);
	    fill(next, oldpix, newpix, l);
	    next.x++;
	    }
	if (coords.y > 0)
	    {
	    next.y--;
	    // ppush(ps, next);
	    fill(next, oldpix, newpix, l);
	    next.y++;
	    }
	if (coords.x < (*l).size - 1)
	    {
	    next.x++;
	    // ppush(ps, next);
	    fill(next, oldpix, newpix, l);
	    next.x--;
	    }
	if (coords.y < (*l).size - 1)
	    {
	    next.y++;
	    // ppush(ps, next);
	    fill(next, oldpix, newpix, l);
	    next.y--;
	    }
	}
    }

void fillall(pos coords, layer* l, cstack cb, astack ab)
// @requires coords is valid for l's size, l is a valid pointer to a stack
// @ensures area from coords to same pixel boundary is filled with calculated avpix
// NOTE: since fillall is only called by 'f', l is assumed to be never NULL
    {
    pixel curpix = avpix(cb,ab);
    /*pos todo;
      pstack ps = pnew(coords);*/
    fill(coords, (*l).pixs[coords.y][coords.x], curpix, l);
    /*
    while (ps != NULL)
	{
	todo = ppop(&ps);
	(*l).pixs[todo.y][todo.x] = curpix;
	}
    */
    }

// Layer stacks
typedef struct lel* lstack;
typedef struct lel
    {
    layer top;
    lstack next;
    } lel;

int nofl(lstack ls)
// Returns the number of stacks in a layer stack
    {
    int res = 0;
    while (ls != NULL)
	{
	res++;
	ls = ls->next;
	}
    return res;
    }

lstack blankstack(int size)
// @assigns a new layer stack
// @ensures there is 1 blank layer in the new stack
    {
    layer bl = blank(size);
    lstack res = malloc(sizeof(lel));
    res->top = bl;
    res->next = NULL;
    return res;
    }

void ladd(lstack* ls, layer l, int size)
// @requires ls is a valid pointer to a layer stack
// @ensures nofl(*ls)++ if there are <10 layers in the stack
    {
    if (nofl(*ls) > 9)
	{
        fprintf(stderr, "NOTICE: layer stack is full.\n");
	return;
	}
    lstack hl = blankstack(size);
    hl->top = l;
    hl->next = *ls;
    *ls = hl;
    }

layer lpop(lstack* ls, int size)
// @requires *ls is not empty
// @ensures the returned layer is the top of *ls
    {
    layer res;
    if (nofl(*ls) == 0)
	{
	fprintf(stderr, "NOTICE: cannot pop from an empty layer stack. Defaulting to blank layer.");
        res = blank(size);
	}
    else
	{
	res = (*ls)->top;
	*ls = (*ls)->next;
	}
    return res;
    }

void lmerge(lstack* ls, int size)
// @requires *ls contains at least 2 layers
// @ensures top 2 layers are merged
    {
    if (nofl(*ls) < 2)
	{
	fprintf(stderr, "NOTICE: cannot merge in a stack of length < 2.");
	return;
	}
    
    layer res = blank(size);
    layer upper = lpop(ls, size);
    layer lower = lpop(ls, size);
    
    for (int i = 0; i < size; i++)
	{
	for (int j = 0; j < size; j++)
	    {
	    res.pixs[i][j].col.r = upper.pixs[i][j].col.r + lower.pixs[i][j].col.r * (255 - upper.pixs[i][j].al) / 255;
	    res.pixs[i][j].col.g = upper.pixs[i][j].col.g + lower.pixs[i][j].col.g * (255 - upper.pixs[i][j].al) / 255;
	    res.pixs[i][j].col.b = upper.pixs[i][j].col.b + lower.pixs[i][j].col.b * (255 - upper.pixs[i][j].al) / 255;
	    res.pixs[i][j].al = upper.pixs[i][j].al + lower.pixs[i][j].al * (255 - upper.pixs[i][j].al) / 255;
	    }
	}
    ladd(ls, res, size);
    }

void lcut(lstack* ls, int size)
// @requires *ls contains at least 2 layers
// @ensures top layer cuts 2nd layer
    {
    if (nofl(*ls) < 2)
	{
	fprintf(stderr, "NOTICE: cannot cut in a stack of length < 2.");
	return;
	}
    
    layer res = blank(size);
    layer upper = lpop(ls, size); // c0
    layer lower = lpop(ls, size); // c1

    for (int i = 0; i < size; i++)
	{
	for (int j = 0; j < size; j++)
	    {
	    res.pixs[i][j].col.r = lower.pixs[i][j].col.r * upper.pixs[i][j].al / 255;
	    res.pixs[i][j].col.g = lower.pixs[i][j].col.g * upper.pixs[i][j].al / 255;
	    res.pixs[i][j].col.b = lower.pixs[i][j].col.b * upper.pixs[i][j].al / 255;
	    res.pixs[i][j].al = lower.pixs[i][j].al * upper.pixs[i][j].al / 255;
	    }
	}
    ladd(ls, res, size);
    }
