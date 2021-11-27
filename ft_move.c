/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:20:53 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:55 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		prog_exit(t_all *all)
{
	free(all->map->map);
	ft_destroy_win(all->win);
	exit(0);
}

void	up_down(t_map *map, t_plr *plr, int key)
{
	double speed;

	speed = 0.2;
	if (key == 13)
	{
		if (map->map[(int)(plr->pos_y + plr->dir_y * speed)][(int)
													plr->pos_x] != '1')
			plr->pos_y += plr->dir_y * speed;
		if (map->map[(int)(plr->pos_y)][(int)(plr->pos_x +
											plr->dir_x * speed)] != '1')
			plr->pos_x += plr->dir_x * speed;
	}
	if (key == 1)
	{
		if (map->map[(int)(plr->pos_y - plr->dir_y * speed)][(int)
													plr->pos_x] != '1')
			plr->pos_y -= plr->dir_y * speed;
		if (map->map[(int)(plr->pos_y)][(int)(plr->pos_x -
													plr->dir_x * speed)] != '1')
			plr->pos_x -= plr->dir_x * speed;
	}
}

void	rot_left_right(t_plr *plr, int key)
{
	double rotspeed;
	double old_dir_x;
	double old_plane_x;

	old_dir_x = plr->dir_x;
	old_plane_x = plr->plane_x;
	rotspeed = 0.07;
	if (key == 123)
	{
		plr->dir_x = plr->dir_x * cos(-rotspeed) - plr->dir_y * sin(-rotspeed);
		plr->dir_y = old_dir_x * sin(-rotspeed) + plr->dir_y * cos(-rotspeed);
		plr->plane_x = plr->plane_x * cos(-rotspeed) - plr->plane_y *
															sin(-rotspeed);
		plr->plane_y = old_plane_x * sin(-rotspeed) + plr->plane_y *
															cos(-rotspeed);
	}
	if (key == 124)
	{
		plr->dir_x = plr->dir_x * cos(rotspeed) - plr->dir_y * sin(rotspeed);
		plr->dir_y = old_dir_x * sin(rotspeed) + plr->dir_y * cos(rotspeed);
		plr->plane_x = plr->plane_x * cos(rotspeed) - plr->plane_y *
														sin(rotspeed);
		plr->plane_y = old_plane_x * sin(rotspeed) + plr->plane_y *
														cos(rotspeed);
	}
}

void	left_right(t_map *map, t_plr *plr, int key)
{
	double speed;

	speed = 0.2;
	if (key == 2)
	{
		if (map->map[(int)(plr->pos_y + plr->dir_x * speed)][(int)
				plr->pos_x] != '1')
			plr->pos_y += plr->dir_x * speed;
		if (map->map[(int)(plr->pos_y)][(int)(plr->pos_x -
											plr->dir_y * speed)] != '1')
			plr->pos_x -= plr->dir_y * speed;
	}
	if (key == 0)
	{
		if (map->map[(int)(plr->pos_y - plr->dir_x * speed)][(int)
				plr->pos_x] != '1')
			plr->pos_y -= plr->dir_x * speed;
		if (map->map[(int)(plr->pos_y)][(int)(plr->pos_x +
													plr->dir_y * speed)] != '1')
			plr->pos_x += plr->dir_y * speed;
	}
}

int		key_press(int key, t_all *all)
{
	if (key == 13 || key == 1)
		up_down(all->map, all->plr, key);
	if (key == 0 || key == 2)
		left_right(all->map, all->plr, key);
	if (key == 123 || key == 124)
		rot_left_right(all->plr, key);
	if (key == 53)
		prog_exit(all);
	raycast(all);
	return (0);
}
