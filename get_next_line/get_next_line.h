/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:58:20 by omykolai          #+#    #+#             */
/*   Updated: 2017/12/07 18:17:14 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 100000

typedef struct	s_dat
{
	int			fd;
	int			len;
	char		buff[BUFF_SIZE + 1];
	int			i;
}				t_dat;

int				get_next_line(const int fd, char **line);

#endif
