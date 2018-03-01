#include <memory.h>
#include <time.h>
#include "pizza.h"


Stack *pieces;
Stack *result;

int cellcount = 0;
int goodcount;
int bestcount;
int scopecount;

clock_t time_start;

int     check_time()
{
    if (clock() - time_start > 10 * CLOCKS_PER_SEC)
        return (1);
    return (0);
}


void	set_marker(t_vector start, t_vector end)
{
	for (int i = start.x; i <= end.x; ++i) {
		for (int j = start.y; j <= end.y; ++j) {
			pizza[j][i].marker = 1;
		}
	}
    scopecount += (end.x - start.x + 1) * (end.y - start.y + 1);
    //print_markers();
}
void    unset_marker(t_piece *p)
{
    if (!p)
        return;
    for (int i = p->start.x; i <= p->end.x; ++i) {
        for (int j = p->start.y; j <= p->end.y; ++j) {
            pizza[j][i].marker = 0;
        }
    }
    scopecount -= (p->end.x - p->start.x + 1) * (p->end.y - p->start.y + 1);
    free(p);
    //print_markers();
}


t_piece *get_piece(int sx, int sy, int ex, int ey)
{
    t_piece *p;

    p = malloc(sizeof(t_piece));
    p->start = get_vector(sy, sx);
    p->end = get_vector(ey - 1, ex - 1);
    set_marker(get_vector(sy, sx), get_vector(ey - 1, ex - 1));
    return (p);
}

void	add_out(t_scope *scope, int sx, int sy, int ex, int ey)
{
	t_out	*out = (t_out*)malloc(sizeof(t_out));
	char	*data = (char*)malloc(sizeof(char) * 16);

	sprintf(data, "%d %d %d %d", sy, sx, ey - 1, ex - 1);
	out->data = data;
	out->next = scope->out;
	scope->out = out;
	cellcount += (ex - sx) * (ey - sy);
	set_marker(get_vector(sy, sx), get_vector(ey - 1, ex - 1));
}

void    a()
{
    ;
}

void    add_result(void)
{
    t_piece *p;

    while ((p = stackPop(result)))
    {
        t_out	*out = (t_out*)malloc(sizeof(t_out));
        char	*data = (char*)malloc(sizeof(char) * 16);


        printf("%d %d %d %d\n", p->start.y, p->start.x, p->end.y, p->end.x);
        fflush(stdout);
        /*out->data = data;
        out->next = output;
        output = out;*/
        //cellcount += (p->end.x - p->start.x + 1) * (p->end.y - p->start.y + 1);
    }

}

int 	check_marker(t_vector start, t_vector end)
{
	for (int i = start.x; i <= end.x; ++i) {
		for (int j = start.y; j <= end.y; ++j) {
			if (pizza[j][i].marker)
				return (0);
		}
	}
	return (1);
}

int 	check_hpiece(int sx, int sy, int ex, int ey, int *width, int *height)
{
	t_vector	start;
	t_vector	end;
	int row = info.rows;
	int col = info.columns;

	start.x = sx;
	start.y = sy;
	end.x = ex - 1;
	end.y = ey - 1;
	if (ey > info.rows)
	{
		*height -= 1;
		return (0);
	}
	if (ex > info.columns)
	{
		*width -= 1;
		return (0);
	}
	if ((ex - sx) * (ey - sy) > info.piece_max_size)
	{
		if (*height > 1)
			*height -= 1;
		else
			(*width > 1) ? *width -= 1 : *width;
		return (0);
	}
	else if (ingr_count(start, end, TOMATO) >= info.ingridient_min_count &&
			 ingr_count(start, end, MUSHROOM) >= info.ingridient_min_count &&
			check_marker(start, end))
		return (1);
	if (*width == 1)
		(*height > 1) ? *height -= 1 : *height;
	else
		(*height < info.piece_max_size) ? *height += 1 : *height;
	(*width > 1) ? *width -= 1 : *width;
	return (0);
}

int 	check_vpiece(int sx, int sy, int ex, int ey, int *width, int *height)
{
	t_vector	start;
	t_vector	end;

	start.x = sx;
	start.y = sy;
	end.x = ex - 1;
	end.y = ey - 1;
	if (ey > info.rows)
	{
		*height -= 1;
		return (0);
	}
	if (ex > info.columns)
	{
		*width -= 1;
		return (0);
	}
	if ((ex - sx) * (ey - sy) > info.piece_max_size)
	{
		if (*width > 1)
			*width -= 1;
		else
			(*height > 1) ? *height -= 1 : *height;
		return (0);
	}
	else if (ingr_count(start, end, TOMATO) >= info.ingridient_min_count &&
			 ingr_count(start, end, MUSHROOM) >= info.ingridient_min_count &&
			check_marker(start, end))
		return (1);
	if (*height == 1)
		(*width > 1) ? *width -= 1 : *width;
	else
		(*width < info.piece_max_size) ? *width += 1 : *width;
	(*height > 1) ? *height -= 1 : *height;
	return (0);
}

int	    try_cut(t_scope *scope, int y, int x)
{
	int width1 = info.piece_max_size;
	int width2 = 1;
	int height1 = 1;
	int height2 = info.piece_max_size;

	while (width1 != 1 || width2 != 1 || height1 != 1 || height2 != 1)
	{
		if (check_hpiece(x, y, x + width1, y + height1, &width1, &height1))
        {
            stackPush(pieces, get_piece(x, y, x + width1, y + height1));
			//add_out(scope, x, y, x + width1, y + height1);
			return 1;
		}
		if (check_vpiece(x, y, x + width2, y + height2, &width2, &height2))
		{
            stackPush(pieces, get_piece(x, y, x + width2, y + height2));
			//add_out(scope, x, y, x + width2, y + height2);
			return 1;
		}
	}
    return (0);
}

void    set_result(void)
{
    StackNode *node;
    t_piece   *item;

    node = pieces->top;
    stackDestroy(result);
    result = stackCreate();
    while (node)
    {
        item = malloc(sizeof(*item));
        memcpy(item, node->item, sizeof(*item));
        stackPush(result, item);
        node = node->next;
    }
    int tmp = scopecount;
    int tmp1 = bestcount;
    bestcount = scopecount;
}

int    cut_scope(int x_start, int x, int y, t_scope *scope)
{
    int res;

    while (y <= scope->end.y)
    {
        if (!pizza[y][x].marker)
            res = try_cut(scope, y, x);
        else
            res = 0;
        x++;
        if (x > scope->end.x)
        {
            y++;
            x = x_start;
        }
        if (res)
        {
            if (scopecount == goodcount)
                return (1);
            if (cut_scope(x_start, x + stackTop(pieces)->end.x - stackTop(pieces)->start.x - 1, y, scope))
                return (1);
            unset_marker(stackPop(pieces));
        }
    }
    if (scopecount > bestcount)
        set_result();
    return (check_time());
}

void	start_cut(void)
{
	t_list	*sc = scopes;

    time_start = clock();
	while (sc)
	{
        pieces = stackCreate();
        result = stackCreate();
        scopecount = 0;
        bestcount = -1;
        goodcount = (sc->scope->end.x - sc->scope->start.x + 1) * (sc->scope->end.y - sc->scope->start.y + 1);
        if (cut_scope(sc->scope->start.x, sc->scope->start.x, sc->scope->start.y, sc->scope))
            if (scopecount > bestcount)
                set_result();
        add_result();
		sc = sc->next;

        stackDestroy(pieces);
        stackDestroy(result);
	}
}
