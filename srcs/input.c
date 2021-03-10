/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:24:44 by mrosie            #+#    #+#             */
/*   Updated: 2021/02/25 15:04:02 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	move_player(t_all *all, float x_off, float y_off)
{
	if ((all->map.mini_map)[(int)(all->plr.y_pos)][(int)(all->plr.x_pos
										+ all->plr.x_dir * x_off * 3)] != '1')
		all->plr.x_pos += all->plr.x_dir * x_off;
	if ((all->map.mini_map)[(int)(all->plr.y_pos + all->plr.y_dir * y_off
									* 3)][(int)(all->plr.x_pos)] != '1')
		all->plr.y_pos += all->plr.y_dir * y_off;
	return (1);
}

int	strafe_player(t_all *all, float x_off, float y_off)
{
	if ((all->map.mini_map)[(int)(all->plr.y_pos)][(int)(all->plr.x_pos
						+ all->plr.plane_x * x_off * 3)] != '1')
		all->plr.x_pos += all->plr.plane_x * x_off;
	if (all->map.mini_map[(int)(all->plr.y_pos + all->plr.plane_y * y_off
							* 3)][(int)(all->plr.x_pos)] != '1')
		all->plr.y_pos += all->plr.plane_y * y_off;
	return (1);
}

int	turn_player(t_all *all, float ang)
{
	float		prev_dir_x;
	float		prev_plane_x;

	prev_dir_x = all->plr.x_dir;
	prev_plane_x = all->plr.plane_x;
	all->plr.x_dir = all->plr.x_dir * cos(ang)
							- all->plr.y_dir * sin(ang);
	all->plr.y_dir = prev_dir_x * sin(ang)
							+ all->plr.y_dir * cos(ang);
	all->plr.plane_x = all->plr.plane_x * cos(ang)
							- all->plr.plane_y * sin(ang);
	all->plr.plane_y = prev_plane_x * sin(ang)
							+ all->plr.plane_y * cos(ang);
	return (1);
}
