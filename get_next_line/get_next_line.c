/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:28:57 by ybong             #+#    #+#             */
/*   Updated: 2021/06/23 17:41:31 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_read(int readsize, int fd, char **backup)
{
	char *buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if ((readsize = read(fd, buf, BUFFER_SIZE)) < 0)
		return (-1);
	if (buf)
		buf[readsize] = '\0';
	backup[fd] = ft_strjoin(backup[fd], buf);
	free(buf);
	return (readsize);
}

int		ft_find_enter(char *str)
{
	int i;

	i = 0;
	if (str == 0)
		return (-42);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ft_split_str(int fd, char **backup, char **line, int enter_idx)
{
	char	*temp;

	temp = ft_strdup(backup[fd]);
	free(backup[fd]);
	backup[fd] = ft_strdup(&temp[enter_idx + 1]);
	temp[enter_idx] = '\0';
	*line = ft_strdup(temp);
	free(temp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*backup[FOPEN_MAX];
	int			readsize;
	int			enter_idx;

	if (BUFFER_SIZE <= 0 || fd < 0 || !(line) || fd > FOPEN_MAX)
		return (-1);
	enter_idx = 0;
	readsize = 0;
	while ((readsize = ft_read(readsize, fd, backup)) >= 0)
	{
		if ((enter_idx = ft_find_enter(backup[fd])) >= 0)
			return ((ft_split_str(fd, backup, line, enter_idx)));
		if (enter_idx == -1 && (readsize < BUFFER_SIZE))
		{
			*line = backup[fd];
			backup[fd] = 0;
			return (0);
		}
		if (readsize == 0 && backup[fd] == 0)
		{
			*line = ft_strdup("");
			return (0);
		}
	}
	return (-1);
}
