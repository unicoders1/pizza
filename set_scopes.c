/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scopes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:32:28 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/27 18:10:33 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pizza.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static const int	scope_factor = 4;

static inline t_vector	get_end(t_vector start, int shift)
{
	t_vector end;

	if (start.y + shift < info.rows)
		end.y = start.y + shift - 1;
	else
		end.y = info.rows - 1;

	if (start.x + shift < info.columns)
		end.x = start.x + shift - 1;
	else
		end.x = info.columns - 1;
	return (end);
}

static float			get_scope_diff(t_scope *s)
{
	float	m_count;
	float	t_count;
	float	sum;

	m_count = ingr_count(s->start, s->end, MUSHROOM);
	t_count = ingr_count(s->start, s->end, TOMATO);
	sum = m_count + t_count;
	return (MAX(m_count / sum, t_count / sum));
}

void					set_scopes(void)
{
	int		shift;
	t_scope	*s;

	scopes = NULL;
	shift = 1;//info.piece_max_size * scope_factor;
	for (int i = 0; i < info.rows; i += shift)
	{
		for (int j = 0; j < info.columns; j += shift)
		{
			s = malloc(sizeof(t_scope));
			s->start.y = i;
			s->start.x = j;
			s->end = get_end(s->start, shift);
			s->out = NULL;
			adding_to_list(s, get_scope_diff(s));
		}
	}
}
