/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:22:25 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:22:27 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	distr_sprites(t_sprite *spr, double *spr_dist, int i)
{
	int		tmp;

	tmp = (int)spr_dist[i];
	spr_dist[i] = spr_dist[i + 1];
	spr_dist[i + 1] = tmp;
	tmp = spr->order[i];
	spr->order[i] = spr->order[i + 1];
	spr->order[i + 1] = tmp;
}

void	sort_sprites(t_sprite *spr, t_plr *plr)
{
	int		i;
	double	spr_dist[spr->sprite_count];

	i = -1;
	while (++i < spr->sprite_count)
	{
		spr->order[i] = i;
		spr_dist[i] = ((plr->pos_x - spr->spritepos[i].x) * (plr->pos_x -
				spr->spritepos[i].x) + (plr->pos_y - spr->spritepos[i].y) *
						(plr->pos_y - spr->spritepos[i].y));
	}
	i = -1;
	while (++i < spr->sprite_count - 1)
	{
		if (spr_dist[i] < spr_dist[i + 1])
		{
			distr_sprites(spr, spr_dist, i);
			i = -1;
		}
	}
}

void	init_spr_param(t_sprite *spr, t_plr *plr, t_win *win, int i)
{
	double	fly;
	int		high;

	fly = 0;
	high = 1;
	spr->sprite_x = spr->spritepos[spr->order[i]].x - plr->pos_x;
	spr->sprite_y = spr->spritepos[spr->order[i]].y - plr->pos_y;
	spr->inv_det = 1.0 / (plr->plane_x * plr->dir_y - plr->dir_x *
			plr->plane_y);
	spr->transform_x = spr->inv_det * (plr->dir_y * spr->sprite_x -
			plr->dir_x * spr->sprite_y);
	spr->transform_y = spr->inv_det * (-plr->plane_y * spr->sprite_x +
											plr->plane_x * spr->sprite_y);
	spr->sprite_screen_x = (int)(((double)win->wight / 2) * (1 +
										spr->transform_x / spr->transform_y));
	spr->v_move_screen = (int)(fly / spr->transform_y);
	spr->sprite_height = abs((int)(win->high / (spr->transform_y))) / high;
	spr->draw_start_y = -spr->sprite_height / 2 + win->high /
			2 + spr->v_move_screen;
}

void	calc_spr_dist(t_sprite *spr, t_plr *plr, t_win *win, int i)
{
	int width;

	width = 1;
	init_spr_param(spr, plr, win, i);
	if (spr->draw_start_y < 0)
		spr->draw_start_y = 0;
	spr->draw_end_y = spr->sprite_height / 2 + win->high / 2 +
			spr->v_move_screen;
	if (spr->draw_end_y >= win->high)
		spr->draw_end_y = win->high - 1;
	spr->sprite_width = abs((int)(win->high / (spr->transform_y))) / width;
	spr->draw_start_x = -spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_start_x < 0)
		spr->draw_start_x = 0;
	spr->draw_end_x = spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_end_x >= win->wight)
		spr->draw_end_x = win->wight - 1;
	spr->stripe = spr->draw_start_x;
}
