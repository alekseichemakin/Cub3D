/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:21:34 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:21:36 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	determinate_dir(t_ray *ray, t_plr *plr, t_map *map)
{
	if (ray->wall_side == 0)
	{
		if (map->x < plr->pos_x)
			ray->walldir = 'W';
		else
			ray->walldir = 'E';
		ray->walldist = (map->x - plr->pos_x + (1.0 - map->step_x) / 2) /
																	ray->dir_x;
	}
	else
	{
		if (map->y < plr->pos_y)
			ray->walldir = 'S';
		else
			ray->walldir = 'N';
		ray->walldist = (map->y - plr->pos_y + (1.0 - map->step_y) / 2) /
															ray->dir_y;
	}
}

void	determinate_side(t_ray *ray, t_plr *plr, t_map *map)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			map->x += map->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			map->y += map->step_y;
			ray->wall_side = 1;
		}
		if (map->map[map->y][map->x] == '1')
			hit = 1;
	}
	determinate_dir(ray, plr, map);
}

void	calcul_wall(t_ray *ray, t_text *text, t_win *win, t_plr *plr)
{
	win->l_high = (int)(win->high / ray->walldist);
	win->l_start = (-win->l_high) / 2 + win->high / 2;
	if (win->l_start < 0)
		win->l_start = 0;
	win->l_end = win->l_high / 2 + win->high / 2;
	if (win->l_end >= win->high)
		win->l_end = win->high - 1;
	if (ray->wall_side == 0)
		text->wall_x = plr->pos_y + ray->walldist * ray->dir_y;
	else
		text->wall_x = plr->pos_x + ray->walldist * ray->dir_x;
	text->wall_x -= floor(text->wall_x);
	text->tex_x = (int)(text->wall_x * (double)(ray->txt_w)) * -1;
	if (ray->wall_side == 0 && ray->dir_x > 0)
		text->tex_x = -ray->txt_w - text->tex_x + 1;
	if (ray->wall_side == 1 && ray->dir_y < 0)
		text->tex_x = -ray->txt_w - text->tex_x + 1;
	text->tex_x += ray->txt_w - 1;
	text->step = (double)ray->txt_h / win->l_high;
	text->tex_pos = (win->l_start - ((double)win->high / 2) +
							((double)win->l_high / 2)) * text->step;
}

void	draw_wall(t_text *text, t_win *win, t_ray *ray)
{
	int y;
	int color;

	y = 0;
	while (y < win->l_start)
		*(int *)(win->addr + (y++ * win->line_length + win->x *
		(win->bits_per_pixel / 8))) = win->c_color;
	while (y >= win->l_start && y < win->l_end)
	{
		text->tex_y = (int)text->tex_pos;
		text->tex_pos += text->step;
		color = *(int *)(ray->txt_data + (text->tex_y * ray->txt_ll +
				text->tex_x * (ray->txt_bpp / 8)));
		if (ray->wall_side == 1)
			color = (color >> 1) & 8355711;
		*(int *)(win->addr + (y++ * win->line_length + win->x *
		(win->bits_per_pixel / 8))) = color;
	}
	while (y < win->high - 1)
		*(int *)(win->addr + (y++ * win->line_length + win->x *
		(win->bits_per_pixel / 8))) = win->f_color;
}

void	raycast(t_all *all)
{
	double	buffer[all->win->wight];

	all->win->x = 0;
	while (all->win->x < all->win->wight)
	{
		all->plr->camera_x = 2 * all->win->x / (double)all->win->wight - 1;
		all->ray->dir_x = all->plr->dir_x + all->plr->plane_x *
				all->plr->camera_x;
		all->ray->dir_y = all->plr->dir_y + all->plr->plane_y *
				all->plr->camera_x;
		all->ray->delta_x = fabs(1 / all->ray->dir_x);
		all->ray->delta_y = fabs(1 / all->ray->dir_y);
		all->map->y = (int)all->plr->pos_y;
		all->map->x = (int)all->plr->pos_x;
		ft_init_ray(all->ray, all->plr, all->map);
		determinate_side(all->ray, all->plr, all->map);
		get_wall_text(all->ray, all->text);
		calcul_wall(all->ray, all->text, all->win, all->plr);
		draw_wall(all->text, all->win, all->ray);
		buffer[all->win->x] = all->ray->walldist;
		all->win->x++;
	}
	ft_sprites(all, buffer);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	mlx_do_sync(all->win->mlx);
}
