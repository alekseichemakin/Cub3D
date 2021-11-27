/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:21:21 by mqueen            #+#    #+#             */
/*   Updated: 2021/03/08 19:21:23 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	get_resolution2(t_win *win)
{
	if (win->high <= 0 || win->wight <= 0)
		ft_error("Wrong map parameter");
	if (win->high % 2 != 0)
		win->high++;
	if (win->wight > win->screen_w)
		win->wight = win->screen_w;
	if (win->high > win->screen_h)
		win->high = win->screen_h;
}

void	get_resolution(char *str, t_win *win)
{
	int		i;
	int		n;
	char	buf[100];

	i = 1;
	n = 0;
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]) == 1)
		buf[n++] = str[i++];
	buf[n] = '\0';
	win->wight = ft_atoi(buf);
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]) == 0)
		ft_error("Wrong map parameter");
	n = 0;
	while (ft_isdigit(str[i]) == 1)
		buf[n++] = str[i++];
	buf[n] = '\0';
	if (str[i])
		ft_error("Wrong map parameter");
	win->high = ft_atoi(buf);
	get_resolution2(win);
}

void	get_color2(char *str, t_text *txt, int i, int n)
{
	char buf[4];

	while (ft_isdigit(str[i]) == 1 && n < 4)
		buf[n++] = str[i++];
	buf[n] = '\0';
	txt->r = ft_atoi(buf);
	n = 0;
	i = counter(str, i);
	if (ft_isdigit(str[i]) == 0)
		ft_error("Wrong map parameter");
	while (ft_isdigit(str[i]) == 1 && n < 4)
		buf[n++] = str[i++];
	buf[n] = '\0';
	txt->g = ft_atoi(buf);
	n = 0;
	i = counter(str, i);
	if (ft_isdigit(str[i]) == 0)
		ft_error("Wrong map parameter");
	while (ft_isdigit(str[i]) == 1 && n < 4)
		buf[n++] = str[i++];
	buf[n] = '\0';
	txt->b = ft_atoi(buf);
	if (str[i] != '\0')
		ft_error("Wrong map parameter");
}

int		get_color(char *str, t_text *txt, int check)
{
	int i;
	int n;

	if (check != -1)
		ft_error("Wrong map parameter");
	n = 0;
	i = 1;
	while (str[i] == ' ' && str[i])
		i++;
	get_color2(str, txt, i, n);
	if (txt->r < 0 || txt->r > 255 || txt->g < 0)
		ft_error("Wrong map parameter");
	if (txt->b < 0 || txt->b > 255 || txt->g > 255)
		ft_error("Wrong map parameter");
	return (get_rgb(txt->r, txt->g, txt->b));
}

char	*get_txt_path(char *str, const char *check, int i)
{
	int start;

	if (check != NULL)
		ft_error("Wrong map parameter");
	while (str[i] == ' ')
		i++;
	start = i;
	while (ft_isprint(str[i]) == 1 && str[i] != ' ')
		i++;
	if (str[i] == ' ')
		ft_error("Wrong map parameter");
	return (ft_substr(str, start, i - start));
}
