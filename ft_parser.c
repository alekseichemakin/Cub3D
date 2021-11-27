/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:21:05 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:21:07 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	get_array(int fd, t_map *map)
{
	char	*line;
	t_list	*head;

	line = NULL;
	head = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head), map);
	ft_lstclear(&head, NULL);
}

int		check_param(t_win *win, t_text *text)
{
	if (win->wight == -1 || win->high == -1 || win->f_color == -1 ||
	win->c_color == -1)
		return (0);
	if (text->txt1_path == NULL || text->txt2_path == NULL || text->txt3_path
	== NULL || text->txt4_path == NULL || text->spr_path == NULL)
		return (0);
	return (1);
}

void	distribut(t_win *win, t_text *text, char *str)
{
	int i;

	i = 0;
	if (ft_strchr(str, 'R') != NULL && win->wight == -1 && win->high == -1)
		get_resolution(str, win);
	else if (ft_strchr(str, 'F') != NULL)
		win->f_color = get_color(str, text, win->f_color);
	else if (ft_strchr(str, 'C') != NULL)
		win->c_color = get_color(str, text, win->c_color);
	else if (ft_strnstr(str, "NO", ft_strlen(str)) != NULL)
		text->txt1_path = get_txt_path(str, text->txt1_path, 2);
	else if (ft_strnstr(str, "SO", ft_strlen(str)) != NULL)
		text->txt2_path = get_txt_path(str, text->txt2_path, 2);
	else if (ft_strnstr(str, "WE", ft_strlen(str)) != NULL)
		text->txt3_path = get_txt_path(str, text->txt3_path, 2);
	else if (ft_strnstr(str, "EA", ft_strlen(str)) != NULL)
		text->txt4_path = get_txt_path(str, text->txt4_path, 2);
	else if (ft_strchr(str, 'S') != NULL)
		text->spr_path = get_txt_path(str, text->spr_path, 1);
	else
		while (str[i])
			if (str[i++] != ' ')
				ft_error("Wrong map argument");
}

void	parse_param(t_win *win, t_text *text, t_map *map)
{
	int y;
	int n;

	init_param(win, text);
	y = -1;
	while (map->map[++y] && y < map->start)
		distribut(win, text, map->map[y]);
	if (check_param(win, text) == 0)
		ft_error("Wrong map");
	y = map->start;
	while (map->map[y])
		y++;
	n = map->start - 1;
	while (map->map[++n])
		if (ft_strlen(map->map[n]) == 0 && n < y)
			ft_error("Wrong map");
}

void	ft_parser(int fd, t_all *all)
{
	double coef;

	get_array(fd, all->map);
	get_start_map(all->map);
	check_map(all->map, all->plr);
	parse_param(all->win, all->text, all->map);
	coef = ((double)all->win->wight / (double)all->win->high) * (66.0 * 3.0) /
			4.0;
	all->plr->plane_y *= coef;
	all->plr->plane_x *= coef;
	close(fd);
}
