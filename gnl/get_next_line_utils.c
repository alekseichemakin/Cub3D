/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 13:58:07 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/22 13:58:09 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t n;

	n = 0;
	if (!str)
		return (0);
	while (str[n])
		n++;
	return (n);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char		*str;
	size_t		len1;
	size_t		len2;
	size_t		i;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	if (!(str = malloc(len1 + len2 + 1)))
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = *s2++;
		i++;
	}
	str[i] = '\0';
	free((char*)s1);
	return (str);
}
