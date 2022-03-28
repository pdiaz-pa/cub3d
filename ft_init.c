/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:08:35 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 09:35:00 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_more(t_global *global)
{
	global->nsew = 'x';
	global->ind2 = 0;
	global->ind3 = 0;
	global->data.img = NULL;
	global->data.mlx_win = NULL;
	global->map = NULL;
	global->texture[0].img = NULL;
	global->texture[1].img = NULL;
	global->texture[2].img = NULL;
	global->texture[3].img = NULL;
	global->texture[4].img = NULL;
	global->s.order = NULL;
	global->s.distance = NULL;
	global->s.zbuffer = NULL;
	global->sxy = NULL;
	global->fred = 0;
	global->fgreen = 0;
	global->fblue = 0;
	global->fcont = 0;
	global->cred = 0;
	global->cgreen = 0;
	global->cblue = 0;
	global->ccont = 0;
	global->forc = 0;
}

void	ft_init(t_global *global)
{
	global->no = NULL;
	global->so = NULL;
	global->we = NULL;
	global->ea = NULL;
	global->sp = NULL;
	global->f = -1;
	global->c = -1;
	global->ry = 0;
	global->rx = 0;
	global->nbrlines = 0;
	global->sizeline = 0;
	global->map = NULL;
	global->dx = 0;
	global->dy = 0;
	global->toomuchplayers = 0;
	global->emptyline = 0;
	global->insidemap = 0;
	global->count = 0;
	global->wrongcharmap = 0;
	global->sum = 0;
	ft_init_more(global);
}
