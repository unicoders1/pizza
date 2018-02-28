/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:03:52 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/27 15:47:02 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pizza.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

static int 			ingr_count_prev(int i, int j, t_ingr ingr)
{
	int	top;
	int	left;

	top = 0;
	left = 0;
	if (i > 0)
		top = ingr_count(get_vector(0, j), get_vector(i - 1, j), ingr);
	if (j > 0)
		left = ingr_count(get_vector(0, 0), get_vector(i, j - 1), ingr);
	return (top + left);
}

static void			set_ingr_count(char ingr, int i, int j)
{
	t_cell	c;

	c.m_count = 0;
	c.t_count = 0;
	if (ingr == 'M')
		c.m_count = 1;
	else if (ingr == 'T')
		c.t_count = 1;
	else
		exit_error("wrong pizza cell");
	c.m_count += ingr_count_prev(i, j, MUSHROOM);
	c.t_count += ingr_count_prev(i, j, TOMATO);
	pizza[i][j] = c;
}

static void			pizza_read_line(char *line, int i)
{
	int		j;

	j = 0;
	while (*line)
	{
		set_ingr_count(*line, i, j);
		++line;
		++j;
	}
}

void				pizza_read(int fd)
{
	char	*line;
	int		i;

	pizza = malloc(sizeof(*pizza) * info.rows);
	i = 0;
	while (get_next_line(fd, &line))
	{
		pizza[i] = malloc(sizeof(*pizza) * info.columns);
		pizza_read_line(line, i);
		free(line);
		++i;
	}
	if (i != info.rows)
		exit_error("map size doesn't match map info");
}

void				pizza_read_info(int fd)
{
	char	*line;
	char	**info_strs;

	if (get_next_line(fd, &line))
	{
		info_strs = ft_strsplit(line, ' ');
		info.rows = ft_atoi(info_strs[0]);
		info.columns = ft_atoi(info_strs[1]);
		info.ingridient_min_count = ft_atoi(info_strs[2]);
		info.piece_max_size = ft_atoi(info_strs[3]);
	}
	else
		exit_error("error on reading pizza info");
}
