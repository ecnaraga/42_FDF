/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_map_fade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:48:51 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:20:59 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ft_inc_rgb(int *rgb, int rgb_ref, int rgbInc)
{
	if (*rgb + rgbInc <= rgb_ref)
		*rgb += rgbInc;
	else
		*rgb = rgb_ref;
}

static void	ft_dec_rgb(int *rgb, int rgb_ref, int rgbInc)
{
	if (*rgb + rgbInc >= rgb_ref)
		*rgb += rgbInc;
	else
		*rgb = rgb_ref;
}

static void	ft_rgb_fade(t_color *color, t_var *var, int rgb)
{
	if (var->error_c[rgb] >= 0)
	{
		if (color->c0[rgb] != color->c1[rgb])
			color->c0[rgb] += var->c_inc[rgb];
		var->error_c[rgb] -= 1;
	}
	if (var->c_inc[rgb] == 1)
		ft_inc_rgb(&color->c0[rgb], color->c1[rgb], var->color_inc[rgb]);
	else if (var->c_inc[rgb] == -1)
		ft_dec_rgb(&color->c0[rgb], color->c1[rgb], var->color_inc[rgb]);
	var->error_c[rgb] += var->error_c_inc[rgb];
}

void	ft_color_fade(t_color *color, t_var *var)
{
	ft_rgb_fade(color, var, r);
	ft_rgb_fade(color, var, g);
	ft_rgb_fade(color, var, b);
}
