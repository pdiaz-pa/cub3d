/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:39:15 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/02/26 09:57:20 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_texture(t_global *global, int x, int y)
{
	y = global->ray.drawstart - 1;
	ft_init_texture(global);
	global->t.step = 1.0 * global->texture[0].height / global->ray.lineheight;
	global->t.texx = (int)(global->t.wallx * (double)global->texture
			[global->t.texdir].width);
	if (global->ray.side == 0 && global->ray.raydirx > 0)
		global->t.texx = global->texture[global->t.texdir].width -
			global->t.texx - 1;
	if (global->ray.side == 1 && global->ray.raydiry < 0)
		global->t.texx = global->texture[global->t.texdir].width -
			global->t.texx - 1;
	global->t.texpos = (global->ray.drawstart - global->ry / 2 +
			global->ray.lineheight / 2) * global->t.step;
	while (++y <= global->ray.drawend)
	{
		global->t.texy = (int)global->t.texpos &
			(global->texture[global->t.texdir].height - 1);
		global->t.texpos += global->t.step;
		if (y < global->ry && x < global->rx)
			global->data.addr[y * global->data.line_length / 4 + x] =
				global->texture[global->t.texdir].addr[global->t.texy *
					global->texture[global->t.texdir].line_length /
					4 + global->t.texx];
	}
}

int		ft_key_press(int keycode, t_global *global)
{
	if (keycode == KEY_W)
		global->data.forward = 1;
	else if (keycode == KEY_S)
		global->data.back = 1;
	else if (keycode == KEY_A)
		global->data.left = 1;
	else if (keycode == KEY_D)
		global->data.right = 1;
	else if (keycode == KEY_Q)
		global->data.rotate_left = 1;
	else if (keycode == KEY_E)
		global->data.rotate_right = 1;
	else if (keycode == KEY_ESC)
		ft_error(global, "Cerrando con ESC");
	else if (keycode == 65307)
		ft_error(global, "Error key_press\n");
	return (1);
}

int		ft_key_release(int keycode, t_global *global)
{
	if (keycode == KEY_W)
		global->data.forward = 0;
	else if (keycode == KEY_S)
		global->data.back = 0;
	else if (keycode == KEY_A)
		global->data.left = 0;
	else if (keycode == KEY_D)
		global->data.right = 0;
	else if (keycode == KEY_Q)
		global->data.rotate_left = 0;
	else if (keycode == KEY_E)
		global->data.rotate_right = 0;
	return (1);
}
