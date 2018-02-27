/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ingr_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:44:48 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/27 17:47:01 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pizza.h"

static inline int	get_ingr(t_cell *c, t_ingr ingr)
{
	if (ingr == TOMATO)
		return (c->t_count);
	else
		return (c->m_count);
}

int					ingr_count(t_vector start, t_vector end, t_ingr ingr)
{
	int		top;
	int		left;
	int		topleft;
	int		all;

	top = 0;
	left = 0;
	topleft = 0;
	all = get_ingr(&pizza[end.i][end.j], ingr);
	if (start.i > 0)
		top = get_ingr(&pizza[start.i - 1][end.j], ingr);
	if (start.j > 0)
		left = get_ingr(&pizza[end.i][start.j - 1], ingr);
	if (start.i > 0 && start.j > 0)
		topleft = get_ingr(&pizza[start.i - 1][start.j - 1], ingr);
	return (all - top - left + topleft);
}
