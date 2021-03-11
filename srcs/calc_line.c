/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:38:13 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/11 17:16:08 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	calc_pltowll_dst(t_drw *drw, t_all *all)
{
	if (drw->side.side == 0 || drw->side.side == 2)
	{
		drw->pltowll_dst = (drw->map_y - all->plr.y_pos +
								(1 - drw->stp_y) / 2) / drw->ray_dir_y;
		drw->wall_x = all->plr.x_pos + drw->pltowll_dst
										* drw->ray_dir_x;
	}
	else if (drw->side.side == 1 || drw->side.side == 3)
	{
		drw->pltowll_dst = (drw->map_x - all->plr.x_pos +
								(1 - drw->stp_x) / 2) / drw->ray_dir_x;
		drw->wall_x = all->plr.y_pos + drw->pltowll_dst
										* drw->ray_dir_y;
	}
	drw->wall_x -= floor(drw->wall_x);
}

static	void	calc_line_param(t_drw *drw, t_all *all)
{
	all->lin.height = (int)(all->map.height_y / drw->pltowll_dst);
	all->lin.start = all->map.height_y / 2 - all->lin.height / 2;
	if (all->lin.start < 0)
		all->lin.start = 0;
	all->lin.end = all->lin.height / 2 + all->map.height_y / 2;
	if (all->lin.end >= (int)all->map.height_y)
		all->lin.end = all->map.height_y - 1;
}

static	void	calc_textr_param(t_drw *drw, t_all *all, t_tex *s)
{
	all->tex.curr_x = drw->x;
	s->textr_x = (int)(drw->wall_x * (float)(s->x_wd));
	if (((s == &all->tex.nrt || s == &all->tex.sth) && drw->ray_dir_x < 0)
		|| ((s == &all->tex.est || s == &all->tex.wst) && drw->ray_dir_y > 0))
		s->textr_x = s->x_wd - s->textr_x - 1;
	s->ratio = 1.0 * s->x_wd / all->lin.height;
	s->start = (all->lin.start - all->map.height_y / 2 +
						all->lin.height / 2) * s->ratio;
}

int				calc_line(t_drw *drw, t_all *all)
{
	calc_pltowll_dst(drw, all);
	calc_line_param(drw, all);
	calc_textr_param(drw, all, &drw->side);
	return (1);
}
