/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:16:29 by mrosie            #+#    #+#             */
/*   Updated: 2021/02/28 17:13:17 by mrosie           ###   ########.fr       */
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

static	int	init_textrs(t_all *all, t_tex *tex)
{
	tex->nrt_img = mlx_xpm_file_to_image(all->prg.mlx, all->map.north,
											&all->tex.res, &all->tex.res);
	(tex->sth_img = mlx_xpm_file_to_image(all->prg.mlx, all->map.south,
											&all->tex.res, &all->tex.res));
	(tex->wst_img = mlx_xpm_file_to_image(all->prg.mlx, all->map.west,
											&all->tex.res, &all->tex.res));
	(tex->est_img = mlx_xpm_file_to_image(all->prg.mlx, all->map.east,
											&all->tex.res, &all->tex.res));
	textrs_validation(tex->nrt_img, tex->sth_img, tex->wst_img, tex->est_img);
	(tex->nrt_adr = mlx_get_data_addr(all->tex.nrt_img, &all->tex.bpp,
											&all->tex.ll, &all->tex.end));
	(tex->sth_adr = mlx_get_data_addr(all->tex.sth_img, &all->tex.bpp,
											&all->tex.ll, &all->tex.end));
	(tex->wst_adr = mlx_get_data_addr(all->tex.wst_img, &all->tex.bpp,
											&all->tex.ll, &all->tex.end));
	(tex->est_adr = mlx_get_data_addr(all->tex.est_img, &all->tex.bpp,
											&all->tex.ll, &all->tex.end));
	textrs_validation(tex->nrt_adr, tex->sth_adr, tex->wst_adr, tex->est_adr);
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
