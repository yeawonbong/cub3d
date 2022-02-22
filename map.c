/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:15:00 by ybong             #+#    #+#             */
/*   Updated: 2022/02/22 18:30:06 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	get_map_info_process(t_data *data, int fd, char *line, int i)
{
	if (!ft_strncmp(line, "NO", 2))
		get_NO(data, line);
	else if (!ft_strncmp(line, "SO", 2))
		get_SO(data, line);
	else if (!ft_strncmp(line, "WE", 2))
		get_WE(data, line);
	else if (!ft_strncmp(line, "EA", 2))
		get_EA(data, line);
	else if (!ft_strncmp(line, "F", 1))
	{
		data->map.info.fbool++;
		data->map.info.floor = ft_strtrim(line + 1, " ");
	}
	else if (!ft_strncmp(line, "C", 1))
	{
		data->map.info.cbool++;
		data->map.info.ceiling = ft_strtrim(line + 1, " ");
	}
	else if (*line && ft_strchr("01 ", *line))
		data->map.maparr[i++] = ft_strdup(line);
	else if (ft_strlen(line) != 0)
		return (-1);
	return (i);
}

void	get_map_info(t_data *data, int fd)
{
	char	*line;
	int		i;
	int		res;

	i = 0;
	while (1)
	{
		res = get_next_line(fd, &line);
		if (res < 0)
			break ;
		i = get_map_info_process(data, fd, line, i);
		if (i < 0)
			map_error("Error\nInvalid map");
		free(line);
		line = 0;
		if (res == 0)
			break ;
	}
	if (data->map.info.fbool != 1 || data->map.info.cbool != 1 || \
		data->map.info.we != 1 || data->map.info.no != 1 || \
			data->map.info.ea != 1 || data->map.info.so != 1)
		map_error("Invalid map");
	data->map.height = i;
	data->map.info.f = set_fc(data->map.info.floor);
	data->map.info.c = set_fc(data->map.info.ceiling);
}

int	isvalid_map_process(t_map *map, char **maparr, int i, int j)
{
	int		k;
	int		u;

	if ((i == 0 || j == 0 \
	|| i == (map->height - 1) || j == (ft_strlen(maparr[i]) - 1)) \
	&& !(maparr[i][j] == ' ' || maparr[i][j] == '1'))
		return (-1);
	if (maparr[i][j] == '0' || ft_strchr("NSEW", maparr[i][j]))
	{
		k = -1;
		while (maparr[i - 1][++k])
			;
		u = -1;
		while (maparr[i + 1][++u])
			;
		if (k - 1 < j || u - 1 < j || (maparr[i - 1][j] == ' ' || \
				maparr[i + 1][j] == ' ' || \
					((j > 0 && maparr[i][j - 1] == ' ') || \
						maparr[i][j + 1] == ' ')))
			map_error("Invalid map");
	}
	return (0);
}

int	isvalid_map(t_map *map, t_player *player)
{
	char	**maparr;
	int		i;
	int		j;

	maparr = map->maparr;
	i = -1;
	while (maparr[++i] != 0 && i < map->height)
	{
		j = -1;
		while (maparr[i][++j] != 0)
		{
			if (ft_strchr("NSEW", maparr[i][j]) != NULL && player->dir == 0)
			{
				player->x = j * BITSIZE + BITSIZE / 2;
				player->y = i * BITSIZE + BITSIZE / 2;
				player->dir = maparr[i][j];
				set_direction(player);
			}
			else if (ft_strchr("01 ", maparr[i][j]) == NULL)
				return (-1);
			if (isvalid_map_process(map, maparr, i, j) < 0)
				return (-1);
		}
	}
	return (0);
}

void	get_map(t_data *data, char *filename)
{
	int		fd;
	char	*line;
	int		width;

	data->map.height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !ft_strncmp((filename - 4), ".cub", 4))
		map_error("Error\nInvalid map");
	get_map_size(data, line, fd);
	data->map.maparr = (char **)malloc(sizeof(char *) * (data->map.height + 1));
	data->map.maparr[data->map.height] = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		map_error("Error\nInvalid map");
	get_map_info(data, fd);
	if (isvalid_map(&data->map, &data->player) < 0 \
		|| data->player.dir == 0)
		map_error("Error\nInvalid map");
	data->map.width = 1200;
	data->map.height = 1000;
	close(fd);
}
