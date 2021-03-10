/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:56:18 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 15:04:56 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	int	get_player_direction(t_all *all, int i, int j)
{
	if (all->map.mini_map[i][j] == 'N')
	{
		all->plr.x_dir = 0;
		all->plr.y_dir = -1;
	}
	else if (all->map.mini_map[i][j] == 'S')
	{
		all->plr.x_dir = 0;
		all->plr.y_dir = 1;
	}
	else if (all->map.mini_map[i][j] == 'E')
	{
		all->plr.x_dir = 1;
		all->plr.y_dir = 0;
	}
	else if (all->map.mini_map[i][j] == 'W')
	{
		all->plr.x_dir = -1;
		all->plr.y_dir = 0;
	}
	return (1);
}

int			get_player_start_position(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map.mini_map[i])
	{
		j = 0;
		while (!(ft_isalpha(all->map.mini_map[i][j]))
									&& all->map.mini_map[i][j])
			j++;
		if (ft_isalpha(all->map.mini_map[i][j]))
		{
			all->plr.x_pos = (float)j + 0.5;
			all->plr.y_pos = (float)i + 0.5;
			get_player_direction(all, i, j);
			all->plr.plane_x *= all->plr.y_dir * -1;
			all->plr.plane_y *= all->plr.x_dir;
			all->map.mini_map[i][j] = '0';
		}
		i++;
	}
	return (1);
}
