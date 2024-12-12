/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:48:20 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 16:52:32 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	del(void *content)
{
	free(content);
	return ;
}

void	ft_error_list(t_cont coord, char *line, char **array, int fd)
{
	if (line)
		free(line);
	if (array)
		ft_free_array(array);
	if (coord.first)
		lst_two_clear(&coord.first, del);
	close(fd);
	exit(1);
}

void	*ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

int	ft_exit_bis(t_cont *coord, t_win *win)
{
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
	}
	lst_two_clear(&coord->first, del);
	exit(1);
}

int	ft_exit(t_win *win)
{
	lst_two_clear(&win->coord.first, del);
	if (!win->mlx_ptr)
	{
		exit(1);
	}
	mlx_destroy_image(win->mlx_ptr, win->img1.mlx_img);
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	mlx_destroy_display(win->mlx_ptr);
	free(win->mlx_ptr);
	exit(0);
}
