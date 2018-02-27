/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:16:14 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/27 18:15:52 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pizza.h"

void	tm_lst_add(t_list **begin, t_list *new)
{
	if (begin && new)
	{
		new->next = *begin;
		*begin = new;
	}
}

void	tm_lst_insert(t_list *first, t_list *second, t_list *new)
{
	first->next = new;
	new->next = second;
}

t_list	*tm_lst_new(t_scope *scope, float diff)
{
	t_list		*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->scope = scope;
	new->diff = diff;
	new->next = NULL;
	return (new);
}

void	adding_to_list(t_scope *scope, float diff)
{
	t_list			*ptr;
	t_list			*ptr2 = NULL;

	ptr = scopes;
	if (scopes == NULL)
		tm_lst_add(&scopes, tm_lst_new(scope, diff));
	else
	{
		while (ptr != NULL)
		{
			if (diff > ptr->diff)
			{
				tm_lst_add(&scopes, tm_lst_new(scope, diff));
				break ;
			}
			ptr2 = ptr->next;
			if (ptr2 != NULL && diff >= ptr2->diff)
			{
				tm_lst_insert(ptr, ptr->next, tm_lst_new(scope, diff));
				break ;
			}
			else if (ptr->next == NULL)
			{
				ptr->next = tm_lst_new(scope, diff);
				break ;
			}
			ptr = ptr->next;
		}
	}
}
