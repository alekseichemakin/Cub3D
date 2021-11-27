/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:20:15 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:18 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	start_all(t_all *all, char **argv, int argc)
{
	int		fd;
	t_win	win;
	t_plr	plr;

	all->plr = &plr;
	all->win = &win;
	check_arg(argv);
	fd = open(argv[1], O_RDONLY);
	all->win->mlx = mlx_init();
	if (fd < 0 || all->win->mlx == 0)
		ft_error("File error");
	mlx_get_screen_size(all->win->mlx, &all->win->screen_w,
										&all->win->screen_h);
	ft_parser(fd, all);
	init_text(all->text, all->win);
	init_win(all->win);
	raycast(all);
	if (argc == 3)
		take_screenshot(all);
	mlx_hook(all->win->win, 2, (1L << 0), key_press, all);
	mlx_hook(all->win->win, 17, 1, prog_exit, all);
	mlx_loop(all->win->mlx);
}

int		main(int argc, char *argv[])
{
	t_all		all;
	t_map		map;
	t_ray		ray;
	t_sprite	spr;
	t_text		text;

	all.map = &map;
	all.ray = &ray;
	all.text = &text;
	all.spr = &spr;
	if (argc < 2 || argc > 3)
		ft_error("Wrong number of arguments");
	start_all(&all, argv, argc);
	exit(0);
}
