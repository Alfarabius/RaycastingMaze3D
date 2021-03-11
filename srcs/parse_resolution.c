/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:46:21 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/11 12:39:30 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	res_handler(t_all *all)
{
	int	max_h;
	int	max_w;

	mlx_get_screen_size(all->prg.mlx, &max_w, &max_h);
	if (all->map.height_y > (uint64_t)max_h)
		all->map.height_y = max_h;
	if (all->map.width_x > (uint64_t)max_w)
		all->map.width_x = max_w;
	return (1);
}

int	parse_resolution(char **str, t_all *all, int *flg)
{
	int i;

	i = 0;
	*flg |= flags_checker(*flg, 'R', all);
	while (str[i])
		i++;
	if (i != 3)
		return (free_tmp(str, 1));
	if (!is_num(str[1]) || !is_num(str[2]))
		return (free_tmp(str, 1));
	all->map.width_x = ft_atoi(str[1]);
	all->map.height_y = ft_atoi(str[2]);
	if (all->map.height_y <= 0 || all->map.width_x <= 0)
		return (free_tmp(str, 1));
	return (free_tmp(str, 0));
}
