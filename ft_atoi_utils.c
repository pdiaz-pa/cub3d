/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:56:58 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/02 16:42:09 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoir(const char *str, t_global *global)
{
	int		sum;

	sum = 0;
	if (str[1] != ' ' || ft_findchar((char *)str, ',') == 1)
		global->error = 2;
	while (str[global->i] == ' ' || str[global->i] == '\t' || str[global->i]
	== ',' || str[global->i] == '\n' || str[global->i] == '\r' ||
	str[global->i] == '\v' || str[global->i] == '\f')
		global->i++;
	if (str[global->i] == '-' || str[global->i] == '+')
		global->error = 2;
	while (str[global->i] >= '0' && str[global->i] <= '9')
	{
		if (sum > 21474636)
			break ;
		sum = (sum * 10) + (str[global->i] - 48);
		global->i++;
	}
	while (str[global->i] >= '0' && str[global->i] <= '9')
		global->i++;
	return (sum);
}

void	ft_f_switcher(t_global *global, int verify)
{
	global->fcont++;
	if (global->fcont == 1)
		global->fred = verify;
	if (global->fcont == 2)
		global->fgreen = verify;
	if (global->fcont == 3)
		global->fblue = verify;
}

int		ft_atoif(const char *str, t_global *global)
{
	int		verify;

	verify = 0;
	if (str[1] != ' ')
		global->error = 2;
	ft_atoifc_check(str, global);
	while (str[global->i] == ' ' || str[global->i] == '\t' || str[global->i]
			== ',' || str[global->i] == '\n' || str[global->i] == '\r'
			|| str[global->i] == '\v' || str[global->i] == '\f')
	{
		global->i++;
		verify = 0;
		if (str[global->i] >= '0' && str[global->i] <= '9')
			global->ind2++;
		while (str[global->i] >= '0' && str[global->i] <= '9')
		{
			verify = (verify * 10) + str[global->i] - 48;
			global->sum = (global->sum * 10) + (str[global->i] - 48);
			global->i++;
		}
		if (verify > 255 || verify < 0)
			global->error = 2;
		ft_f_switcher(global, verify);
	}
	return (global->sum);
}

void	ft_c_switcher(t_global *global, int verify)
{
	global->ccont++;
	if (global->ccont == 1)
		global->cred = verify;
	if (global->ccont == 2)
		global->cgreen = verify;
	if (global->ccont == 3)
		global->cblue = verify;
}

int		ft_atoic(const char *str, t_global *global)
{
	int		verify;

	verify = 0;
	if (str[1] != ' ')
		global->error = 2;
	ft_atoifc_check(str, global);
	while (str[global->i] == ' ' || str[global->i] == '\t' || str[global->i]
			== ',' || str[global->i] == '\n' || str[global->i] == '\r'
			|| str[global->i] == '\v' || str[global->i] == '\f')
	{
		global->i++;
		verify = 0;
		if (str[global->i] >= '0' && str[global->i] <= '9')
			global->ind2++;
		while (str[global->i] >= '0' && str[global->i] <= '9')
		{
			verify = (verify * 10) + str[global->i] - 48;
			global->sum = (global->sum * 10) + (str[global->i] - 48);
			global->i++;
		}
		if (verify > 255 || verify < 0)
			global->error = 2;
		ft_c_switcher(global, verify);
	}
	return (global->sum);
}
