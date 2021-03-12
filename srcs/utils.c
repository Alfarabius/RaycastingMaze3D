/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:46:24 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/12 11:41:58 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_pixel_put(t_prg *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		is_num(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int		valid_file(char *frm, char *arg, int size)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 5)
		return (0);
	else if (ft_strncmp(&arg[len - 4], frm, size))
		return (0);
	else if (arg[len - 5] == '/')
		return (0);
	return (1);
}
