/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:22:00 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:22:02 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	write_headder(int fd, t_scrshot *scrshot)
{
	write(fd, scrshot->file_type, 2);
	write(fd, &scrshot->file_size, 4);
	write(fd, &scrshot->reserved, 4);
	write(fd, &scrshot->pixel_data_offset, 4);
	write(fd, &scrshot->header_size, 4);
	write(fd, &scrshot->image_width, 4);
	write(fd, &scrshot->image_height, 4);
	write(fd, &scrshot->planes, 2);
	write(fd, &scrshot->bits_per_pixel, 2);
	write(fd, &scrshot->compression, 4);
	write(fd, &scrshot->image_size, 4);
	write(fd, &scrshot->x_pixels_per_meter, 4);
	write(fd, &scrshot->y_pixels_per_meter, 4);
	write(fd, &scrshot->total_colors, 4);
	write(fd, &scrshot->important_colors, 4);
}

void	hadder_bmp(int fd, t_win win, t_scrshot *scrshot)
{
	scrshot->file_type[0] = 0x42;
	scrshot->file_type[1] = 0x4D;
	scrshot->file_size = (win.wight * win.high * 4) + 54;
	scrshot->reserved = 0x00000000;
	scrshot->pixel_data_offset = 0x36;
	scrshot->header_size = 40;
	scrshot->image_width = win.wight;
	scrshot->image_height = -win.high;
	scrshot->planes = 1;
	scrshot->bits_per_pixel = 32;
	scrshot->compression = 0;
	scrshot->image_size = (win.wight * win.high * 4);
	scrshot->x_pixels_per_meter = 0;
	scrshot->y_pixels_per_meter = 0;
	scrshot->total_colors = 0;
	scrshot->important_colors = 0;
	write_headder(fd, scrshot);
}

void	take_screenshot(t_all *all)
{
	t_scrshot	scrshot;
	int			fd;
	int			i;

	all->scrshot = &scrshot;
	i = -1;
	fd = open("000.bmp", O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
	hadder_bmp(fd, *all->win, all->scrshot);
	while (++i < all->win->high)
		write(fd, all->win->addr + i * all->win->line_length, all->win->wight *
		4);
	close(fd);
	ft_putstr_fd("\nScreenshot saved successfully\n", 1);
	exit(0);
}
