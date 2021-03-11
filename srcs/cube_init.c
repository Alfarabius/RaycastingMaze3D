/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:16:29 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/11 15:57:09 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	int	init_sprite(t_all *all)
{
	if (!(all->dta.spt_img = mlx_xpm_file_to_image(all->prg.mlx,
			all->map.sprite, &all->dta.w_res, &all->dta.h_res)))
		return (error_handler("something with sprite img"));
	if (!(all->dta.spt_addr = mlx_get_data_addr(all->dta.spt_img,
			&all->dta.bpp, &all->dta.ll, &all->dta.end)))
		return (error_handler("something with sprite addres"));
	return (1);
}

static	int	textrs_validation(void *a1, void *a2, void *a3, void *a4)
{
	if (!a1 || !a2 || !a3 || !a4)
		return (error_handler("something with textures"));
	return (1);
}

static	int	init_textrs(t_all *all, t_atex *tex)
{
	tex->nrt.img = mlx_xpm_file_to_image(all->prg.mlx, all->map.north,
											&tex->nrt.x_wd, &tex->nrt.y_hg);
	(tex->sth.img = mlx_xpm_file_to_image(all->prg.mlx, all->map.south,
											&tex->sth.x_wd, &tex->sth.y_hg));
	(tex->wst.img = mlx_xpm_file_to_image(all->prg.mlx, all->map.west,
											&tex->wst.x_wd, &tex->wst.y_hg));
	(tex->est.img = mlx_xpm_file_to_image(all->prg.mlx, all->map.east,
											&tex->est.x_wd, &tex->est.y_hg));
	textrs_validation(tex->nrt.img, tex->sth.img, tex->wst.img, tex->est.img);
	(tex->nrt.adr = mlx_get_data_addr(tex->nrt.img, &tex->nrt.bpp,
											&tex->nrt.ll, &tex->nrt.end));
	(tex->sth.adr = mlx_get_data_addr(tex->sth.img, &tex->sth.bpp,
											&tex->sth.ll, &tex->sth.end));
	(tex->wst.adr = mlx_get_data_addr(tex->wst.img, &tex->wst.bpp,
											&tex->wst.ll, &tex->wst.end));
	(tex->est.adr = mlx_get_data_addr(tex->est.img, &tex->est.bpp,
											&tex->est.ll, &tex->est.end));
	textrs_validation(tex->nrt.adr, tex->sth.adr, tex->wst.adr, tex->est.adr);
	return (1);
}

void		cube_init(t_all *all)
{
	all->prg.mlx = mlx_init();
	if (!res_handler(all))
		error_handler("resolution error");
	init_textrs(all, &all->tex);
	init_sprite(all);
	all->prg.img = mlx_new_image(all->prg.mlx, all->map.width_x,
													all->map.height_y);
	all->prg.addr = mlx_get_data_addr(all->prg.img, &all->prg.bits_per_pixel,
								&all->prg.line_length, &all->prg.endian);
	draw_img(all);
}
