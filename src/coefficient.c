/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coefficient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:23:34 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:20:38 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ft_z_info(t_cont coord, t_coef *co)
{
	int		i;
	t_coord	*pt;

	while (coord.first)
	{
		pt = (t_coord *)coord.first->data;
		i = -1;
		if (co->alt == NR)
		{
			co->min_z = pt[0].z;
			co->max_z = pt[0].z;
		}
		while (++i < pt[0].len)
		{
			if (pt[i].z > co->max_z)
				co->max_z = pt[i].z;
			if (pt[i].z < co->min_z)
				co->min_z = pt[i].z;
			co->alt = (SAME_Z) * (co->min_z == co->max_z) + (DIFF_Z)
				* (co->min_z != co->max_z);
		}
		coord.first = coord.first->next;
	}
}

static void	ft_adjust_height(t_coef *co, int line, int col)
{
	double	tmp;

	tmp = HEIGHT - (col - 1) * co->pix * sin((0.52359877559 + co->rot));
	tmp = (tmp - (line - 1) * co->pix * sin((0.52359877559 - co->rot))) / 2;
	while (tmp < 50.0)
	{
		co->pix -= 1;
		tmp = HEIGHT - (col - 1) * co->pix * sin((0.52359877559 + co->rot));
		tmp = (tmp - (line - 1) * co->pix * sin((0.52359877559 - co->rot))) / 2;
	}
}

static void	ft_adjust_width(t_coef *co, int line, int col)
{
	double	tmp;

	tmp = WIDTH - (col - 1) * co->pix * cos((0.52359877559 + co->rot));
	tmp = (tmp + (line - 1) * co->pix * cos((0.52359877559 - co->rot))) / 2;
	while (tmp < 10.0 || tmp > WIDTH - 10)
	{
		co->pix -= 1;
		tmp = WIDTH - (col - 1) * co->pix * cos((0.52359877559 + co->rot));
		tmp = (tmp + (line - 1) * co->pix * cos((0.52359877559 - co->rot))) / 2;
	}
}

static void	ft_get_copix(t_cont *coord, t_coef *co)
{
	t_coord	*pt;

	co->pix = 20;
	pt = (t_coord *)coord->first->data;
	ft_adjust_height(co, coord->size, pt[0].len);
	ft_adjust_width(co, coord->size, pt[0].len);
	if (co->pix < 2)
		co->pix = 2;
	co->pix_ref = co->pix;
}

void	ft_get_coef(t_cont *coord, t_coef *co)
{
	int	i;

	co->rot = 0.00;
	co->alt = NR;
	co->z_var = 1;
	co->z_var_ref = 1;
	co->proj = isometric;
	i = -1;
	while (++i <= 6)
		co->mv[i] = 0;
	ft_get_copix(coord, co);
	ft_z_info(*coord, co);
}
