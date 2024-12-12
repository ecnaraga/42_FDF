/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:33:13 by galambey          #+#    #+#             */
/*   Updated: 2023/08/31 17:21:58 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_fdf(t_cont coord)
{
	t_win	win;

	win.mlx_ptr = mlx_init();
	if (!win.mlx_ptr)
	{
		lst_two_clear(&coord.first, del);
		exit(1);
	}
	win.win_ptr = mlx_new_window(win.mlx_ptr, WIDTH, HEIGHT, "fdf");
	if (!win.win_ptr)
		ft_exit_bis(&coord, &win);
	win.img1.mlx_img = mlx_new_image(win.mlx_ptr, WIDTH, HEIGHT);
	if (!win.img1.mlx_img)
		ft_exit_bis(&coord, &win);
	win.img1.addr = mlx_get_data_addr(win.img1.mlx_img, &win.img1.bpp,
			&win.img1.line_len, &win.img1.endian);
	win.coord = coord;
	ft_get_coef(&coord, &win.img1.co);
	mlx_loop_hook(win.mlx_ptr, &ft_handle_no_event, &win);
	mlx_hook(win.win_ptr, KeyPress, KeyPressMask, &ft_handle_event, &win);
	mlx_hook(win.win_ptr, DestroyNotify, StructureNotifyMask, &ft_exit, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
