/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:04:58 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 10:29:44 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_data_ray(t_global *global)
{
	if (!(global->s.zbuffer = (double *)malloc(sizeof(double) * global->rx)))
		exit(0);
	global->data.forward = 0;
	global->data.back = 0;
	global->data.left = 0;
	global->data.right = 0;
	global->data.rotate_right = 0;
	global->data.rotate_left = 0;
	global->ray.posx = (double)global->dx + 0.5;
	global->ray.posy = (double)global->dy + 0.5;
	global->ray.dirx = 0;
	global->ray.diry = 0;
	global->ray.planx = 0;
	global->ray.plany = 0;
	ft_init_nsew(global);
}

void	ft_init_ray2(t_global *global)
{
	if (global->ray.raydiry == 0)
		global->ray.deltadistx = 0;
	else if (global->ray.raydirx == 0)
		global->ray.deltadistx = 1;
	else
		global->ray.deltadistx = fabs(1 / global->ray.raydirx);
	if (global->ray.raydirx == 0)
		global->ray.deltadisty = 0;
	else if (global->ray.raydiry == 0)
		global->ray.deltadisty = 1;
	else
		global->ray.deltadisty = fabs(1 / global->ray.raydiry);
}

void	ft_init_ray(t_global *global)
{
	global->ray.hit = 0;
	global->ray.perpwalldist = 0;
	global->ray.camerax = 2 * global->ray.x / (double)global->rx - 1;
	global->ray.raydirx = global->ray.dirx + global->ray.planx *
						global->ray.camerax;
	global->ray.raydiry = global->ray.diry + global->ray.plany *
						global->ray.camerax;
	global->ray.mapx = (int)global->ray.posx;
	global->ray.mapy = (int)global->ray.posy;
	global->ray.movespeed = 0.175;
	global->ray.rotspeed = 0.033 * 3.0;
	ft_init_ray2(global);
}

void	ft_init_sprite_where(t_global *global, int i, int j, int v)
{
	i = i - 1;
	while (++i < global->nbrlines)
	{
		j = -1;
		while (++j < global->sizeline)
		{
			if (global->map[i][j] == '2')
			{
				global->sxy[v].x = (double)i + 0.5;
				global->sxy[v].y = (double)j + 0.5;
				v++;
			}
		}
	}
}

void	ft_init_sprite(t_global *global)
{
	int i;
	int j;

	i = -1;
	global->s.nbrsprites = 0;
	ft_verify_errors(global);
	while (++i < global->nbrlines)
	{
		j = -1;
		while (++j < global->sizeline)
		{
			if (global->map[i][j] == '2')
				global->s.nbrsprites += 1;
		}
	}
	if (!(global->sxy = (t_sxy *)malloc(sizeof(t_sxy) * global->s.nbrsprites)))
		ft_error(global, "No Malloc sxy* en ft_init_sprite");
	if (!(global->s.order = (int *)malloc(sizeof(int) * global->s.nbrsprites)))
		ft_error(global, "No Malloc s.order * en ft_init_sprite");
	if (!(global->s.distance = (double *)malloc(sizeof(double)
		* global->s.nbrsprites)))
		ft_error(global, "No Malloc s.distance* en ft_init_sprite");
	ft_init_sprite_where(global, 0, 0, 0);
	ft_mlx(global);
}
