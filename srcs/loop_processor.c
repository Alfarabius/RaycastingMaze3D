/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:59:49 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/07 18:05:49 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void	close_prg(t_all *all)
{
	mlx_destroy_window(all->prg.mlx, all->prg.win);
	exit(1);
}

int				keypress_handler(int keycode, t_all *all)
{
	if (keycode == ESC)
		close_prg(all);
	else if (keycode == W)
		all->key_flag |= W_FLG;
	else if (keycode == S)
		all->key_flag |= S_FLG;
	else if (keycode == RIGHT)
		all->key_flag |= RIGHT_FLG;
	else if (keycode == LEFT)
		all->key_flag |= LEFT_FLG;
	else if (keycode == D)
		all->key_flag |= D_FLG;
	else if (keycode == A)
		all->key_flag |= A_FLG;
	return (keycode);
}

int				keyrelease_handler(int keycode, t_all *all)
{
	if (keycode == W)
		all->key_flag &= ~W_FLG;
	else if (keycode == S)
		all->key_flag &= ~S_FLG;
	else if (keycode == RIGHT)
		all->key_flag &= ~RIGHT_FLG;
	else if (keycode == LEFT)
		all->key_flag &= ~LEFT_FLG;
	else if (keycode == D)
		all->key_flag &= ~D_FLG;
	else if (keycode == A)
		all->key_flag &= ~A_FLG;
	return (keycode);
}

int				loop_processor(t_all *all)
{
	int		any;

	any = 0;
	if (all->key_flag & W_FLG)
		any = move_player(all, all->plr.speed, all->plr.speed);
	else if (all->key_flag & S_FLG)
		any = move_player(all, -all->plr.speed, -all->plr.speed);
	if (all->key_flag & D_FLG)
		any = strafe_player(all, all->plr.speed, all->plr.speed);
	else if (all->key_flag & A_FLG)
		any = strafe_player(all, -all->plr.speed, -all->plr.speed);
	if (all->key_flag & RIGHT_FLG)
		any = turn_player(all, all->plr.rot_speed);
	else if (all->key_flag & LEFT_FLG)
		any = turn_player(all, -all->plr.rot_speed);
	if (any)
	{
		draw_img(all);
		mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, all->prg.win);
		mlx_put_image_to_window(all->prg.mlx, all->prg.win, all->prg.img, 0, 0);
	}
	mlx_do_sync(all->prg.mlx);
	return (1);
}
