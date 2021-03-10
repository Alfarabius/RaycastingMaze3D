/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 13:10:29 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 16:18:18 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	qsort_sprites(t_dta *dta, int beg, int end)
{
	int		left;
	int		right;
	float	mid;
	t_spt	tmp;

	left = beg;
	right = end;
	mid = dta->spt_arr[(beg + end) / 2].dist;
	while (left <= right)
	{
		while (dta->spt_arr[left].dist > mid)
			left++;
		while (dta->spt_arr[right].dist < mid)
			right--;
		if (left <= right)
		{
			tmp = dta->spt_arr[left];
			dta->spt_arr[left++] = dta->spt_arr[right];
			dta->spt_arr[right--] = tmp;
		}
	}
	if (beg < right)
		qsort_sprites(dta, beg, right);
	if (left < end)
		qsort_sprites(dta, left, end);
}

static	void	calc_sprite(t_dta *spr, t_all *all, t_plr *plr, int i)
{
	spr->rel_x = spr->spt_arr[i].x - plr->x_pos;
	spr->rel_y = spr->spt_arr[i].y - plr->y_pos;
	spr->inv = 1.0 / (plr->plane_x * plr->y_dir - plr->plane_y * plr->x_dir);
	spr->trns_x = spr->inv *
		(plr->y_dir * spr->rel_x - plr->x_dir * spr->rel_y);
	spr->trns_y = spr->inv * (plr->plane_x *
		spr->rel_y - plr->plane_y * spr->rel_x);
	spr->scrn_x = (int)((all->map.width_x / 2) *
		(1 + spr->trns_x / spr->trns_y));
	spr->height = abs((int)(all->map.height_y / spr->trns_y));
	spr->start_y = (all->map.height_y / 2) - spr->height / 2;
	if (spr->start_y < 0)
		spr->start_y = 0;
	spr->end_y = (all->map.height_y / 2) + spr->height / 2;
	if (spr->end_y >= (int)all->map.height_y)
		spr->end_y = all->map.height_y - 1;
	spr->width = abs((int)(all->map.height_y / spr->trns_y));
	spr->start_x = spr->scrn_x - spr->width / 2;
	if (spr->start_x < 0)
		spr->start_x = 0;
	spr->end_x = spr->scrn_x + spr->width / 2;
	if (spr->end_x >= (int)all->map.width_x)
		spr->end_x = all->map.width_x - 1;
}

static	void	draw_sprite(t_dta *spr, t_all *all, float *z_buf, int x)
{
	int				y;
	unsigned int	color;

	y = spr->start_y;
	spr->img_x = (int)((x - (spr->scrn_x - spr->width / 2)) *
					spr->w_res / spr->width);
	if (spr->trns_y > 0 && x > 0 &&
		x < (int)all->map.width_x && spr->trns_y < z_buf[x])
		while (y < spr->end_y)
		{
			spr->img_y = (int)(((y - all->map.height_y * 0.5 +
				spr->height * 0.5) * spr->h_res) / spr->height);
			color = *((unsigned int *)(spr->spt_addr +
				(spr->img_y * spr->ll + spr->img_x * (spr->bpp / 8))));
			if (color != WHITE)
				my_pixel_put(&(all->prg), x, y, color);
			y++;
		}
}

int				draw_sprites(t_all *all, t_plr *plr, float *z_buf, t_dta *spr)
{
	int	i;
	int	x;

	i = 0;
	qsort_sprites(spr, 0, spr->spt_amt - 1);
	while (i < all->dta.spt_amt)
	{
		all->dta.spt_arr[i].dist = (plr->x_pos - spr->spt_arr[i].x) *
		(plr->x_pos - spr->spt_arr[i].x) + (plr->y_pos - spr->spt_arr[i].y) *
			(plr->y_pos - spr->spt_arr[i].y);
		i++;
	}
	i = 0;
	while (i < all->dta.spt_amt)
	{
		calc_sprite(spr, all, plr, i);
		x = spr->start_x;
		while (x < spr->end_x)
			draw_sprite(spr, all, z_buf, x++);
		i++;
	}
	return (1);
}
