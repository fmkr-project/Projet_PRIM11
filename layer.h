// Layer definition
typedef struct layer
    {
    int size;
    pixel** pixs;
    } layer;

layer blank(int n)
    {
    layer res;
    res.size = n;

    pixel** pixs = NULL;
    pixs = (pixel**) malloc(res.size * sizeof(pixel*));
    for (int h = 0; h < res.size; h++)
	pixs[h] = calloc(res.size, sizeof(pixel));

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

void pline(layer *l, cstack cb, astack ab, pos coords0, pos coords1)
    {
    int delx = coords1.x - coords0.x;
    int dely = coords1.y - coords0.y;
    int d; int s; pixel avp;
    if (abs(delx) > abs(dely)) d = abs(delx); else d = abs(dely);
    if (delx*dely > 0) s = 0; else s = 1;

    int x = coords0.x * d + (d-s)/2;
    int y = coords0.y * d + (d-s)/2;
    for (int hl = 0; hl<d; hl++)
	{
	avp = avpix(cb,ab);
	(*l).pixs[x/d][y/d] = avp;
	x += delx;
	y += dely;
	}
    avp = avpix(cb,ab);
    (*l).pixs[coords1.x][coords1.y] = avp;
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
    {
    layer bl = blank(size);
    lstack res = malloc(sizeof(lel));
    res->top = bl;
    res->next = NULL;
    return res;
    }

void ladd(lstack* ls, layer l, int size)
    {
    if (nofl(*ls) > 9)
	{
        printf("NOTICE: layer stack is full.\n");
	return;
	}
    lstack hl = blankstack(size);
    hl->top = l;
    hl->next = *ls;
    *ls = hl;
    }

layer lpop(lstack* ls, int size)
    {
    layer res;
    if (nofl(*ls) == 0)
	{
	printf("NOTICE: cannot pop from an empty layer stack. Defaulting to blank layer.");
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
    {
    if (nofl(*ls) < 2)
	{
	printf("NOTICE: cannot merge in a stack of length < 2.");
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
