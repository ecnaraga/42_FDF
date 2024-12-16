/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:22:40 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:22:12 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	ft_adapt_z(int *z, double *z_p, t_coef *co)
{
	(void) *z;
	if (co->alt == SAME_Z)
		*z_p = 0;
	else if (co->min_z > 0)
		*z_p = *z - co->min_z;
	else if (co->max_z < 0)
		*z_p = *z - co->max_z;
	else
		*z_p = *z;
	if (co->alt == DIFF_Z && (co->min_z >= 0 || co->max_z <= 0))
		*z_p = *z_p * co->z_var * (*z_p != 0);
	else if (co->alt == DIFF_Z && (co->min_z != 0 && co->max_z != 0))
		*z_p = *z_p * co->z_var * (*z != co->mid_z);
}

void	ft_calcul_first_pt_iso(t_coord *pt, t_cont coord, t_coef *co)
{
	co->an.d_sin_p = co->pix * sin((0.52359877559 + co->rot));
	co->an.d_sin_m = co->pix * sin((0.52359877559 - co->rot));
	co->an.d_cos_p = co->pix * cos((0.52359877559 + co->rot));
	co->an.d_cos_m = co->pix * cos((0.52359877559 - co->rot));
	pt->xd_p = WIDTH - (pt->len - 1) * co->an.d_cos_p;
	pt->xd_p = ((pt->xd_p + (coord.size - 1) * co->an.d_cos_m) / 2);
	pt->yd_p = HEIGHT - (pt->len - 1) * co->an.d_sin_p;
	pt->yd_p = ((pt->yd_p - (coord.size - 1) * co->an.d_sin_m) / 2);
	ft_adapt_z(&pt->z, &pt->z_p, co);
	if (co->mv[UD] != 0 || co->mv[RL] != 0)
		ft_translate(&pt->xd_p, &pt->yd_p, co);
	if (pt->len == 1 && coord.size == 1)
	{
		ft_ck_translate(pt, NULL, co);
		pt->x_p = (int)pt->xd_p;
		pt->y_p = (int)pt->yd_p;
	}
}

void	ft_calcul_lg_first_pt_iso(t_coord *pt_0, t_coord *pt_1, t_coef *co)
{
	pt_1->xd_p = pt_0->xd_p - co->an.d_cos_m;
	pt_1->yd_p = pt_0->yd_p + co->an.d_sin_m;
	ft_adapt_z(&pt_1->z, &pt_1->z_p, co);
}

void	ft_calcul_pt_iso_else(t_coord *pt_0, t_coord *pt_1, t_coef *co)
{
	pt_1->xd_p = pt_0->xd_p + co->an.d_cos_p;
	pt_1->yd_p = pt_0->yd_p + co->an.d_sin_p;
	ft_adapt_z(&pt_1->z, &pt_1->z_p, co);
}
