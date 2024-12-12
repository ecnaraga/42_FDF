/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:43:49 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 16:51:12 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_final_coord(t_coord *pt_0, t_coord *pt_1, t_coef *co)
{
	if (co->proj == isometric)
	{
		pt_0->yd_p = pt_0->yd_p - pt_0->z_p;
		pt_1->yd_p = pt_1->yd_p - pt_1->z_p;
	}
	pt_1->x_p = (int)pt_1->xd_p;
	pt_1->y_p = (int)pt_1->yd_p;
	pt_0->x_p = (int)pt_0->xd_p;
	pt_0->y_p = (int)pt_0->yd_p;
	if (co->mv[CK] == 0)
		ft_ck_translate(pt_0, pt_1, co);
}
