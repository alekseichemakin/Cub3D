/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:21:46 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:21:49 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	get_wall_text_sn(t_ray *ray, t_text *text)
{
	if (ray->walldir == 'S')
	{
		ray->txt_data = text->txt2_data;
		ray->txt_h = text->txt2_h;
		ray->txt_w = text->txt2_w;
		ray->txt_bpp = text->txt2_bpp;
		ray->txt_ll = text->txt2_ll;
	}
	else if (ray->walldir == 'N')
	{
		ray->txt_data = text->txt1_data;
		ray->txt_h = text->txt1_h;
		ray->txt_w = text->txt1_w;
		ray->txt_bpp = text->txt1_bpp;
		ray->txt_ll = text->txt1_ll;
	}
}

void	get_wall_text(t_ray *ray, t_text *text)
{
	if (ray->walldir == 'W')
	{
		ray->txt_data = text->txt3_data;
		ray->txt_h = text->txt3_h;
		ray->txt_w = text->txt3_w;
		ray->txt_bpp = text->txt3_bpp;
		ray->txt_ll = text->txt3_ll;
	}
	else if (ray->walldir == 'E')
	{
		ray->txt_data = text->txt4_data;
		ray->txt_h = text->txt4_h;
		ray->txt_w = text->txt4_w;
		ray->txt_bpp = text->txt4_bpp;
		ray->txt_ll = text->txt4_ll;
	}
	else if (ray->walldir == 'S' || ray->walldir == 'N')
		get_wall_text_sn(ray, text);
}

void	ft_init_ray(t_ray *ray, t_plr *plr, t_map *map)
{
	if (ray->dir_x < 0)
	{
		map->step_x = -1;
		ray->side_x = (plr->pos_x - map->x) * ray->delta_x;
	}
	else
	{
		map->step_x = 1;
		ray->side_x = (map->x + 1.0 - plr->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		map->step_y = -1;
		ray->side_y = (plr->pos_y - map->y) * ray->delta_y;
	}
	else
	{
		map->step_y = 1;
		ray->side_y = (map->y + 1.0 - plr->pos_y) * ray->delta_y;
	}
}
