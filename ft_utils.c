/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:22:37 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:22:39 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int		check_arg(char **argv)
{
	char	str[5];
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (argv[1][i] != '.' && argv[1][i])
		i++;
	while (argv[1][++i] && n < 5)
		str[n++] = argv[1][i];
	str[n] = '\0';
	if (ft_strnstr(str, "cub", 3) == NULL || ft_strlen(str) != 3)
		ft_error("Wrong argument");
	if ((argv[2] && ft_strnstr(argv[2], "--save", 6) == NULL) ||
													ft_strlen(argv[2]) > 6)
		ft_error("Wrong argument");
	return (0);
}

void	get_start_map(t_map *map)
{
	char c;

	map->y = -1;
	while (map->map[++map->y])
	{
		if (ft_strchr(map->map[map->y], '1') != 0 ||
			ft_strchr(map->map[map->y], '0') != 0 ||
			ft_strchr(map->map[map->y], '2') != 0)
		{
			c = 'A';
			while (c++ <= 'Z' && ft_strchr(map->map[map->y], c) == 0)
			{
				if (c == 'Z')
				{
					map->start = map->y;
					break ;
				}
			}
		}
		if (c == 'Z')
			break ;
	}
}

int		counter(const char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i++] != ',')
		ft_error("Wrong map parameter");
	while (str[i] == ' ')
		i++;
	return (i);
}

void	make_map(t_list **head, int size, t_map *map)
{
	int		i;
	t_list	*tmp;

	i = -1;
	map->map = ft_calloc(size + 1, sizeof(char *));
	tmp = *head;
	while (tmp)
	{
		map->map[++i] = tmp->content;
		tmp = tmp->next;
	}
}
