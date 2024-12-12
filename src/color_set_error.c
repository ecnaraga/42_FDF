/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:44:15 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:21:11 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ft_rgb_error(t_var *var, t_color color, int delta, int i)
{
	if (delta == 0)
	{
		var->color_inc[i] = 0;
		var->error_c_inc[i] = 0;
		var->error_c[i] = -0.5;
		if (i != RGB)
			var->c_inc[i] = ft_sign(color.d[i]);
	}
	else
	{
		var->color_inc[i] = (color.d[i]) / delta;
		var->error_c[i] = -0.5;
		if (i != RGB)
			var->c_inc[i] = ft_sign(color.d[i]);
		var->error_c_inc[i] = ft_abs(color.d[i]) / (float)delta
			- (float)ft_abs(var->color_inc[i]);
	}
}

static void	ft_set_var_error(t_var *var, t_color color, int delta)
{
	ft_rgb_error(var, color, delta, r);
	ft_rgb_error(var, color, delta, g);
	ft_rgb_error(var, color, delta, b);
}

void	ft_set_delta(t_color color, t_var *var, int ck_color0, int ck_color1)
{
	color.d[r] = color.c1[r] - color.c0[r];
	color.d[g] = color.c1[g] - color.c0[g];
	color.d[b] = color.c1[b] - color.c0[b];
	if (ck_color0 == y || ck_color1 == y)
	{
		if (var->dy > var->dx)
			ft_set_var_error(var, color, var->dy);
		else
			ft_set_var_error(var, color, var->dx);
	}
	else
	{
		color.d[RGB] = ft_abs(color.d[r]) + ft_abs(color.d[g])
			+ ft_abs(color.d[b]);
		if (var->dy > var->dx)
			ft_rgb_error(var, color, var->dy, RGB);
		else
			ft_rgb_error(var, color, var->dx, RGB);
	}
}
