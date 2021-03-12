/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:39:51 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/12 11:55:19 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			flags_checker(int flg, char key, t_all *all)
{
	int flg_add;

	if (key == 's')
		flg_add = STH_F;
	if (key == 'n')
		flg_add = NRT_F;
	if (key == 'w')
		flg_add = WST_F;
	if (key == 'e')
		flg_add = EST_F;
	if (key == 'S')
		flg_add = SPR_F;
	if (key == 'C')
		flg_add = CEL_F;
	if (key == 'F')
		flg_add = FLR_F;
	if (key == 'R')
		flg_add = RES_F;
	if (flg & flg_add)
		return (error_handler("Double param"));
	all->map.p_cnt += 1;
	return (flg_add);
}

static	int	parse_path(char flag, char **str, t_all *all, int *flg)
{
	char	*acc;
	int		i;

	i = 0;
	*flg |= flags_checker(*flg, flag, all);
	while (str[i])
		i++;
	if (i > 2 || i < 2 || !(acc = ft_strdup(str[1])) ||
		!valid_file(".xpm", acc, 5))
		return (free_tmp(str, 1));
	if (flag == 'n')
		all->map.north = acc;
	else if (flag == 's')
		all->map.south = acc;
	else if (flag == 'w')
		all->map.west = acc;
	else if (flag == 'e')
		all->map.east = acc;
	else if (flag == 'S')
		all->map.sprite = acc;
	else
		return (free_tmp(str, 1));
	return (free_tmp(str, 0));
}

static	int	parse_line(char *str, t_all *all, int *flg)
{
	char	**acc;

	if (*str == ' ')
		return (error_handler("line start is space"));
	acc = ft_split(str, ' ');
	if (acc[0] == NULL)
		return (free_tmp(acc, 0) - 1);
	else if (!ft_strncmp(acc[0], "R", 2))
		return (parse_resolution(acc, all, flg));
	else if (!ft_strncmp(acc[0], "S", 2))
		return (parse_path('S', acc, all, flg));
	else if (!ft_strncmp(acc[0], "F", 2))
		return (parse_color('F', acc, all, flg));
	else if (!ft_strncmp(acc[0], "C", 2))
		return (parse_color('C', acc, all, flg));
	else if (!ft_strncmp(acc[0], "NO", 3))
		return (parse_path('n', acc, all, flg));
	else if (!ft_strncmp(acc[0], "SO", 3))
		return (parse_path('s', acc, all, flg));
	else if (!ft_strncmp(acc[0], "WE", 3))
		return (parse_path('w', acc, all, flg));
	else if (!ft_strncmp(acc[0], "EA", 3))
		return (parse_path('e', acc, all, flg));
	return (free_tmp(acc, 1));
}

static	int	config_cube(t_list *map_lst, t_all *all)
{
	if (!create_map(&all->map, map_lst) ||
						!valid_map(all->map.mini_map))
		return (error_handler("map are not valid or did not created"));
	ft_lstclear(&map_lst, free);
	get_player_start_position(all);
	get_sprites_map(all);
	close(all->fd);
	return (0);
}

int			parse_file(t_all *all, char *str)
{
	char	*line;
	t_list	*map_lst;
	int		err;
	int		flg;

	flg = NO_FLG;
	err = 0;
	map_lst = NULL;
	if ((all->fd = open(str, O_RDONLY)) == -1)
		return (error_handler("fd open return -1"));
	while ((err = get_next_line(all->fd, &line)))
	{
		if (err == -1)
			return (error_handler("gnl return -1"));
		flg == ALL_FLG ? ft_lstadd_back(&map_lst, ft_lstnew(line)) : 0;
		flg != ALL_FLG ? parse_line(line, all, &flg) : 0;
		all->map.p_cnt < 9 ? free(line) : 0;
		flg == ALL_FLG ? all->map.p_cnt += 1 : 0;
	}
	ft_lstadd_back(&map_lst, ft_lstnew(line));
	return (config_cube(map_lst, all));
}
