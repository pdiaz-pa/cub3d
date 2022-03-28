/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:09:46 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/02/25 11:09:48 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_stepsidedist(t_global *global)
{
	if (global->ray.raydirx < 0)
	{
		global->ray.stepx = -1;
		global->ray.sidedistx = (global->ray.posx - global->ray.mapx)
							* global->ray.deltadistx;
	}
	else
	{
		global->ray.stepx = 1;
		global->ray.sidedistx = (global->ray.mapx + 1.0 - global->ray.posx)
							* global->ray.deltadistx;
	}
	if (global->ray.raydiry < 0)
	{
		global->ray.stepy = -1;
		global->ray.sidedisty = (global->ray.posy - global->ray.mapy)
							* global->ray.deltadisty;
	}
	else
	{
		global->ray.stepy = 1;
		global->ray.sidedisty = (global->ray.mapy + 1.0 - global->ray.posy)
							* global->ray.deltadisty;
	}
	ft_incrementray(global);
}

void	ft_incrementray(t_global *global)
{
	while (global->ray.hit == 0)
	{
		if (global->ray.sidedistx < global->ray.sidedisty)
		{
			global->ray.sidedistx += global->ray.deltadistx;
			global->ray.mapx += global->ray.stepx;
			global->ray.side = 0;
		}
		else
		{
			global->ray.sidedisty += global->ray.deltadisty;
			global->ray.mapy += global->ray.stepy;
			global->ray.side = 1;
		}
		if (global->map[global->ray.mapx][global->ray.mapy] == '1')
			global->ray.hit = 1;
		ft_drawstartend(global);
	}
}

void	ft_drawstartend(t_global *global)
{
	if (global->ray.side == 0)
		global->ray.perpwalldist = ((double)global->ray.mapx -
				global->ray.posx + (1 - (double)global->ray.
				stepx) / 2) / global->ray.raydirx;
	else
		global->ray.perpwalldist = ((double)global->ray.mapy -
				global->ray.posy + (1 - (double)global->ray.
				stepy) / 2) / global->ray.raydiry;
	global->ray.lineheight = (int)(global->ry / global->ray.perpwalldist);
	global->ray.drawstart = -global->ray.lineheight / 2 + global->ry / 2;
	if (global->ray.drawstart < 0)
		global->ray.drawstart = 0;
	global->ray.drawend = global->ray.lineheight / 2 + global->ry / 2;
	if (global->ray.drawend >= global->ry || global->ray.drawend < 0)
		global->ray.drawend = global->ry - 1;
}
