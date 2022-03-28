/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:48:29 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2021/03/03 10:29:44 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_checker_parsing(t_global *global, char *str)
{
	if (global->insidemap == 1 && ft_emptyline(str) == 0 &&
		global->count < global->nbrlines)
		global->emptyline = 1;
	if (global->emptyline == 1)
		exit(0);
}

int		ft_parsing_map(char *file, t_global *global)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	fd = open(file, O_RDONLY);
	if (!(global->map = malloc(sizeof(char*) * global->nbrlines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, global);
		ft_checker_parsing(global, str);
		if ((global->insidemap = ft_is_map(str, global)) == 1)
		{
			global->count++;
			ft_copy_map(str, global);
		}
		free(str);
	}
	ft_flood_fill(global->dx, global->dy, global);
	close(fd);
	ft_init_sprite(global);
	return (0);
}

void	ft_parsing(char *file, t_global *global)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	if ((fd = open(file, O_DIRECTORY)) != -1)
		ft_error(global, "El .cub es un directorio\n");
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(global, "Fichero .cub inválido\n");
	global->error = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, global);
		if (global->error == 2)
			ft_error(global, "Error al parsear el mapa\n");
		ft_premap(&str, global);
		ft_texture(str, global);
		ft_map(str, global);
		free(str);
	}
	close(fd);
	if (global->sizeline == 0 || global->nbrlines == 0)
		ft_error(global, "No existe mapa\n");
	ft_parsing_map(file, global);
}

int		ft_iscub(char *str, t_global *global)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error(global, "Nombre del mapa inválido\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, global);
	else
		ft_error(global, "Nombre del mapa inválido\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_global global;

	global.save = 0;
	ft_init(&global);
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			global.save = 1;
		ft_iscub(argv[1], &global);
	}
	else
		ft_error(&global, "Número de argumentos inválido");
}
