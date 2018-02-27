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

typedef enum
{
	TOMATO,
	MUSHROOM
}				t_ingr;

typedef struct
{
	int			i;
	int			j;
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
}				t_cell;

typedef struct
{
	t_vector	start;
	t_vector	end;
}				t_scope;

typedef	struct		s_list
{
	t_scope			*scope;
	struct s_list	*next;
	float			diff;
}					t_list;

t_info			info;
t_cell			**pizza;
t_list			*scopes;


void			pizza_read_info(int fd);
void			pizza_read(int fd);
void			set_scopes(void);
void			adding_to_list(t_scope *field, float diff);
int				ingr_count(t_vector start, t_vector end, t_ingr ingr);
t_vector		get_vector(int i, int j);
void			exit_error(char *message);

#endif
