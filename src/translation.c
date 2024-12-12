/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:58:35 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:23:17 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_ck_translate(t_coord *pt_0, t_coord *pt_1, t_coef *co)
{
	if (pt_0 && pt_0->xd_p >= -10 && pt_0->xd_p <= WIDTH + 10
		&& pt_0->yd_p >= -10 && pt_0->yd_p <= HEIGHT + 10)
		co->mv[CK] = 1;
	else if (pt_1 && pt_1->xd_p >= -10 && pt_1->xd_p <= WIDTH + 10
		&& pt_1->yd_p >= -10 && pt_1->yd_p <= HEIGHT + 10)
		co->mv[CK] = 1;
}

void	ft_reset_ck_translate(t_coef *co)
{
	int	i;

	i = UD;
	if (co->mv[CK] == 0)
	{
		if (co->mv[U] == 1)
			co->mv[UD] += 10;
		if (co->mv[D] == 1)
			co->mv[UD] -= 10;
		if (co->mv[R] == 1)
			co->mv[RL] -= 10;
		if (co->mv[L] == 1)
			co->mv[RL] += 10;
	}
	while (++i <= 6)
		co->mv[i] = 0;
}

void	ft_translate(double *x, double *y, t_coef *co)
{
	*y = *y + co->mv[UD];
	*x = *x + co->mv[RL];
}
