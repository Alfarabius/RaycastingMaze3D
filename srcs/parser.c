/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:39:51 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 16:16:18 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			is_num(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

static	int	parse_path(char flag, char **str, t_all *all)
{
	char	*acc;
	int		i;

	i = 0;
	while (str[i])
		i++;
	acc = ft_strdup(str[1]);
	if (i > 2 || i < 2 || !acc || ft_strlen(acc) < 5 ||
		(ft_strncmp(&acc[ft_strlen(acc) - 4], ".xpm", 5)))
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

static	int	ft_parse_line(char *str, t_all *all)
{
	char	**acc;

	if (*str == ' ')
		return (error_handler("line start is space"));
	acc = ft_split(str, ' ');
	if (acc[0] == NULL)
		return (free_tmp(acc, 0) - 1);
	else if (!ft_strncmp(acc[0], "R", 2))
		return (parse_resolution(acc, all));
	else if (!ft_strncmp(acc[0], "S", 2))
		return (parse_path('S', acc, all));
	else if (!ft_strncmp(acc[0], "F", 2))
		return (parse_color('F', acc, all));
	else if (!ft_strncmp(acc[0], "C", 2))
		return (parse_color('C', acc, all));
	else if (!ft_strncmp(acc[0], "NO", 3))
		return (parse_path('n', acc, all));
	else if (!ft_strncmp(acc[0], "SO", 3))
		return (parse_path('s', acc, all));
	else if (!ft_strncmp(acc[0], "WE", 3))
		return (parse_path('w', acc, all));
	else if (!ft_strncmp(acc[0], "EA", 3))
		return (parse_path('e', acc, all));
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

int			ft_parse_file(t_all *all, char *str)
{
	char	*line;
	t_list	*map_lst;
	int		count;
	int		err;

	count = 0;
	err = 0;
	map_lst = NULL;
	if ((all->fd = open(str, O_RDONLY)) == -1)
		return (error_handler("fd open return -1"));
	while ((err = get_next_line(all->fd, &line)))
	{
		if (err == -1)
			return (error_handler("gnl return -1"));
		count < 8 ? count += ft_parse_line(line, all) : 0;
		count == 9 ? ft_lstadd_back(&map_lst, ft_lstnew(line)) : 0;
		count < 9 ? free(line) : 0;
		count == 8 ? count += 1 : 0;
	}
	ft_lstadd_back(&map_lst, ft_lstnew(line));
	return (config_cube(map_lst, all));
}
