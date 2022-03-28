/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:25:55 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 09:32:39 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_walls_util(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != 'X')
			return (1);
		i++;
	}
	return (0);
}

int		ft_walls(t_global *global)
{
	int i;

	i = 0;
	while (i < global->nbrlines)
	{
		if (global->map[i][0] != '1' && global->map[i][0] != 'X')
			return (1);
		i++;
	}
	if (ft_walls_util(global->map[0]) == 1)
		return (1);
	if (ft_walls_util(global->map[global->nbrlines - 1]) == 1)
		return (1);
	return (0);
}
