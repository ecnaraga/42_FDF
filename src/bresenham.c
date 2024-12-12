/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:05:09 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 15:14:01 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ft_draw_vertical(t_coord pt_0, t_coord pt_1, t_img *img, t_var var)
{
	t_coord	pt;

	pt.x_p = pt_0.x_p;
	pt.y_p = pt_0.y_p;
	pt.color = var.color_0;
	pt.ck_color = pt_0.ck_color;
	while (pt.y_p != pt_1.y_p + var.y_inc)
	{
		if (pt.y_p >= 0 && pt.y_p <= HEIGHT && pt.x_p >= 0 && pt.x_p <= WIDTH)
			ft_img_pix_put(img, pt);
		ft_put_color(&pt, &var, pt_1.ck_color);
		pt.y_p += var.y_inc;
	}
}

static void	ft_draw_horizontal(t_coord pt_0, t_coord pt_1, t_img *img,
		t_var var)
{
	t_coord	pt;

	pt.x_p = pt_0.x_p;
	pt.y_p = pt_0.y_p;
	pt.color = var.color_0;
	pt.ck_color = pt_0.ck_color;
	while (pt.x_p != pt_1.x_p + var.x_inc)
	{
		if (pt.x_p >= 0 && pt.x_p <= WIDTH && pt.y_p >= 0 && pt.y_p <= HEIGHT)
			ft_img_pix_put(img, pt);
		ft_put_color(&pt, &var, pt_1.ck_color);
		pt.x_p += var.x_inc;
	}
}

static void	ft_draw_diag_h(t_coord pt_0, t_coord pt_1, t_img *img, t_var var)
{
	t_coord	pt;

	pt.x_p = pt_0.x_p;
	pt.y_p = pt_0.y_p;
	pt.color = var.color_0;
	pt.ck_color = pt_0.ck_color;
	var.delta = 2 * var.dy;
	var.error = -var.dx;
	var.error_inc = -2 * var.dx;
	while (pt.x_p != pt_1.x_p + var.x_inc)
	{
		if (pt.x_p >= 0 && pt.x_p <= WIDTH && pt.y_p >= 0 && pt.y_p <= HEIGHT)
			ft_img_pix_put(img, pt);
		var.error += var.delta;
		ft_put_color(&pt, &var, pt_1.ck_color);
		if (var.error >= 0)
		{
			pt.y_p += var.y_inc;
			var.error += var.error_inc;
		}
		pt.x_p += var.x_inc;
	}
}

static void	ft_draw_diag_v(t_coord pt_0, t_coord pt_1, t_img *img, t_var var)
{
	t_coord	pt;

	pt.x_p = pt_0.x_p;
	pt.y_p = pt_0.y_p;
	pt.color = var.color_0;
	pt.ck_color = pt_0.ck_color;
	var.delta = 2 * var.dx;
	var.error = -var.dy;
	var.error_inc = -2 * var.dy;
	while (pt.y_p != pt_1.y_p + var.y_inc)
	{
		if (pt.x_p >= 0 && pt.x_p <= WIDTH && pt.y_p >= 0 && pt.y_p <= HEIGHT)
			ft_img_pix_put(img, pt);
		var.error += var.delta;
		ft_put_color(&pt, &var, pt_1.ck_color);
		if (var.error >= 0)
		{
			pt.x_p += var.x_inc;
			var.error += var.error_inc;
		}
		pt.y_p += var.y_inc;
	}
}

void	ft_draw_line(t_img *img, t_coord pt_0, t_coord pt_1, t_coef *co)
{
	t_var	var;

	ft_final_coord(&pt_0, &pt_1, co);
	var.dx = pt_1.x_p - pt_0.x_p;
	var.dy = pt_1.y_p - pt_0.y_p;
	var.dz = pt_1.z - pt_0.z;
	var.x_inc = ft_sign(var.dx);
	var.y_inc = ft_sign(var.dy);
	var.dx = ft_abs(var.dx);
	var.dy = ft_abs(var.dy);
	ft_define_color(pt_0, pt_1, &var, *co);
	if (var.dy == 0)
		ft_draw_horizontal(pt_0, pt_1, img, var);
	else if (var.dx == 0)
		ft_draw_vertical(pt_0, pt_1, img, var);
	else if (var.dx >= var.dy)
		ft_draw_diag_h(pt_0, pt_1, img, var);
	else
		ft_draw_diag_v(pt_0, pt_1, img, var);
}
