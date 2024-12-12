/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:44:03 by garance           #+#    #+#             */
/*   Updated: 2023/08/31 17:22:37 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	ck_char_hexa(char c, char *base)
{
	int	i;

	i = -1;
	if (c >= 'A' && c <= 'F')
		c = c + 32;
	while (base[++i])
	{
		if (base[i] == c)
			return (i);
	}
	return (-1);
}

static void	ft_set_color(char *str, int *error, t_coord *elem)
{
	int		i;
	int		nb;
	char	*base;

	nb = 0;
	base = "0123456789abcdef";
	if (!str[0])
		return ;
	if (str[0] == ',' && str[1] == '0' && str[2] == 'x' && ft_strlen(str) <= 9)
	{
		i = 3;
		while (ck_char_hexa(str[i], base) > -1)
		{
			nb = nb * 16 + ck_char_hexa(str[i], base);
			i++;
		}
		if (i <= 9 && !str[i])
		{
			*error = E_OK;
			elem->color = nb;
			elem->ck_color = y;
			return ;
		}
	}
	*error = E_ERR;
}

static void	ft_signe(char c, int *s, int *i)
{
	if (c == '-')
	{
		*s = -1;
		*i += 1;
	}
}

void	ft_atoi_parse_z_and_color(char *str, int *error, t_coord *elem)
{
	int			i;
	long int	nb;
	int			count;
	int			s;

	nb = 0;
	i = 0;
	count = 0;
	s = 1;
	if (!str)
		*error = E_ERR;
	ft_signe(str[0], &s, &i);
	if (!str[i] || str[i] < '0' || str[i] > '9')
		*error = E_ERR;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i++] - 48;
		count++;
	}
	if ((str[i] && str[i] != '\n') || (str[i] == '\n' && str[i + 1]) || nb
		* s > 2147483647 || nb * s < -2147483648 || count > 10)
		*error = E_ERR;
	elem->ck_color = n;
	ft_set_color(str + i, error, elem);
	elem->z = (int)nb * s;
}
