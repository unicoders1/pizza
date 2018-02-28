/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:58:11 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/23 16:20:44 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "../libft/libft.h"

static int	read_line(const int fd, char **line, t_dat *dat)
{
	int		red;
	char	*tmp;
	int		flag;

	flag = 0;
	while ((red = read(fd, dat->buff, BUFF_SIZE)) > 0)
	{
		if ((tmp = ft_strchr(dat->buff, '\n')))
		{
			*tmp = 0;
			flag = 1;
			dat->fd = fd;
			dat->i = tmp - dat->buff + 1;
			dat->len = red;
		}
		dat->buff[red] = 0;
		tmp = *line;
		*line = ft_strjoin(tmp, dat->buff);
		free(tmp);
		if (flag)
			return (red);
	}
	return (red);
}

static int	add_new(const int fd, t_list **files_dat, char **line)
{
	const int	size = sizeof(t_dat);
	t_list		*new;
	t_dat		*dat;
	int			red;

	new = NULL;
	if (!(dat = ft_memalloc(sizeof(*dat))))
		return (-1);
	red = read_line(fd, line, dat);
	if (red > 0)
	{
		if (!(new = ft_lstnew((void*)dat, size)))
			red = -1;
		if (red >= 0 && new)
			ft_lstadd(files_dat, new);
	}
	free(dat);
	return (red >= 0 ? *line != NULL : -1);
}

static int	use_dat(t_dat *dat, char **line)
{
	int		len;
	char	*last;

	if (dat->i >= dat->len)
		return (0);
	if ((last = ft_strchr(dat->buff + dat->i, '\n')))
		len = (int)(last - dat->buff - dat->i);
	else
		len = dat->len - dat->i;
	if (!*line && !(*line = malloc(sizeof(**line) * (len + 1))))
		return (-1);
	ft_strncpy(*line, dat->buff + dat->i, len);
	(*line)[len] = 0;
	dat->i += len + 1;
	return (dat->buff[dat->i - 1] != 0);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*files_dat = NULL;
	t_list			*cur;
	t_dat			*dat;
	int				res;

	if (fd < 0 || !line)
		return (-1);
	cur = files_dat;
	*line = NULL;
	while (cur)
	{
		dat = (t_dat*)cur->value;
		if (dat->fd == fd)
		{
			if (dat->i < dat->len &&
				(res = use_dat(dat, line)) != 0)
				return (res);
			break ;
		}
		cur = cur->next;
	}
	return (add_new(fd, &files_dat, line));
}
