/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_premap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:11:37 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 09:21:28 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_path_texture(char *str, char **texture, t_global *global, int j)
{
	global->count = 0;
	if (*texture != NULL)
		global->error = 2;
	if (ft_findchar(str, '.') == 0 || ft_findchar(str, '/') == 0
		|| ft_strlen2(str) <= 2)
		global->error = 2;
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			global->error = 2;
		j++;
	}
	if (!(*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)))))
		global->error = 2;
	while (str[j] != '\0')
	{
		(*texture)[global->count] = str[j];
		global->count++;
		j++;
	}
	(*texture)[global->count] = '\0';
}

void	ft_texture(char *str, t_global *global)
{
	int			i;
	static int	j;

	j = 0;
	i = 0;
	if (str[i] == 'S' && str[i + 1] == 'O')
		ft_path_texture(str, &global->no, global, 2);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		ft_path_texture(str, &global->so, global, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ft_path_texture(str, &global->we, global, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ft_path_texture(str, &global->ea, global, 2);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ft_path_texture(str, &global->sp, global, 1);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E' &&
	str[0] != 'R' && str[0] != 'F' && str[0] != 'C' && str[0] > 65
	&& str[0] < 122)
		global->error = 2;
	j++;
}

void	ft_premap_checker(t_global *global)
{
	if (global->sizeline > 0 && (global->no == NULL || global->so == NULL ||
				global->we == NULL || global->ea == NULL || global->sp == NULL))
		global->error = 2;
	if ((global->no != NULL || global->so != NULL || global->we != NULL ||
				global->ea != NULL || global->sp != NULL) && (global->rx == 0
				|| global->ry == 0))
		global->error = 2;
}

void	ft_premap(char **str, t_global *global)
{
	int	i;

	i = 0;
	global->i = 1;
	ft_premap_checker(global);
	if (*str[i] == 'R')
	{
		if (global->rx != 0 && global->ry != 0)
			global->error = 2;
		global->rx = ft_atoir(*str, global);
		global->ry = ft_atoir(*str, global);
		if (ft_atoir(*str, global) > 0 || global->rx == 0 || global->ry == 0)
			global->error = 2;
	}
	else if (*str[i] == 'F')
		global->f = ft_atoif(*str, global);
	else if (*str[i] == 'C')
		global->c = ft_atoic(*str, global);
	global->f = ft_translate_color(global->fred, global->fgreen, global->fblue);
	global->c = ft_translate_color(global->cred, global->cgreen, global->cblue);
}
