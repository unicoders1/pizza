#include "pizza.h"
int cellcount = 0;

void	set_marker(t_vector start, t_vector end)
{
	for (int i = start.x; i <= end.x; ++i) {
		for (int j = start.y; j <= end.y; ++j) {
			pizza[j][i].marker = 1;
		}
	}
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

void	try_cut(t_scope *scope, int y, int x)
{
	int width1 = info.piece_max_size;
	int width2 = 1;
	int height1 = 1;
	int height2 = info.piece_max_size;

	while (width1 != 1 || width2 != 1 || height1 != 1 || height2 != 1)
	{
		if (check_hpiece(x, y, x + width1, y + height1, &width1, &height1))
		{
			add_out(scope, x, y, x + width1, y + height1);
			return ;
		}
		if (check_vpiece(x, y, x + width2, y + height2, &width2, &height2))
		{
			add_out(scope, x, y, x + width2, y + height2);
			return ;
		}
	}
}

void 	cut_scope(t_scope *scope)
{
	int	x_start = scope->start.y;
	int	y_start = scope->start.y;
	int	x = x_start;
	int	y = y_start;

	while (y <= scope->end.y)
	{
		if (!pizza[y][x].marker)
			try_cut(scope, y, x);
		x++;
		if (x > scope->end.x)
		{
			y++;
			x = x_start;
		}
	}
}

void	start_cut(void)
{
	t_list	*sc = scopes;

	while (sc)
	{
		cut_scope(sc->scope);
		sc = sc->next;
	}
}
