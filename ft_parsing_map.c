/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:00:27 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 10:27:58 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_flood_fill(int x, int y, t_global *global)
{
	if ((y >= global->sizeline || y < 0) || (x >= global->nbrlines || x < 0))
		ft_error(global, "Mapa no valido");
	if (global->map[x][y] == '1')
		return ;
	if (global->map[x][y] == 'X')
	{
		global->map[x][y] = '0';
		ft_flood_fill(x - 1, y, global);
		ft_flood_fill(x + 1, y, global);
		ft_flood_fill(x, y - 1, global);
		ft_flood_fill(x, y + 1, global);
		ft_flood_fill(x + 1, y + 1, global);
		ft_flood_fill(x - 1, y + 1, global);
		ft_flood_fill(x - 1, y - 1, global);
		ft_flood_fill(x + 1, y - 1, global);
	}
	else
		return ;
}

void	ft_x_filler(t_global *global, int j, int i)
{
	while (j <= (global->sizeline - 1))
	{
		global->map[i][j] = 'X';
		j++;
	}
}

int		ft_copy_map(char *str, t_global *global)
{
	static int	i = 0;
	int			j;

	j = 0;
	global->map[i] = NULL;
	if (!(global->map[i] = malloc(sizeof(char) * global->sizeline + 1)))
		return (0);
	while (str[j] != '\0')
	{
		if (ft_nsew(str[j], global, i, j) == 1)
			global->map[i][j] = 'X';
		else if (str[j] == ' ' || str[j] == '0')
			global->map[i][j] = 'X';
		else if (str[j] == '1')
			global->map[i][j] = '1';
		else
			global->map[i][j] = str[j];
		j++;
	}
	ft_x_filler(global, j, i);
	global->map[i][j] = '\0';
	j = 0;
	i++;
	return (0);
}

int		ft_is_map(char *str, t_global *global)
{
	int i;

	i = 0;
	ft_empty_checker(str, global);
	if (str[0] != '\0' && (ft_findchar(str, '1') == 1 ||
		ft_findchar(str, '0') == 1))
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
					&& str[i] != '\t')
			{
				if (global->insidemap == 1)
					global->wrongcharmap = 2;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_map(char *str, t_global *global)
{
	int			i;
	static int	snblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_is_map(str, global) == 1)
	{
		if (global->f == -1 || global->c == -1 || global->no == NULL ||
				global->so == NULL || global->we == NULL ||
				global->ea == NULL || global->sp == NULL)
			global->error = 2;
		if ((i = ft_strlen(str)) > ssizeline)
			ssizeline = i;
		snblines = snblines + 1;
	}
	global->nbrlines = snblines;
	global->sizeline = ssizeline;
}
