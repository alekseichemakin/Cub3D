/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:20:03 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:06 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	check_txt(t_text *text, t_win *win)
{
	if (open(text->txt1_path, O_RDONLY) < 0 || open(text->txt2_path,
		O_RDONLY) < 0 || open(text->txt3_path, O_RDONLY) < 0)
	{
		ft_destroy_win(win);
		ft_error("Wrong map parameter");
	}
	if (open(text->txt4_path, O_RDONLY) < 0 || open(text->spr_path, O_RDONLY)
															< 0)
	{
		ft_destroy_win(win);
		ft_error("Wrong map parameter");
	}
}

void	init_text2(t_text *text, t_win *win)
{
	if (!(text->txt3 = mlx_xpm_file_to_image(win->mlx, text->txt3_path,
										&(text->txt3_w), &(text->txt3_h))) ||
			!(text->txt3_data = mlx_get_data_addr(text->txt3, &(text->txt3_bpp),
									&(text->txt3_ll), &(text->txt3_ed))))
	{
		ft_destroy_win(win);
		ft_error("Wrong texture");
	}
	if (!(text->txt4 = mlx_xpm_file_to_image(win->mlx, text->txt4_path,
								&(text->txt4_w), &(text->txt4_h))) ||
		!(text->txt4_data = mlx_get_data_addr(text->txt4, &(text->txt4_bpp),
										&(text->txt4_ll), &(text->txt4_ed))))
	{
		ft_destroy_win(win);
		ft_error("Wrong texture");
	}
	if (!(text->spr = mlx_xpm_file_to_image(win->mlx, text->spr_path, &
											(text->spr_w), &(text->spr_h))) ||
		!(text->spr_data = mlx_get_data_addr(text->spr, &(text->spr_bpp),
										&(text->spr_ll), &(text->spr_ed))))
	{
		ft_destroy_win(win);
		ft_error("Wrong texture");
	}
}

void	init_text(t_text *text, t_win *win)
{
	check_txt(text, win);
	if (!(text->txt1 = mlx_xpm_file_to_image(win->mlx, text->txt1_path,
										&(text->txt1_w), &(text->txt1_h)))
	|| !(text->txt1_data = mlx_get_data_addr(text->txt1, &(text->txt1_bpp),
										&(text->txt1_ll), &(text->txt1_ed))))
	{
		ft_destroy_win(win);
		ft_error("Wrong texture");
	}
	if (!(text->txt2 = mlx_xpm_file_to_image(win->mlx, text->txt2_path,
										&(text->txt2_w), &(text->txt2_h))) ||
	!(text->txt2_data = mlx_get_data_addr(text->txt2, &(text->txt2_bpp),
									&(text->txt2_ll), &(text->txt2_ed))))
	{
		ft_destroy_win(win);
		ft_error("Wrong texture");
	}
	init_text2(text, win);
}

void	init_win(t_win *win)
{
	win->win = mlx_new_window(win->mlx, win->wight, win->high, "cub3d");
	win->img = mlx_new_image(win->mlx, win->wight, win->high);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
									&win->line_length, &win->endian);
	if (win->win == 0 || win->img == 0)
		ft_error("Couldn't create win");
}

void	init_param(t_win *win, t_text *text)
{
	win->wight = -1;
	win->high = -1;
	win->f_color = -1;
	win->c_color = -1;
	text->txt1_path = NULL;
	text->txt2_path = NULL;
	text->txt3_path = NULL;
	text->txt4_path = NULL;
	text->spr_path = NULL;
}
