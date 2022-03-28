/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:07:28 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/02 14:45:45 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_verify_errors(t_global *global)
{
	if (ft_walls(global) == 1)
		ft_error(global, "Mapa no rodeado de 1s\n");
	if (global->nsew == 'x')
		ft_error(global, "No hay jugador\n");
	if (global->toomuchplayers == 1)
		ft_error(global, "Más de un jugador\n");
	if (global->emptyline == 1)
		ft_error(global, "Línea vacía en el mapa\n");
	if (global->wrongcharmap == 2)
		ft_error(global, "Caracter incorrecto en el mapa\n");
}

void	ft_error2(t_global *global)
{
	if (global->map)
		free(global->map);
	if (global->s.order)
		free(global->s.order);
	if (global->s.distance)
		free(global->s.distance);
	if (global->sxy)
		free(global->sxy);
	if (global->s.zbuffer)
		free(global->s.zbuffer);
	ft_exit(global);
}

void	ft_error(t_global *global, char *str)
{
	int i;

	i = -1;
	if (global->error != 0)
		write(1, "Error\n", 6);
	global->ind3 = 1;
	write(1, str, ft_strlen(str));
	if (global->no)
		free(global->no);
	if (global->so)
		free(global->so);
	if (global->we)
		free(global->we);
	if (global->ea)
		free(global->ea);
	if (global->sp)
		free(global->sp);
	if (global->map)
	{
		while (++i < global->nbrlines)
			free(global->map[i]);
	}
	ft_error2(global);
}

int		ft_exit(t_global *global)
{
	if (global->data.img)
		mlx_destroy_image(global->data.mlx_ptr, global->data.img);
	if (global->texture[0].img)
		mlx_destroy_image(global->data.mlx_ptr, global->texture[0].img);
	if (global->texture[1].img)
		mlx_destroy_image(global->data.mlx_ptr, global->texture[1].img);
	if (global->texture[2].img)
		mlx_destroy_image(global->data.mlx_ptr, global->texture[2].img);
	if (global->texture[3].img)
		mlx_destroy_image(global->data.mlx_ptr, global->texture[3].img);
	if (global->texture[4].img)
		mlx_destroy_image(global->data.mlx_ptr, global->texture[4].img);
	if (global->data.mlx_win)
		mlx_destroy_window(global->data.mlx_ptr, global->data.mlx_win);
	exit(0);
}
