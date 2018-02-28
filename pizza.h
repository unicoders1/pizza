/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pizza.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:08:52 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/27 18:18:57 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIZZA_H
# define PIZZA_H
# include <stdbool.h>
# include <stdlib.h>

# include <stdio.h>
# include <fcntl.h>

typedef enum
{
	TOMATO,
	MUSHROOM
}				t_ingr;

typedef struct
{
	int			x;
	int			y;
}				t_vector;

typedef struct
{
	int			rows;
	int			columns;
	int			ingridient_min_count;
	int			piece_max_size;
}				t_info;

typedef struct
{
	int			m_count;
	int			t_count;
	int 		marker;
}				t_cell;

typedef struct		s_out
{
	char 			*data;
	struct s_out	*next;
}					t_out;

typedef struct
{
	t_vector	start;
	t_vector	end;
	t_out		*out;
}				t_scope;

typedef	struct		s_list
{
	t_scope			*scope;
	float			diff;
	struct s_list	*next;
}					t_list;

t_info			info;
t_cell			**pizza;
t_list			*scopes;


void			pizza_read_info(FILE *fptr);
void			pizza_read(FILE *fptr);
void			set_scopes(void);
void			adding_to_list(t_scope *field, float diff);
int				ingr_count(t_vector start, t_vector end, t_ingr ingr);
t_vector		get_vector(int i, int j);
void			exit_error(char *message);
char			**ft_strsplit(char const *str, char c);

/*
 * start_cut.c
 */

void	start_cut(void);

#endif
