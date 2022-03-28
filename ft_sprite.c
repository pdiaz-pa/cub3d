/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:24:14 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/02/25 15:53:50 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_sprite(int y, int stripe, int texx, t_global *global)
{
	int d;
	int texy;

	while (y < global->s.drawendy)
	{
		d = (y) * 256 - global->ry * 128 + global->s.spriteheight * 128;
		texy = ((d * global->texture[4].height) / global->s.spriteheight) / 256;
		if (global->texture[4].addr[texy * global->texture[4].line_length / 4 +
				texx] != BLACK)
		{
			global->data.addr[y * global->data.line_length / 4 + stripe] =
				global->texture[4].addr[texy * global->texture[4].line_length /
				4 + texx];
		}
		y++;
	}
}

void	ft_sprite_calc(t_global *global, int i)
{
	global->s.spritex = global->sxy[global->s.order[i]].x - global->ray.posx;
	global->s.spritey = global->sxy[global->s.order[i]].y - global->ray.posy;
	global->s.invdet = 1.0 / (global->ray.planx *
		global->ray.diry - global->ray.dirx * global->ray.plany);
	global->s.transformx = global->s.invdet *
		(global->ray.diry * global->s.spritex -
		global->ray.dirx * global->s.spritey);
	global->s.transformy = global->s.invdet * (-global->ray.plany *
	global->s.spritex + global->ray.planx * global->s.spritey);
	global->s.spritescreenx = (int)(global->rx / 2) *
		(1 + global->s.transformx / global->s.transformy);
	global->s.spriteheight = abs((int)(global->ry / (global->s.transformy)));
	global->s.drawstarty = -global->s.spriteheight / 2 + global->ry / 2;
	if (global->s.drawstarty < 0)
		global->s.drawstarty = 0;
	global->s.drawendy = global->s.spriteheight / 2 + global->ry / 2;
	if (global->s.drawendy >= global->ry)
		global->s.drawendy = global->ry - 1;
	global->s.spritewidth = abs((int)(global->ry / (global->s.transformy)));
	global->s.drawstartx = -global->s.spritewidth / 2 + global->s.spritescreenx;
	if (global->s.drawstartx < 0)
		global->s.drawstartx = 0;
	global->s.drawendx = global->s.spritewidth / 2 + global->s.spritescreenx;
	if (global->s.drawendx >= global->rx)
		global->s.drawendx = global->rx - 1;
}

void	ft_sort(t_global *global)
{
	int i;

	i = -1;
	while (++i < global->s.nbrsprites)
	{
		global->s.order[i] = i;
		global->s.distance[i] = ((global->ray.posx - global->sxy[i].x) *
				(global->ray.posx - global->sxy[i].x) + (global->ray.posy -
					global->sxy[i].y) * (global->ray.posy - global->sxy[i].y));
	}
}

void	ft_sort_sprite(t_global *global)
{
	int		i;
	int		j;
	double	tmp;

	ft_sort(global);
	i = -1;
	while (++i < global->s.nbrsprites)
	{
		j = -1;
		while (++j < global->s.nbrsprites - 1)
		{
			if (global->s.distance[j] < global->s.distance[j + 1])
			{
				tmp = global->s.distance[j];
				global->s.distance[j] = global->s.distance[j + 1];
				global->s.distance[j + 1] = tmp;
				tmp = global->s.order[j];
				global->s.order[j] = global->s.order[j + 1];
				global->s.order[j + 1] = (int)tmp;
			}
		}
	}
}

void	ft_sprite(t_global *global)
{
	int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	ft_sort_sprite(global);
	while (++i < global->s.nbrsprites)
	{
		ft_sprite_calc(global, i);
		stripe = global->s.drawstartx;
		while (stripe < global->s.drawendx)
		{
			texx = (int)(256 * (stripe - (-global->s.spritewidth / 2 +
			global->s.spritescreenx)) *
				global->texture[4].width / global->s.spritewidth) / 256;
			if (global->s.transformy > 0 && stripe >= 0 && stripe <
				global->rx && global->s.transformy < global->s.zbuffer[stripe])
			{
				y = global->s.drawstarty;
				ft_draw_sprite(y, stripe, texx, global);
			}
			stripe++;
		}
	}
}
