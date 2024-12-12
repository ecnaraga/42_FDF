/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 08:46:26 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:21:46 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_reset(t_coef *co)
{
	int	i;

	co->rot = 0.00;
	co->pix = co->pix_ref;
	co->z_var = 1;
	co->z_var_ref = 1;
	i = -1;
	while (++i <= 6)
		co->mv[i] = 0;
}

int	ft_handle_no_event(t_win *win)
{
	if (win->img1.co.proj == isometric)
		ft_img_iso(&win->img1, win->coord);
	else
		ft_img_para(&win->img1, win->coord);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img1.mlx_img,
		0, 0);
	return (0);
}

static void	ft_transform(int keysym, t_coef *co)
{
	ft_ev_translate(keysym, co->mv);
	ft_ev_zoom(keysym, co);
	ft_ev_rotate(keysym, &co->rot);
	ft_ev_elevation(keysym, co);
	ft_ev_projection(keysym, co);
}

int	ft_handle_event(int keysym, t_win *win)
{
	t_img	img2;
	void	*temp;

	if (keysym != XK_Escape)
	{
		img2.mlx_img = mlx_new_image(win->mlx_ptr, WIDTH, HEIGHT);
		if (!img2.mlx_img)
			ft_exit(win);
		img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len,
				&img2.endian);
		img2.co = win->img1.co;
		ft_transform(keysym, &img2.co);
		temp = win->img1.mlx_img;
		win->img1 = img2;
		if (win->img1.co.proj == isometric)
			ft_img_iso(&win->img1, win->coord);
		else
			ft_img_para(&win->img1, win->coord);
		mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img1.mlx_img,
			0, 0);
		mlx_destroy_image(win->mlx_ptr, temp);
	}
	if (keysym == XK_Escape)
		ft_exit(win);
	return (0);
}
