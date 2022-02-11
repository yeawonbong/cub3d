/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:15:00 by ybong             #+#    #+#             */
/*   Updated: 2022/02/11 16:49:01 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	map_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	get_map_info_process(t_data *data, int fd, char *line, int i)
{
	int		ismap;

	ismap = 0;
	if (!ft_strncmp(line, "NO", 2) && !ismap)
		data->map.info.north = ft_strtrim(line + 2, " ");
	else if (!ft_strncmp(line, "SO", 2) && !ismap)
		data->map.info.south = ft_strtrim(line + 2, " ");
	else if (!ft_strncmp(line, "WE", 2) && !ismap)
		data->map.info.west = ft_strtrim(line + 2, " ");
	else if (!ft_strncmp(line, "EA", 2) && !ismap)
		data->map.info.east = ft_strtrim(line + 2, " ");
	else if (!ft_strncmp(line, "F", 1) && !ismap)
		data->map.info.floor = ft_strtrim(line + 1, " ");
	else if (!ft_strncmp(line, "C", 1) && !ismap)
		data->map.info.ceiling = ft_strtrim(line + 1, " ");
	else if (*line && ft_strchr("1 ", *line))
	{
		ismap = 1;
		data->map.maparr[i++] = ft_strdup(line);
	}
	else if (ismap == 1)
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
	data->map.height = i;
}

int	isvalid_map_process(t_map *map, char **maparr, int i, int j)
{
	if ((i == 0 || j == 0 \
	|| i == (map->height - 1) || j == (ft_strlen(maparr[i]) - 1)) \
	&& !ft_strchr("1 ", maparr[i][j]))
		return (-1);
	if (maparr[i][j] == ' ')
	{
		if (0 < i && !ft_strchr("1 ", maparr[i - 1][j]))
			return (-1);
		if (0 < j && !ft_strchr("1 ", maparr[i][j - 1]))
			return (-1);
		if (i < map->height - 1 && !ft_strchr("1 ", maparr[i + 1][j]))
			return (-1);
		if (j < ft_strlen(maparr[i]) - 1 && \
			!ft_strchr("1 ", maparr[i][j + 1]))
			return (-1);
	}
	return (0);
}

void	set_direction(t_player *player)
{
	if (player->dir == 'N') // ㅂㅜㄱ
	{
		player->theta = 3 * M_PI / 2; //M_PI;
		player->vec_x = 0;
		player->vec_y = 1;
	}
	if (player->dir == 'S') // nam
	{
		player->theta = M_PI / 2; //M_PI;
		player->vec_x = 0;
		player->vec_y = -1;
	}
	if (player->dir == 'E') // dong
	{
		player->theta = 0; //M_PI;
		player->vec_x = 1;
		player->vec_y = 0;
	}
	if (player->dir == 'W') // seo
	{
		player->theta = M_PI; //M_PI;
		player->vec_x = -1;
		player->vec_y = 0;
	}
}

int	isvalid_map(t_map *map, t_player *player)
{
	char	**maparr;
	int		i;
	int		j;

	maparr = map->maparr;
	i = -1;
	while (maparr[++i])
	{
		j = -1;
		while (maparr[i][++j])
		{
			if (ft_strchr("NSEW", maparr[i][j]) && !player->dir)
			{
				player->x = j * 100;
				player->y = i * 100;
				player->dir = maparr[i][j];
				set_direction(player);
			}
			else if (!ft_strchr("01 ", maparr[i][j]))
				return (-1);
			if (isvalid_map_process(map, maparr, i, j) < 0)
				return (-1);
		}
	}
	return (0);
}

void	get_map_size(t_data *data, char *line, int fd)
{
	int	width;

	while (get_next_line(fd, &line) > 0)
	{
		width = 0;
		while (line[width] != 0)
			width++;
		if (data->map.width < width)
			data->map.width = width;
		data->map.height++;
	}
	close(fd);
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
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		map_error("Error\nInvalid map");
	get_map_info(data, fd);
	if (isvalid_map(&data->map, &data->player) < 0)
		map_error("Error\nInvalid map");
	// { 
	// 	// for (int i=0; data->map.maparr[i]; i++) //출력 확인
	// 	// {
	// 	// 	printf("%s, %d\n", data->map.maparr[i], i);
	// 	// }
	// 	printf("current player position: x_%f, y_%f, dir_%c\n", data->player.x, data->player.y, data->player.dir);
	// 	printf("map.height: %d, width: %d\n", data->map.height, data->map.width);
	// 	// printf("NO %s\nSO %s\nWE %s\nEA %s\nF %s\nC %s\n", data->map.info.north, data->map.info.south, data->map.info.west, data->map.info.east, data->map.info.floor, data->map.info.ceiling);
	// }
	data->map.width = 1000;
	data->map.height = 1000;
	close(fd);
}

// int main(int argc, char *argv[])
// {
// 	argc =0;
// 	t_data data;
// 	ft_memset(&data, 0, sizeof(t_data));
// 	get_map(&data, argv[1]);
	
// 	// data.mlx = mlx_init();
// 	// data.win = mlx_new_window(data.mlx, data.map.width * 100, data.map.height * 100 + 100, "minsikim_shooting");
// 	// mlx_loop(data.mlx); ///SEG

// 	return 0;
// }

// gcc map.c libft.a libgnl.a