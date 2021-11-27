/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:20:29 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:32 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	check_voids(int x, int y, t_map *map)
{
	int lh_x;
	int lh_y;

	if (map->dir_x == 0)
	{
		lh_x = map->dir_y;
		lh_y = map->dir_x;
	}
	else
	{
		lh_x = map->dir_y * -1;
		lh_y = map->dir_x * -1;
	}
	while (map->map[y + lh_y] && map->map[y + lh_y][x + lh_x] != '1')
	{
		if (map->map[y + lh_y][x + lh_x] != '2' && map->map[y + lh_y][x + lh_x]
															!= '0')
			ft_error("Wrong map");
		y += lh_y;
		x += lh_x;
	}
}

void	init_rh_do_step(t_map *map)
{
	if (map->dir_x == 0)
	{
		map->rh_x = map->dir_y * -1;
		map->rh_y = map->dir_x * -1;
	}
	else
	{
		map->rh_x = map->dir_y;
		map->rh_y = map->dir_x;
	}
	if (map->map[map->y + map->rh_y][map->x + map->rh_x] != '1')
	{
		map->dir_x = map->rh_x;
		map->dir_y = map->rh_y;
	}
}

void	check_front_rwall(t_map *map)
{
	if (map->map[map->y + map->dir_y] && (map->map[map->y + map->dir_y][map->x +
	map->dir_x] == '0' || map->map[map->y + map->dir_y][map->x + map->dir_x]
	== '2'))
	{
		map->x += map->dir_x;
		map->y += map->dir_y;
	}
	else if (map->map[map->y + map->dir_y] && (map->map[map->y +
	map->dir_y][map->x + map->dir_x] == '1'))
	{
		map->dir_x = -map->rh_x;
		map->dir_y = -map->rh_y;
	}
	else
		ft_error("Wrong map");
}

void	init_plr(t_map *map, t_plr *plr)
{
	while (map->map[map->y] && ft_strchr(map->map[map->y], 'N') == NULL &&
	ft_strchr(map->map[map->y], 'E') == NULL &&
	ft_strchr(map->map[map->y], 'W') == NULL && ft_strchr(map->map[map->y],
																'S') == NULL)
		map->y++;
	if (map->map[map->y] == NULL)
		ft_error("Wrong map");
	while (map->map[map->y][map->x] != 'N' && map->map[map->y][map->x] != 'E' &&
			map->map[map->y][map->x] != 'W' && map->map[map->y][map->x] != 'S')
		map->x++;
	plr->pos_x = map->x + 0.5;
	plr->pos_y = map->y + 0.5;
	init_dir(map->map[map->y][map->x], plr);
	map->map[map->y][map->x] = '0';
}

void	check_map(t_map *map, t_plr *plr)
{
	int plane;
	int map_start;

	map_start = map->y;
	map->x = 0;
	plane = 0;
	init_plr(map, plr);
	check_map_parameters(map, map_start);
	while (++plane <= 4)
	{
		init_plane(map, plane);
		while (1)
		{
			init_rh_do_step(map);
			check_front_rwall(map);
			check_voids(map->x, map->y, map);
			if (map->x == map->start_x && map->y == map->start_y &&
				map->dir_x == map->startdir_x && map->dir_y == map->startdir_y)
				break ;
		}
	}
}
