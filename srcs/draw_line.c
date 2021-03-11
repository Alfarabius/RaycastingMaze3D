/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:01:14 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/11 18:19:27 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	unsigned int	get_color(t_tex *side)
{
	unsigned int	color;
	int				textr_y;

	textr_y = ((int)side->start) & (side->y_hg - 1);
	side->start += side->ratio;
	color = *((unsigned int *)(side->adr + (textr_y * side->ll
		+ side->textr_x * (side->bpp / 8))));
	return (color);
}

int						draw_line(int start, int end, int color, t_all *all)
{
	while (start <= end)
		my_pixel_put(&(all->prg), all->tex.curr_x, start++, color);
	return (1);
}

int						draw_wall(int start, int end, t_tex side, t_all *all)
{
	while (start <= end)
		my_pixel_put(&(all->prg), all->tex.curr_x, start++, get_color(&side));
	return (1);
}
