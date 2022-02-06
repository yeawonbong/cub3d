/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 17:19:03 by ybong             #+#    #+#             */
/*   Updated: 2022/02/04 17:51:46 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (c == '\0')
		return ((char *)&str[i]);
	while (i != 0)
	{
		i--;
		if (str[i] == (char)c)
			return ((char *)&str[i]);
	}
	return (0);
}
