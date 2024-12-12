/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:06:13 by galambey          #+#    #+#             */
/*   Updated: 2023/08/31 17:22:56 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_first_point(t_coord *pt, t_coord *pt_ref, t_img *img, t_cont coord)
{
	if (!coord.first->prev)
	{
		if (img->co.proj == isometric)
			ft_calcul_first_pt_iso(pt, coord, &img->co);
		else
			ft_calcul_first_pt_para(pt, coord, &img->co);
		if (pt->len == 1 && coord.size == 1)
		{
			pt->color = 0x0000FF;
			if (pt->y_p >= 0 && pt->y_p <= HEIGHT && pt->x_p >= 0
				&& pt->x_p <= WIDTH)
				ft_img_pix_put(img, *pt);
		}
	}
	else
	{
		if (img->co.proj == isometric)
			ft_calcul_lg_first_pt_iso(pt_ref, pt, &img->co);
		else
			ft_calcul_lg_first_pt_para(pt_ref, pt, &img->co);
	}
}
