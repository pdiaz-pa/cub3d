/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiaz-pa <pdiaz-pa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 11:20:51 by pdiaz-pa          #+#    #+#             */
/*   Updated: 2020/12/22 11:54:25 by pdiaz-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_strlen(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (start < (unsigned int)ft_strlen((char *)s))
	{
		while (s[start] != '\0' && i < len)
		{
			str[i] = s[start];
			i++;
			start++;
		}
	}
	str[i] = '\0';
	return (str);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_subbuff(char *buff, int start, int len)
{
	int		i;
	char	*str;

	str = NULL;
	str = ft_strjoin(str, buff);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		buff[i] = str[start];
		i++;
		start++;
	}
	buff[i] = 0;
	free(str);
	return (buff);
}
