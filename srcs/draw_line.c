/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:01:14 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/07 18:48:58 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	unsigned int	get_color(t_all *all, int side)
{
	unsigned int	color;
	int				textr_y;
	void			*adr;

	adr = NULL;
	if (side == 0)
		adr = all->tex.wst_adr;
	else if (side == 1)
		adr = all->tex.nrt_adr;
	else if (side == 2)
		adr = all->tex.est_adr;
	else if (side == 3)
		adr = all->tex.sth_adr;
	textr_y = ((int)all->tex.start) & (all->tex.res - 1);
	all->tex.start += all->tex.ratio;
	color = *((unsigned int *)(adr + (textr_y * all->tex.ll
			+ all->tex.textr_x * (all->tex.bpp / 8))));
	return (color);
}

int						draw_line(int start, int end, int color, t_all *all)
{
	while (start <= end)
		my_pixel_put(&(all->prg), all->tex.curr_x, start++, color);
	return (1);
}

int						draw_wall(int start, int end, int side, t_all *all)
{
	unsigned int color;

	while (start <= end)
	{
		color = get_color(all, side);
		my_pixel_put(&(all->prg), all->tex.curr_x, start++, color);
	}
	return (1);
}
