/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:16:33 by mrosie            #+#    #+#             */
/*   Updated: 2021/02/17 15:40:09 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	int		create_sprites_array(t_all *all, t_list *spt_lst)
{
	t_list	*tmp;
	t_spt	*start;

	if (!(all->dta.spt_arr = (t_spt *)malloc(sizeof(t_spt) * all->dta.spt_amt)))
		return (0);
	start = all->dta.spt_arr;
	while (spt_lst)
	{
		*all->dta.spt_arr = *(t_spt *)spt_lst->content;
		all->dta.spt_arr++;
		tmp = spt_lst;
		spt_lst = spt_lst->next;
		ft_lstdelone(tmp, free);
	}
	all->dta.spt_arr = start;
	return (1);
}

static	t_spt	*add_sprite(t_all *all, int y, int x)
{
	t_spt *new_spt;

	if (!(new_spt = (t_spt *)malloc(sizeof(t_spt))))
		return (NULL);
	all->dta.spt_amt += 1;
	new_spt->y = y + 0.5;
	new_spt->x = x + 0.5;
	new_spt->dist = (all->plr.x_pos - x) * (all->plr.x_pos - x) +
			(all->plr.y_pos - y) * (all->plr.y_pos - y);
	return (new_spt);
}

int				get_sprites_map(t_all *all)
{
	int		y;
	int		x;
	t_list	*spt_lst;
	t_spt	*spt;

	y = 0;
	spt_lst = NULL;
	while (all->map.mini_map[y])
	{
		x = 0;
		while (all->map.mini_map[y][x])
		{
			if (all->map.mini_map[y][x] == '2')
			{
				if (!(spt = add_sprite(all, y, x)))
					return (error_handler("memerror with new sprite"));
				ft_lstadd_back(&spt_lst, ft_lstnew(spt));
			}
			x++;
		}
		y++;
	}
	if (!(create_sprites_array(all, spt_lst)))
		return (error_handler("sprites array not created"));
	return (1);
}
