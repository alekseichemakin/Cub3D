/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:20:40 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:43 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_dir2(char dir, t_plr *plr)
{
	plr->dir_y = 0;
	plr->plane_x = 0.0;
	if (dir == 'W')
		plr->dir_x = -1;
	else
		plr->dir_x = 1;
	if (dir == 'W')
		plr->plane_y = -0.01;
	else
		plr->plane_y = 0.01;
}

void	init_dir(char dir, t_plr *plr)
{
	if (dir == 'N' || dir == 'S')
	{
		plr->dir_x = 0;
		plr->plane_y = 0.0;
		if (dir == 'S')
			plr->dir_y = -1;
		else
			plr->dir_y = 1;
		if (dir == 'S')
			plr->plane_x = 0.01;
		else
			plr->plane_x = -0.01;
	}
	else
		init_dir2(dir, plr);
}

void	init_plane2(t_map *map, int plane)
{
	map->start_x = map->x;
	map->dir_y = 0;
	if (plane == 2)
	{
		while (map->map[map->y][map->x] != '1')
			map->y++;
		map->start_y = --map->y;
		map->dir_x = 1;
	}
	else if (plane == 4)
	{
		while (map->map[map->y][map->x] != '1')
			map->y--;
		map->start_y = ++map->y;
		map->dir_x = -1;
	}
}

void	init_plane(t_map *map, int plane)
{
	if (plane == 1)
	{
		while (map->map[map->y][map->x] != '1')
			map->x++;
		map->start_x = --map->x;
		map->start_y = map->y;
		map->dir_x = 0;
		map->dir_y = -1;
	}
	else if (plane == 3)
	{
		while (map->map[map->y][map->x] != '1')
			map->x--;
		map->start_x = ++map->x;
		map->start_y = map->y;
		map->dir_x = 0;
		map->dir_y = 1;
	}
	else
		init_plane2(map, plane);
	map->startdir_x = map->dir_x;
	map->startdir_y = map->dir_y;
}

void	check_map_parameters(t_map *map, int map_start)
{
	int i;

	while (map->map[map_start])
	{
		i = 0;
		while (map->map[map_start][i])
		{
			if (map->map[map_start][i] != '0' && map->map[map_start][i] !=
			'1' && map->map[map_start][i] != '2' && map->map[map_start][i] !=
			' ')
				ft_error("Wrong map");
			i++;
		}
		map_start++;
	}
}
