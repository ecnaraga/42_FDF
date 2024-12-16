/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallele.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garance <garance@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:22:40 by garance           #+#    #+#             */
/*   Updated: 2023/08/21 13:00:08 by garance          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	ft_calcul_first_pt_para(t_coord *pt, t_cont coord, t_coef *co)
{
	co->an.d_sin_p = co->pix * sin((1.57079632679 + co->rot));
	co->an.d_sin_m = co->pix * sin((3.14159265359 - co->rot));
	co->an.d_cos_p = co->pix * cos((0 + co->rot));
	co->an.d_cos_m = co->pix * cos((1.57079632679 - co->rot));
	ft_adapt_z(&pt->z, &pt->z_p, co);
	pt->xd_p = (WIDTH - (pt->len - 1) * co->an.d_cos_p);
	pt->xd_p = ((pt->xd_p + (coord.size - 1) * co->an.d_cos_m) / 2)
		- floor(pt->z_p * sin(0.785398));
	pt->yd_p = HEIGHT - (coord.size - 1) * co->an.d_sin_p;
	pt->yd_p = (pt->yd_p - (pt->len - 1) * co->an.d_sin_m) / 2
		- floor(pt->z_p * cos(0.785398));
	if (co->mv[UD] != 0 || co->mv[RL] != 0)
		ft_translate(&pt->xd_p, &pt->yd_p, co);
	if (pt->len == 1 && coord.size == 1)
	{
		ft_ck_translate(pt, NULL, co);
		pt->x_p = (int)pt->xd_p;
		pt->y_p = (int)pt->yd_p;
		pt->color = 0x0000FF;
	}
}

void	ft_calcul_lg_first_pt_para(t_coord *pt_0, t_coord *pt_1,
		t_coef *co)
{
	ft_adapt_z(&pt_1->z, &pt_1->z_p, co);
	if (pt_1->z == pt_0->z)
	{
		pt_1->xd_p = pt_0->xd_p - co->an.d_cos_m * (floor(co->rot != 0));
		pt_1->yd_p = pt_0->yd_p + co->an.d_sin_p * (floor(co->rot) != 0)
			+ (co->pix) * (floor(co->rot) == 0);
	}
	else
	{
		pt_1->xd_p = pt_0->xd_p - co->an.d_cos_m - floor((pt_1->z_p)
				* sin(0.785398)) + floor((pt_0->z_p) * sin(0.785398));
		pt_1->yd_p = pt_0->yd_p + co->an.d_sin_p - floor((pt_1->z_p)
				* cos(0.785398)) + floor((pt_0->z_p) * cos(0.785398));
	}
}

void	ft_calcul_pt_para_else(t_coord *pt_0, t_coord *pt_1, t_coef *co)
{
	ft_adapt_z(&pt_1->z, &pt_1->z_p, co);
	if (pt_1->z == pt_0->z)
	{
		pt_1->xd_p = pt_0->xd_p + co->an.d_cos_p - (pt_1->z_p
				- pt_0->z_p);
		pt_1->yd_p = pt_0->yd_p + co->an.d_sin_m * (floor(co->rot) != 0);
	}
	else
	{
		pt_1->xd_p = pt_0->xd_p + co->an.d_cos_p - floor((pt_1->z_p)
				* sin(0.785398)) + floor((pt_0->z_p) * sin(0.785398));
		pt_1->yd_p = pt_0->yd_p + co->an.d_sin_m - floor((pt_1->z_p)
				* cos(0.785398)) + floor((pt_0->z_p) * cos(0.785398));
	}
}
