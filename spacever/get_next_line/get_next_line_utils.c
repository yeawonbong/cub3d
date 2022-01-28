/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:26:16 by ybong             #+#    #+#             */
/*   Updated: 2021/07/01 18:12:41 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char*)&str[i]);
		i++;
	}
	if (str[i] == c)
		return ((char*)&str[i]);
	return (0);
}

char	*ft_strdup(const char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!(s = (char*)malloc(ft_strlen(str) + 1)))
		return (0);
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	if (!(dst = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	free(s1);
	j = 0;
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*tempptr;

	i = 0;
	tempptr = (unsigned char *)ptr;
	while (i < num)
		tempptr[i++] = (unsigned char)value;
	return (ptr);
}
