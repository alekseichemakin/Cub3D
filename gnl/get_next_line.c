/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 13:56:45 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/23 12:02:10 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_n(char *remainder)
{
	int i;

	i = 0;
	if (!remainder)
		return (0);
	while (remainder[i])
	{
		if (remainder[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_line(char *remainder)
{
	char	*str;
	int		i;

	if (!(remainder))
	{
		free(remainder);
		return (NULL);
	}
	i = 0;
	while (remainder[i] != '\n' && remainder[i])
		i++;
	if (!(str = malloc(sizeof(char) * (i + 1))))
	{
		free(remainder);
		return (NULL);
	}
	i = 0;
	while (remainder[i] != '\n' && remainder[i])
	{
		str[i] = remainder[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*trim_rem(char *remainder)
{
	char	*str;
	int		i;
	int		n;

	if (!(remainder))
	{
		free(remainder);
		return (NULL);
	}
	i = 0;
	n = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	if (!(str = malloc(sizeof(char) * (ft_strlen_gnl(remainder) - i + 1))))
	{
		free(remainder);
		return (NULL);
	}
	while (remainder[i])
		str[n++] = remainder[i++];
	str[n] = '\0';
	free(remainder);
	return (str);
}

static int	clean(char *remainder, char *buf)
{
	if (remainder)
	{
		free(remainder);
		remainder = NULL;
	}
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	int			r;
	char		*buf;
	static char	*remainder;

	buf = NULL;
	if (!line || fd < 0 || BUFFER_SIZE <= 0 || !(buf = malloc(sizeof(char)
			* (BUFFER_SIZE + 1))) || read(fd, buf, 0) < 0)
		return (clean(remainder, buf));
	r = 1;
	while ((check_n(remainder) == 0 && (r = read(fd, buf, BUFFER_SIZE))) ||
	(remainder == NULL))
	{
		buf[r] = '\0';
		if (!(remainder = ft_strjoin_gnl(remainder, buf)))
			return (clean(remainder, buf));
	}
	free(buf);
	buf = NULL;
	*line = get_line(remainder);
	remainder = trim_rem(remainder);
	if (ft_strlen_gnl(remainder) != 0 || r != 0)
		return (1);
	free(remainder);
	remainder = NULL;
	return (0);
}
