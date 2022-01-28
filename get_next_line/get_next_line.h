/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 19:48:36 by ybong             #+#    #+#             */
/*   Updated: 2021/06/30 21:34:18 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

int		ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *str, int c);
int		get_next_line(int fd, char **line);
void	*ft_memset(void *ptr, int value, size_t num);

#endif
