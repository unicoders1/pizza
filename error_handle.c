/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:10:40 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/27 14:25:37 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "pizza.h"

void	exit_error(char *message)
{
	printf("%s\n", message);
	fflush(stdout);
	exit(EXIT_FAILURE);
}
