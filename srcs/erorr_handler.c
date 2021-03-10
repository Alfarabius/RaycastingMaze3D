/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erorr_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:12:11 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 16:13:00 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			free_tmp(char **arr, char flag)
{
	size_t i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	if (flag)
		return (error_handler("error while parsing"));
	return (1);
}

int			error_handler(char *mes)
{
	write(1, "Error\n", 7);
	write(2, mes, ft_strlen(mes));
	write(2, "\n", 1);
	exit(0);
	return (0);
}
