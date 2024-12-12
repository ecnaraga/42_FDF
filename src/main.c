/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galambey <galambey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:24:50 by galambey          #+#    #+#             */
/*   Updated: 2023/08/31 17:13:03 by galambey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int ac, char **av)
{
	t_cont	coord;
	int		fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit(1);
		coord = ft_recup_map(fd);
		close(fd);
		if (coord.first == NULL)
			exit(1);
		ft_fdf(coord);
	}
	else {
		ft_putstr_fd("Error : Miss an argugment\n", 2);
		exit(1);
	}
}
