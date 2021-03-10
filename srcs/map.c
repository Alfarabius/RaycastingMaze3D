/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:22:34 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 16:30:30 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	int	map_vars_init(t_val *m)
{
	m->col = 0;
	m->plr = 0;
	m->len = 0;
	m->row = 0;
	return (1);
}

static	int	check_around(char **map, int col, int row, int *plr)
{
	int		valid;
	size_t	prev_len;
	size_t	next_len;

	if (ft_strchr("NSWE", map[row][col]))
		*plr += 1;
	prev_len = ft_strlen(map[row - 1]) - 1;
	next_len = ft_strlen(map[row + 1]) - 1;
	if ((int)prev_len < col || col > (int)next_len)
		return (0);
	valid = 1;
	map[row - 1][col] == ' ' ? valid = 0 : 0;
	map[row][col + 1] == ' ' ? valid = 0 : 0;
	map[row][col - 1] == ' ' ? valid = 0 : 0;
	map[row + 1][col] == ' ' ? valid = 0 : 0;
	return (valid);
}

static	int	check_terminal(char **map, int row)
{
	int		last;
	int		col;

	last = 0;
	col = 0;
	while (map[last])
		last++;
	if (last == row)
		return (0);
	while (map[row][col])
	{
		if (map[row][col] != '1' && map[row][col] != ' ')
			return (0);
		col++;
	}
	col = 0;
	while (map[last - 1][col])
	{
		if (map[last - 1][col] != '1' && map[last - 1][col] != ' ')
			return (0);
		col++;
	}
	return (1);
}

static	int	no_empty_lines(char **map, int *strt)
{
	int		row;
	char	map_start;

	row = 0;
	map_start = 0;
	while (map[row])
	{
		if (!map_start && map[row][0] == '\0')
			*strt += 1;
		if (!map_start && map[row][0] != '\0')
			map_start = 1;
		if (map[row][0] == '\0' && map_start && map[row + 1]
									&& map[row + 1][0] != '\0')
			return (0);
		row++;
	}
	return (1);
}

int			valid_map(char **map)
{
	t_val	m;

	map_vars_init(&m);
	if (!no_empty_lines(map, &m.row) || !check_terminal(map, m.row))
		return (error_handler("not valid map: /0 or terminal"));
	while (map[m.row])
	{
		m.col = 0;
		m.len = ft_strlen(map[m.row]);
		if ((m.len > 0 && map[m.row][0] != '1' && map[m.row][0] != ' ') ||
		(m.len > 0 && map[m.row][(int)m.len - 1] != '1' &&
			map[m.row][m.len - 1] != ' '))
			return (error_handler("not valid map: not 1 or ' ' on terminal"));
		while (map[m.row][m.col])
		{
			if (!ft_strchr("012 NSWE", map[m.row][m.col]))
				return (error_handler("nvm: wrong symbol in map"));
			if (ft_strchr("02NSWE", map[m.row][m.col]))
				if (!check_around(map, m.col, m.row, &m.plr))
					return (error_handler("nwm: fail around test"));
			m.col++;
		}
		m.row++;
	}
	return (m.plr == 1 ? 1 : 0);
}
