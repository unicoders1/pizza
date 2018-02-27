/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pizza.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:17:56 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/27 18:11:36 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pizza.h"

static void	print_ingr_count_all(void)
{
	printf("%d %d %d %d\n\n", info.rows, info.columns,
		info.ingridient_min_count, info.piece_max_size);
	printf("MUSHROOMS:\n\n");
	for (int i = 0; i < info.rows; ++i)
	{
		for (int j = 0; j < info.columns; ++j)
			printf("%-3d", pizza[i][j].m_count);
		puts("");
	}
	printf("TOMATOS:\n\n");
	for (int i = 0; i < info.rows; ++i)
	{
		for (int j = 0; j < info.columns; ++j)
			printf("%-3d", pizza[i][j].t_count);
		puts("");
	}
}

static void print_ingr_count(void)
{
	t_vector start;
	t_vector end;

	scanf("%d %d %d %d", &start.i, &start.j, &end.i, &end.j);
	printf("M: %d, T: %d\n",
		ingr_count(start, end, MUSHROOM),
		ingr_count(start, end, TOMATO));
}

static void print_list(void)
{
	while (scopes)
	{
		printf("%-3d %-3d, diff: %f\n", scopes->scope->start.i, scopes->scope->start.j
			, scopes->diff);
		fflush(stdout);
		scopes = scopes->next;
	}
}

t_vector	get_vector(int i, int j)
{
	t_vector v;
	v.i = i;
	v.j = j;
	return (v);
}

int			main(int argc, char const *argv[])
{
	FILE	*fptr;

	if (argc == 2)
	{
		fptr = fopen(argv[1], "r");
		if (fptr)
		{
			pizza_read_info(fptr);
			pizza_read(fptr);
			set_scopes();
			/*print_ingr_count_all();
			while (true)
				print_ingr_count();*/
			print_list();
		}
		else
			exit_error("open file error");
	}
	return (0);
}
