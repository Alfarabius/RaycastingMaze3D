/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:09:04 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 15:46:44 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	init_var_and_const(t_all *all)
{
	all->key_flag = NO_FLG;
	all->plr.plane_x = FOV;
	all->plr.plane_y = FOV;
	all->dta.spt_amt = 0;
}

static	void	plr_spd(t_all *all)
{
	all->plr.speed = (float)all->map.width_x / 15000;
	all->plr.rot_speed = (float)all->map.width_x / 30000;
	if (all->plr.speed > 0.08)
		all->plr.speed = 0.08;
	if (all->plr.rot_speed > 0.06)
		all->plr.rot_speed = 0.06;
}

static	int		quit(int button_code, t_all *all)
{
	(void)all;
	(void)button_code;
	exit(1);
	return (0);
}

void			prg_init(t_all *all, char **argv)
{
	if ((ft_strlen(argv[1]) < 5) ||
		!(ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 5)))
	{
		init_var_and_const(all);
		ft_parse_file(all, argv[1]);
		cube_init(all);
		plr_spd(all);
		if (argv[2] && (!(ft_strncmp(argv[2], "--save", 7))))
			make_screenshot(all->map.height_y, all->map.width_x, all);
		else if (argv[2] && ft_strncmp(argv[2], "--save", 7))
			error_handler("second arg isn`t --save");
		all->prg.win = mlx_new_window(all->prg.mlx, all->map.width_x,
											all->map.height_y, "cub3D");
		mlx_put_image_to_window(all->prg.mlx, all->prg.win,
											all->prg.img, 0, 0);
	}
	else
		error_handler("not *.cub");
}

int				main(int argc, char *argv[])
{
	t_all	all;

	if (argc > 1 && argc < 4)
	{
		prg_init(&all, argv);
		mlx_hook(all.prg.win, 2, 1L << 0, keypress_handler, &all);
		mlx_hook(all.prg.win, 3, 1L << 1, keyrelease_handler, &all);
		mlx_hook(all.prg.win, 17, 1L << 0, quit, &all);
		mlx_loop_hook(all.prg.mlx, loop_processor, &all);
		mlx_loop(all.prg.mlx);
	}
	else
		error_handler("arguments number");
	return (0);
}
