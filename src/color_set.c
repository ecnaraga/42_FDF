/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:25:48 by galambey          #+#    #+#             */
/*   Updated: 2023/08/31 17:21:27 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_set_rgb(int col, unsigned char *rgb, int *c)
{
		rgb[r] = col >> 16;
		rgb[g] = col >> 8;
		rgb[b] = col >> 0;
		c[r] = rgb[r];
		c[g] = rgb[g];
		c[b] = rgb[b];
}

void	ft_set_rgb_else(t_coord pt, int *c, t_coef co)
{
	if (pt.z < co.mid_z)
	{
		c[r] = 255 * (pt.z - co.min_z) / (co.mid_z - co.min_z);
		c[g] = 0;
		c[b] = 255;
	}
	else
	{
		c[r] = 255;
		c[g] = 0;
		c[b] = 255 * (co.max_z - pt.z) / (co.max_z - co.mid_z);
	}
}

static void	ft_set_color_dep(t_coord pt_0, t_var *var, t_coef co,
		t_color *color)
{
	if (pt_0.z == co.min_z || pt_0.z == co.max_z || pt_0.z == co.mid_z)
	{
		var->color_0 = (pt_0.z == co.min_z) * 0x0000FF + (pt_0.z == co.mid_z)
			* 0xFF00FF + (pt_0.z == co.max_z) * 0xFF0000;
		ft_set_rgb(var->color_0, color->rgb0, color->c0);
	}
	else
	{
		ft_set_rgb_else(pt_0, color->c0, co);
		var->color_0 = ((color->c0[r] * 16 * 16) + color->c0[g]) * 16 * 16
			+ color->c0[b];
	}
}

static void	ft_set_color_arr(t_coord pt_1, t_var *var, t_coef co,
		t_color *color)
{
	if (pt_1.z == co.min_z || pt_1.z == co.max_z || pt_1.z == co.mid_z)
	{
		var->color_1 = (pt_1.z == co.min_z) * 0x0000FF + (pt_1.z == co.mid_z)
			* 0xFF00FF + (pt_1.z == co.max_z) * 0xFF0000 + 0;
		ft_set_rgb(var->color_1, color->rgb1, color->c1);
	}
	else
	{
		ft_set_rgb_else(pt_1, color->c1, co);
		var->color_1 = ((color->c1[r] * 16 * 16) + color->c1[g]) * 16 * 16
			+ color->c1[b];
	}
}

void	ft_define_color(t_coord pt_0, t_coord pt_1, t_var *var, t_coef co)
{
	t_color	color;

	if (pt_0.ck_color == y)
	{
		var->color_0 = pt_0.color;
		ft_set_rgb(var->color_0, color.rgb0, color.c0);
	}
	else if (co.min_z == co.max_z)
		var->color_0 = 0x0000FF;
	else
		ft_set_color_dep(pt_0, var, co, &color);
	if (pt_1.ck_color == y)
	{
		var->color_1 = pt_1.color;
		ft_set_rgb(var->color_1, color.rgb1, color.c1);
	}
	else if (co.min_z == co.max_z)
		var->color_1 = 0x0000FF;
	else
		ft_set_color_arr(pt_1, var, co, &color);
	if (var->color_0 != var->color_1)
		ft_set_delta(color, var, pt_0.ck_color, pt_1.ck_color);
}
