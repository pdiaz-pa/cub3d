/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:08:19 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/02/26 14:30:29 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_forward_back(t_global *global)
{
	if (global->data.forward == 1)
	{
		if (global->map[(int)(global->ray.posx + (global->ray.dirx * global->
						ray.movespeed))][(int)global->ray.posy] == '0')
			global->ray.posx += global->ray.dirx * global->ray.movespeed;
		if (global->map[(int)(global->ray.posx)][(int)(global->ray.posy +
					(global->ray.diry * global->ray.movespeed))] == '0')
			global->ray.posy += global->ray.diry * global->ray.movespeed;
	}
	if (global->data.back == 1)
	{
		if (global->map[(int)(global->ray.posx - (global->ray.dirx * global->
						ray.movespeed))][(int)(global->ray.posy)] == '0')
			global->ray.posx -= global->ray.dirx * global->ray.movespeed;
		if (global->map[(int)(global->ray.posx)][(int)(global->ray.posy -
					(global->ray.diry * global->ray.movespeed))] == '0')
			global->ray.posy -= global->ray.diry * global->ray.movespeed;
	}
}

void	ft_left_right(t_global *global)
{
	if (global->data.right == 1)
	{
		if (global->map[(int)(global->ray.posx + global->ray.diry *
					(global->ray.movespeed))][(int)global->ray.posy] == '0')
			global->ray.posx += global->ray.diry * global->ray.movespeed;
		if (global->map[(int)global->ray.posx][(int)(global->ray.posy -
					global->ray.dirx *
					(global->ray.movespeed))] == '0')
			global->ray.posy -= global->ray.dirx * global->ray.movespeed;
	}
	if (global->data.left == 1)
	{
		if (global->map[(int)(global->ray.posx - global->ray.diry *
					(global->ray.movespeed))][(int)global->ray.posy] == '0')
			global->ray.posx -= global->ray.diry * global->ray.movespeed;
		if (global->map[(int)global->ray.posx][(int)(global->ray.posy +
					global->ray.dirx *
					(global->ray.movespeed))] == '0')
			global->ray.posy += global->ray.dirx * global->ray.movespeed;
	}
}

void	ft_rotate_right_left(t_global *global)
{
	double oldplanx;
	double olddirx;

	oldplanx = global->ray.planx;
	olddirx = global->ray.dirx;
	if (global->data.rotate_right == 1)
	{
		global->ray.dirx = global->ray.dirx * cos(-global->ray.rotspeed / 2) -
			global->ray.diry * sin(-global->ray.rotspeed / 2);
		global->ray.diry = olddirx * sin(-global->ray.rotspeed / 2) +
			global->ray.diry * cos(-global->ray.rotspeed / 2);
		global->ray.planx = global->ray.planx * cos(-global->ray.rotspeed / 2)
			- global->ray.plany * sin(-global->ray.rotspeed / 2);
		global->ray.plany = oldplanx * sin(-global->ray.rotspeed / 2) +
			global->ray.plany * cos(-global->ray.rotspeed / 2);
	}
	ft_rotate_left(global, olddirx);
}

void	ft_rotate_left(t_global *global, double olddirx)
{
	double oldplanex;

	if (global->data.rotate_left == 1)
	{
		olddirx = global->ray.dirx;
		oldplanex = global->ray.planx;
		global->ray.dirx = global->ray.dirx * cos(global->ray.rotspeed / 2) -
			global->ray.diry * sin(global->ray.rotspeed / 2);
		global->ray.diry = olddirx * sin(global->ray.rotspeed / 2) + global->
			ray.diry * cos(global->ray.rotspeed / 2);
		global->ray.planx = global->ray.planx * cos(global->ray.rotspeed / 2) -
			global->ray.plany * sin(global->ray.rotspeed / 2);
		global->ray.plany = oldplanex * sin(global->ray.rotspeed / 2) +
			global->ray.plany * cos(global->ray.rotspeed / 2);
	}
}
