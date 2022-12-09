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
