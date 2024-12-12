/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:29:20 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:20:46 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ft_inc_error(t_color *color, t_var *var, int x1, int x2)
{
	if (color->c0[x1] < 255)
		color->c0[x1] += 1;
	else if (color->c0[x2] > 0)
		color->c0[x2] -= 1;
	var->error_c[RGB] -= 1;
}

static void	ft_fade_blue_red(t_color *color, t_var *var, int x1, int x2)
{
	int	temp;

	if (var->error_c[RGB] >= 0)
		ft_inc_error(color, var, x1, x2);
	if (color->c0[x1] < 255)
	{
		if (color->c0[x1] + var->color_inc[RGB] <= 255)
			color->c0[x1] += var->color_inc[RGB];
		else
		{
			temp = var->color_inc[RGB] - (255 - color->c0[x1]);
			color->c0[x1] = 255;
			color->c0[x2] -= temp;
		}
	}
	else if (color->c0[x2] > 0)
	{
		if (color->c0[x2] - var->color_inc[RGB] >= 0)
			color->c0[x2] -= var->color_inc[RGB];
		else
			color->c0[x2] = 0;
	}
	var->error_c[RGB] += var->error_c_inc[RGB];
}

void	ft_put_color(t_coord *pt, t_var *var, int ck_color_1)
{
	t_color	color;

	ft_set_rgb(pt->color, color.rgb0, color.c0);
	if ((pt->ck_color == y || ck_color_1 == y)
		&& var->color_0 != var->color_1)
	{
		ft_set_rgb(var->color_1, color.rgb1, color.c1);
		ft_color_fade(&color, var);
	}
	else if (pt->ck_color == n && ck_color_1 == n)
	{
		if (var->dz > 0)
			ft_fade_blue_red(&color, var, r, b);
		if (var->dz < 0)
			ft_fade_blue_red(&color, var, b, r);
	}
	pt->color = ((color.c0[r] * 16 * 16) + color.c0[g]) * 16 * 16
		+ color.c0[b];
}
