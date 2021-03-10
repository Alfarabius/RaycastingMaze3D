/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:26:47 by mrosie            #+#    #+#             */
/*   Updated: 2021/03/10 16:27:02 by mrosie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	create_map(t_map *map, t_list *lst)
{
	int i;

	i = 0;
	if (!(map->mini_map = (char **)malloc(sizeof(char *) *
		(ft_lstsize(lst) + 1))))
		return (0);
	while (lst)
	{
		if (!(map->mini_map[i] = ft_strdup((char *)lst->content)))
			return (0);
		lst = lst->next;
		i++;
	}
	map->mini_map[i] = NULL;
	return (1);
}
