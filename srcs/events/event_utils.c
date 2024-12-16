/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:08:54 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 14:14:50 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	ft_ev_translate(int keysym, int *mv)
{
	if (keysym == XK_Up)
	{
		mv[UD] -= 10;
		mv[U] = 1;
	}
	else if (keysym == XK_Down)
	{
		mv[UD] += 10;
		mv[D] = 1;
	}
	else if (keysym == XK_Right)
	{
		mv[RL] += 10;
		mv[R] = 1;
	}
	else if (keysym == XK_Left)
	{
		mv[RL] -= 10;
		mv[L] = 1;
	}
}

void	ft_ev_zoom(int keysym, t_coef *co)
{
	double	temp;

	if (keysym == XK_KP_Add && co->pix < 45)
	{
		temp = co->z_var / (double)co->pix;
		co->pix += 1;
		if (co->z_var > 0.0 || (co->z_var == 0
				&& co->z_var_ref > 0.0))
			co->z_var += ft_dabs(temp);
		else if (co->z_var < 0 || (co->z_var == 0
				&& co->z_var_ref < 0.0))
			co->z_var -= ft_dabs(temp);
	}
	else if (keysym == XK_KP_Subtract && co->pix > 1)
	{
		temp = co->z_var / (double)co->pix;
		co->pix -= 1;
		if (co->z_var > 0.0)
			co->z_var -= ft_dabs(temp);
		else if (co->z_var < 0.0)
			co->z_var += ft_dabs(temp);
	}
}

void	ft_ev_rotate(int keysym, double *rot)
{
	if (keysym == XK_Control_L)
	{
		*rot -= 0.05;
		if (*rot < -0.01)
			*rot = 12.55;
		if (*rot > 6.29 && *rot < 6.31)
			*rot = 0;
	}
	else if (keysym == XK_Control_R)
	{
		*rot += 0.05;
		if (*rot > 0.04 && *rot < 0.06)
			*rot = 6.35;
		if (*rot > 12.59 && *rot < 12.61)
			*rot = 0;
	}
}

void	ft_ev_elevation(int keysym, t_coef *co)
{
	if (keysym == XK_z)
	{
		if (co->z_var < 0 && co->z_var + 0.1 > 0)
			co->z_var = 0;
		else
			co->z_var += 0.1;
		co->z_var_ref = co->z_var;
	}
	else if (keysym == XK_m)
	{
		if (co->z_var > 0 && co->z_var - 0.1 < 0)
			co->z_var = 0;
		else
			co->z_var -= 0.1;
		co->z_var_ref = co->z_var;
	}
}

void	ft_ev_projection(int keysym, t_coef *co)
{
	if (keysym == XK_space || keysym == XK_BackSpace)
	{
		if (co->proj == parallele || keysym == XK_BackSpace)
			co->proj = isometric;
		else
			co->proj = parallele;
		ft_reset(co);
	}
}
