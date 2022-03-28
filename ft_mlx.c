/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:09:50 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 09:35:41 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_atoifc_check(const char *str, t_global *global)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != ',')
		i++;
	if (str[i] == ',')
		j = 1;
	i++;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		global->error = 2;
	if (ft_nbr_commas(str) != 2)
		global->error = 2;
}

int		ft_nbr_commas(const char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
	}
	return (j);
}

void	ft_init_nsew(t_global *global)
{
	if (global->nsew == 'N')
		global->ray.dirx = -1;
	if (global->nsew == 'S')
		global->ray.dirx = 1;
	if (global->nsew == 'E')
		global->ray.diry = 1;
	if (global->nsew == 'W')
		global->ray.diry = -1;
	if (global->nsew == 'N')
		global->ray.plany = 0.66;
	if (global->nsew == 'S')
		global->ray.plany = -0.66;
	if (global->nsew == 'E')
		global->ray.planx = 0.66;
	if (global->nsew == 'W')
		global->ray.planx = -0.66;
}

int		ft_mlx(t_global *global)
{
	ft_init_data_ray(global);
	if (!(global->data.mlx_ptr = mlx_init()))
		ft_error(global, "Error mlx init\n");
	if (global->rx > 2560)
		global->rx = 2560;
	if (global->ry > 1440)
		global->ry = 1440;
	ft_get_texture(global);
	global->data.img = mlx_new_image(global->data.mlx_ptr,
			global->rx, global->ry);
	global->data.addr = (int *)mlx_get_data_addr(global->data.img,
					&global->data.
					bits_per_pixel, &global->data.line_length,
					&global->data.endian);
	global->data.mlx_win = mlx_new_window(global->data.mlx_ptr, global->rx,
			global->ry, "Cub3D");
	mlx_hook(global->data.mlx_win, 17, 1L << 0, ft_exit, global);
	mlx_hook(global->data.mlx_win, 2, 1L << 0, ft_key_press, global);
	mlx_loop_hook(global->data.mlx_ptr, ft_raycasting, global);
	mlx_hook(global->data.mlx_win, 3, 1L << 1, ft_key_release, global);
	mlx_loop(global->data.mlx_ptr);
	return (0);
}
