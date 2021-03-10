/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfarabi <alfarabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:39:26 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/01 18:16:00 by alfarabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	calc_sdx(t_drw *drw, t_all *all, char sgn)
{
	drw->stp_x = sgn;
	if (sgn == 1)
		drw->s_dst_x = (drw->map_x + 1.0 - all->plr.x_pos) * drw->d_dst_x;
	else
		drw->s_dst_x = (all->plr.x_pos - drw->map_x) * drw->d_dst_x;
}

static	void	calc_sdy(t_drw *drw, t_all *all, char sgn)
{
	drw->stp_y = sgn;
	if (sgn == 1)
		drw->s_dst_y = (drw->map_y + 1.0 - all->plr.y_pos) * drw->d_dst_y;
	else
		drw->s_dst_y = (all->plr.y_pos - drw->map_y) * drw->d_dst_y;
}

static	void	ray_calc(t_drw *drw, t_all *all)
{
	drw->cam_x = 2 * drw->x / (float)all->map.width_x - 1;
	drw->ray_dir_x = all->plr.x_dir + all->plr.plane_x * drw->cam_x;
	drw->ray_dir_y = all->plr.y_dir + all->plr.plane_y * drw->cam_x;
	drw->map_x = (int)all->plr.x_pos;
	drw->map_y = (int)all->plr.y_pos;
	drw->d_dst_x = fabs(1 / drw->ray_dir_x);
	drw->d_dst_y = fabs(1 / drw->ray_dir_y);
	if (drw->ray_dir_x < 0)
		calc_sdx(drw, all, -1);
	else
		calc_sdx(drw, all, 1);
	if (drw->ray_dir_y < 0)
		calc_sdy(drw, all, -1);
	else
		calc_sdy(drw, all, 1);
}

static	char	hit_check(t_drw *drw, t_all *all)
{
	if (drw->s_dst_x < drw->s_dst_y)
	{
		drw->s_dst_x += drw->d_dst_x;
		drw->map_x += drw->stp_x;
		if (drw->stp_x > 0)
			drw->side = 0;
		else
			drw->side = 2;
	}
	else
	{
		drw->s_dst_y += drw->d_dst_y;
		drw->map_y += drw->stp_y;
		if (drw->stp_y > 0)
			drw->side = 1;
		else
			drw->side = 3;
	}
	if (all->map.mini_map[drw->map_y][drw->map_x] == '1')
		return (1);
	return (0);
}

int				draw_img(t_all *all)
{
	t_drw	drw;
	float	z_buff[all->map.width_x];

	drw.x = 0;
	drw.side = 0;
	while (drw.x < (int)all->map.width_x)
	{
		drw.is_hit = 0;
		ray_calc(&drw, all);
		while (!drw.is_hit)
			if (hit_check(&drw, all))
				drw.is_hit = 1;
		calc_line(&drw, all);
		draw_line(0, all->lin.start + 1, all->map.cell_color, all);
		draw_wall(all->lin.start, all->lin.end, drw.side, all);
		draw_line(all->lin.end, all->map.height_y - 1,
									all->map.floor_color, all);
		z_buff[drw.x] = drw.pltowll_dst;
		drw.x++;
	}
	draw_sprites(all, &all->plr, z_buff, &all->dta);
	return (1);
}
