/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:27:40 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/02/26 10:42:23 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_header(t_global *global, int fd)
{
	int tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * global->rx * global->ry;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &global->rx, 4);
	write(fd, &global->ry, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &global->data.bits_per_pixel, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	ft_save(t_global *global)
{
	int fd;
	int x;
	int y;

	fd = open("./save.bmp", O_CREAT | O_RDWR, 0777);
	ft_header(global, fd);
	y = global->ry - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < (global->rx))
		{
			write(fd, &global->data.addr[y * global->data.line_length
			/ 4 + x], 4);
			x++;
		}
		y--;
	}
	ft_error(global, "Imagen guardada correctamente.");
}
