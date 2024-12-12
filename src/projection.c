/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:58:01 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:23:08 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_img_pix_put(t_img *img, t_coord pt)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (pt.y_p * img->line_len + pt.x_p * (img->bpp
				/ 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (pt.color >> i) & 0xFF;
		else
			*pixel++ = (pt.color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static void	ft_draw_iso(t_img *img, t_coord *pt_0, t_coord *pt_1,
		t_coef *co)
{
	int	i;

	i = -1;
	while (++i < pt_0[0].len)
	{
		if (i == pt_0[0].len - 1 && i > 0)
			ft_calcul_pt_iso_else(&pt_0[i - 1], &pt_0[i], co);
		else if (pt_0[0].len > 1)
		{
			ft_calcul_pt_iso_else(&pt_0[i], &pt_0[i + 1], co);
			ft_draw_line(img, pt_0[i], pt_0[i + 1], co);
		}
		if (pt_1)
		{
			if (i > 0)
				ft_calcul_pt_iso_else(&pt_1[i - 1], &pt_1[i], co);
			else
				ft_calcul_lg_first_pt_iso(&pt_0[i], &pt_1[i], co);
			ft_draw_line(img, pt_0[i], pt_1[i], co);
		}
	}
}

void	ft_img_iso(t_img *img, t_cont coord)
{
	t_cont	temp;
	t_coord	*pt_0;
	t_coord	*pt_1;
	t_coord	pt_ref;

	temp = coord;
	img->co.mid_z = img->co.min_z + (img->co.max_z - img->co.min_z) / 2;
	while (coord.first)
	{
		pt_0 = (t_coord *)coord.first->data;
		if (coord.first->next)
			pt_1 = (t_coord *)coord.first->next->data;
		else
			pt_1 = NULL;
		ft_first_point(&pt_0[0], &pt_ref, img, coord);
		if (pt_0[0].len == 1 && coord.size == 1)
			break ;
		pt_ref = pt_0[0];
		ft_draw_iso(img, pt_0, pt_1, &img->co);
		coord.first = coord.first->next;
	}
	coord = temp;
	ft_reset_ck_translate(&img->co);
}

static void	ft_draw_para(t_img *img, t_coord *pt_0, t_coord *pt_1,
		t_coef *co)
{
	int	i;

	i = -1;
	while (++i < pt_0[0].len)
	{
		if (i == pt_0[0].len - 1)
			ft_calcul_pt_para_else(&pt_0[i - 1], &pt_0[i], co);
		else
		{
			ft_calcul_pt_para_else(&pt_0[i], &pt_0[i + 1], co);
			ft_draw_line(img, pt_0[i], pt_0[i + 1], co);
		}
		if (pt_1)
		{
			if (i > 0)
				ft_calcul_pt_para_else(&pt_1[i - 1], &pt_1[i], co);
			else
				ft_calcul_lg_first_pt_para(&pt_0[i], &pt_1[i], co);
			ft_draw_line(img, pt_0[i], pt_1[i], co);
		}
	}
}

void	ft_img_para(t_img *img, t_cont coord)
{
	t_cont	temp;
	t_coord	*pt_0;
	t_coord	*pt_1;
	t_coord	pt_ref;

	temp = coord;
	img->co.mid_z = img->co.min_z + (img->co.max_z - img->co.min_z) / 2;
	while (coord.first)
	{
		pt_0 = (t_coord *)coord.first->data;
		if (coord.first->next)
			pt_1 = (t_coord *)coord.first->next->data;
		else
			pt_1 = NULL;
		ft_first_point(&pt_0[0], &pt_ref, img, coord);
		if (pt_0[0].len == 1 && coord.size == 1)
			break ;
		pt_ref = pt_0[0];
		ft_draw_para(img, pt_0, pt_1, &img->co);
		coord.first = coord.first->next;
	}
	coord = temp;
	ft_reset_ck_translate(&img->co);
}
