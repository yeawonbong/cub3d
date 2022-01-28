/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:08:45 by ybong             #+#    #+#             */
/*   Updated: 2021/07/01 20:23:18 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_count_reslen(long long n)
{
	int			count;
	int			minus;
	int			reslen;

	minus = 0;
	if (n < 0)
		minus = 1;
	count = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		count++;
	}
	reslen = count + minus;
	return (reslen);
}

char		*ft_itoa(int n)
{
	long long	tempn;
	char		*res;
	int			reslen;

	tempn = (long long)n;
	reslen = ft_count_reslen(tempn);
	if (!(res = malloc(reslen + 1)))
		return (0);
	if (tempn < 0)
	{
		res[0] = '-';
		tempn *= -1;
	}
	res[reslen--] = '\0';
	while (tempn / 10 != 0)
	{
		res[reslen] = (tempn % 10) + '0';
		tempn = tempn / 10;
		reslen--;
	}
	res[reslen] = tempn + '0';
	return (res);
}

int			ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int				i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char*)str1;
	s2 = (unsigned char*)str2;
	i = 0;
	while (n > 0 && (s1[i] || s2[i]))
	{
		if (s1[i] == s2[i])
		{
			i++;
			n--;
		}
		else if (s1[i] > s2[i])
			return (1);
		else
			return (-1);
	}
	return (0);
}
