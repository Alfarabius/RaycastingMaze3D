/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:16:42 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/11 12:39:21 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	int	valid_color_elem(char *str, int *cmm, int i)
{
	if (i == 1 && *str == ',')
		return (0);
	while (*str && (*str == ',' || *str == ' ' || ft_isdigit(*str)))
	{
		*cmm += *str == ',' ? 1 : 0;
		if (*str == ',' && *(str + 1) == ',')
			return (0);
		str++;
	}
	if (*str != ',' && !ft_isdigit(*str) && *str)
		return (0);
	if (*cmm > 2)
		return (0);
	return (1);
}

static	int	get_color_val(char **str, int *flg, int *count)
{
	int	i;
	int	color;

	if (!*str)
		return (0);
	i = 0;
	color = 0;
	if (is_num(str[i]))
	{
		color = atoi(str[i]);
		if (color > 255 || color < 0)
			return (-1);
		*flg += 1;
	}
	*count += 1;
	return (color);
}

int			get_color(char **str, int *flg)
{
	int		i;
	int		rgb;
	int		count;
	char	**acc;

	i = 1;
	*flg = 0;
	while (str[i])
	{
		count = 0;
		acc = ft_split(str[i], ',');
		*flg < 1 ? rgb = get_color_val(acc + count, flg, &count) << 16 : 0;
		*flg < 2 ? rgb |= get_color_val(acc + count, flg, &count) << 8 : 0;
		*flg >= 2 ? rgb |= get_color_val(acc + count, flg, &count) : 0;
		if (rgb == -1)
			return (free_tmp(str, 1));
		free_tmp(acc, 0);
		i++;
	}
	return (rgb);
}

int			parse_color(char flag, char **str, t_all *all, int *flg)
{
	int		rgb;
	int		f;
	int		i;

	i = 0;
	f = 0;
	*flg |= flags_checker(*flg, flag, all);
	while (str[++i])
		if (!valid_color_elem(str[i], &f, i))
			return (free_tmp(str, 1));
	if (i < 2 || i > 6 || f < 2 ||
		str[i - 1][ft_strlen(str[i - 1]) - 1] == ',')
		return (free_tmp(str, 1));
	rgb = get_color(str, &f);
	flag == 'F' ? all->map.floor_color = rgb : 0;
	flag == 'C' ? all->map.cell_color = rgb : 0;
	return (f == 3 ? free_tmp(str, 0) : free_tmp(str, 1));
}
