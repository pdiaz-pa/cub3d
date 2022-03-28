/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:26:54 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/02/26 09:56:31 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_texture_address(t_global *global)
{
	global->texture[0].addr = (int *)mlx_get_data_addr(global->texture[0].img,
			&global->texture[0].bits_per_pixel,
			&global->texture[0].line_length, &global->texture[0].endian);
	global->texture[1].addr = (int *)mlx_get_data_addr(global->texture[1].img,
			&global->texture[1].bits_per_pixel,
			&global->texture[1].line_length, &global->texture[1].endian);
	global->texture[2].addr = (int *)mlx_get_data_addr(global->texture[2].img,
			&global->texture[2].bits_per_pixel,
			&global->texture[2].line_length, &global->texture[2].endian);
	global->texture[3].addr = (int *)mlx_get_data_addr(global->texture[3].img,
			&global->texture[3].bits_per_pixel,
			&global->texture[3].line_length, &global->texture[3].endian);
	global->texture[4].addr = (int *)mlx_get_data_addr(global->texture[4].img,
			&global->texture[4].bits_per_pixel,
			&global->texture[4].line_length, &global->texture[4].endian);
}

void	ft_get_texture(t_global *global)
{
	if (!(global->texture[0].img = mlx_xpm_file_to_image(global->data.mlx_ptr,
					global->no, &(global->texture[0].width),
					&(global->texture[0].height))))
		ft_error(global, "Falta la textura SO\n");
	if (!(global->texture[1].img = mlx_xpm_file_to_image(global->data.mlx_ptr,
					global->so, &(global->texture[1].width),
					&(global->texture[1].height))))
		ft_error(global, "Falta la textura NO\n");
	if (!(global->texture[2].img = mlx_xpm_file_to_image(global->data.mlx_ptr,
					global->we, &(global->texture[2].width),
					&(global->texture[2].height))))
		ft_error(global, "Falta la textura EA\n");
	if (!(global->texture[3].img = mlx_xpm_file_to_image(global->data.mlx_ptr,
					global->ea, &(global->texture[3].width),
					&(global->texture[3].height))))
		ft_error(global, "Falta la textura WE\n");
	if (!(global->texture[4].img = mlx_xpm_file_to_image(global->data.mlx_ptr,
					global->sp, &(global->texture[4].width),
					&(global->texture[4].height))))
		ft_error(global, "Falta la textura S\n");
	ft_get_texture_address(global);
}

void	ft_init_texture(t_global *global)
{
	if (global->ray.side == 0 && global->ray.raydirx < 0)
		global->t.texdir = 0;
	if (global->ray.side == 0 && global->ray.raydirx >= 0)
		global->t.texdir = 1;
	if (global->ray.side == 1 && global->ray.raydiry < 0)
		global->t.texdir = 2;
	if (global->ray.side == 1 && global->ray.raydiry >= 0)
		global->t.texdir = 3;
	if (global->ray.side == 0)
		global->t.wallx = global->ray.posy + global->ray.perpwalldist
		* global->ray.raydiry;
	else
		global->t.wallx = global->ray.posx + global->ray.perpwalldist
		* global->ray.raydirx;
	global->t.wallx -= floor((global->t.wallx));
}

int		ft_draw_lines(t_global *global)
{
	int j;
	int i;

	j = -1;
	global->ray.drawend = global->ry - global->ray.drawstart;
	i = global->ray.drawend;
	while (++j < global->ray.drawstart)
		global->data.addr[j * global->data.line_length / 4 +
			global->ray.x] = global->c;
	if (j <= global->ray.drawend)
		ft_draw_texture(global, global->ray.x, j);
	j = i;
	while (++j < global->ry)
		global->data.addr[j * global->data.line_length / 4 +
			global->ray.x] = global->f;
	return (0);
}

int		ft_raycasting(t_global *global)
{
	global->ray.x = 0;
	while (global->ray.x < global->rx)
	{
		ft_init_ray(global);
		ft_stepsidedist(global);
		ft_draw_lines(global);
		global->s.zbuffer[global->ray.x] = global->ray.perpwalldist;
		global->ray.x++;
	}
	ft_sprite(global);
	if (global->save == 1)
		ft_save(global);
	mlx_put_image_to_window(global->data.mlx_ptr, global->data.mlx_win,
		global->data.img, 0, 0);
	ft_forward_back(global);
	ft_left_right(global);
	ft_rotate_right_left(global);
	return (0);
}
