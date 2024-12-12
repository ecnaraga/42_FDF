/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:04:39 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:22:51 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	ft_coord(t_coord *elem, int ord, int abs, char *height)
{
	int	error;

	error = 0;
	elem->x = abs;
	elem->y = ord;
	ft_atoi_parse_z_and_color(height, &error, elem);
	if (elem->z > 1000)
		elem->z = 1000;
	else if (elem->z < -1000)
		elem->z = -1000;
	if (error == E_ERR)
		return (E_ERR);
	return (E_OK);
}

static int	ft_map_error(t_coord *tab_pt)
{
	if (tab_pt)
		free(tab_pt);
	return (E_ERR);
}

int	ft_lstmap_coord(t_cont *coord, char **array, int j, int *check)
{
	t_coord		*tab_pt;
	t_lst_two	*new;
	int			len_array;
	int			i;

	len_array = ft_arraylen(array);
	tab_pt = malloc(sizeof(t_coord) * ft_arraylen(array));
	if (!tab_pt || len_array == 0)
		return (ft_map_error(tab_pt));
	i = -1;
	while (++i < len_array && array[i][0] != '\n')
	{
		if (ft_coord(&tab_pt[i], j, i, array[i]) == E_ERR)
			return (ft_map_error(tab_pt));
	}
	tab_pt[0].len = len_array;
	if (*check != V_DFT && *check != len_array)
		return (ft_map_error(tab_pt));
	*check = len_array;
	new = lst_two_addnew(tab_pt);
	if (!new)
		return (ft_map_error(tab_pt));
	lst_two_addback(coord, new);
	return (E_OK);
}

t_cont	ft_recup_map(int fd)
{
	char	*line;
	char	**array;
	t_cont	coord;
	int		j;
	int		check;

	j = 0;
	coord.first = NULL;
	coord.size = 0;
	check = V_DFT;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		array = ft_split_isspace(line);
		if (!array)
			ft_error_list(coord, line, array, fd);
		if (ft_lstmap_coord(&coord, array, j, &check) == E_ERR)
			ft_error_list(coord, line, array, fd);
		ft_free_array(array);
		free(line);
		j++;
	}
	return (coord);
}
