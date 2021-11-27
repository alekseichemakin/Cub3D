/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:22:12 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:22:14 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		define_sprites(char **map, int y)
{
	int x;
	int i;

	y = y - 1;
	i = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '2')
				i++;
	}
	return (i);
}

void	get_sprite(t_sprite *spr, t_map *map)
{
	int x;
	int y;
	int i;

	spr->sprite_count = define_sprites(map->map, map->start);
	spr->spritepos = malloc(spr->sprite_count * sizeof(t_spritepos));
	spr->order = malloc(spr->sprite_count * sizeof(int));
	y = map->start - 1;
	i = 0;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (map->map[y][x] == '2')
			{
				spr->spritepos[i].y = y + 0.5;
				spr->spritepos[i++].x = x + 0.5;
			}
		}
	}
}

void	draw_spr(t_sprite *spr, t_win *win, t_text *text, const double *buffer)
{
	int y;
	int d;
	int color;

	while (++spr->stripe < spr->draw_end_x)
	{
		spr->tex_x = (int)(256 * (spr->stripe - (-spr->sprite_width / 2 +
			spr->sprite_screen_x)) * text->spr_w / spr->sprite_width) / 256;
		if (spr->transform_y > 0 && spr->stripe > 0 && spr->stripe <
				win->wight && spr->transform_y < buffer[spr->stripe])
		{
			y = spr->draw_start_y - 1;
			while (++y < spr->draw_end_y)
			{
				d = (y - spr->v_move_screen) - win->high / 2 +
					spr->sprite_height / 2;
				spr->tex_y = ((d * text->spr_h) / spr->sprite_height);
				color = *(int *)(text->spr_data + (spr->tex_y * text->spr_ll +
										spr->tex_x * (text->spr_bpp / 8)));
				if ((color & 0x00FFFFFF) != 0)
					*(int *)(win->addr + (y * win->line_length + spr->stripe *
					(win->bits_per_pixel / 8))) = color;
			}
		}
	}
}

void	ft_sprites(t_all *all, const double *buffer)
{
	int i;

	i = 0;
	get_sprite(all->spr, all->map);
	sort_sprites(all->spr, all->plr);
	while (i < all->spr->sprite_count)
	{
		calc_spr_dist(all->spr, all->plr, all->win, i);
		draw_spr(all->spr, all->win, all->text, buffer);
		i++;
	}
	if (all->spr->spritepos)
		free(all->spr->spritepos);
	if (all->spr->order)
		free(all->spr->order);
}
