#include "./cub3d.h"

void	get_map_info(t_data *data, int fd)
{
	char	*line;
	int		i;
	int		res;
	int		ismap;

	ismap = 0;
	i = 0;
	while (0 <= (res = get_next_line(fd, &line)))
	{
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
		{
			perror("Error\nInvalid map");
			exit(EXIT_FAILURE);
		}
		free(line);
		line = 0;
		if (res == 0)
			break;
	}
	data->map.height = i;
}

int		isvalid_map(t_map *map, t_player *player)
{
	char	**maparr;
	int		i;
	int		j;

	maparr = map->maparr;
	i = 0;
	while (maparr[i])
	{
		j = 0;
		while (maparr[i][j])
		{
			if (ft_strchr("NSEW", maparr[i][j]) && !player->dir)
			{
				// player->x = j;
				// player->y = i;
				player->dir = maparr[i][j];
			}
			else if (!ft_strchr("01 ", maparr[i][j]))
				return (-1);
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
				if (j < ft_strlen(maparr[i]) - 1 && !ft_strchr("1 ", maparr[i][j + 1]))
					return (-1);
			}	
			j++;
		}
		i++;
	}
	return (0);	
}

void	get_map(t_data *data, char *filename)
{
	int		fd;
	int		i;
	char	*line;
	int		width;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror("Error\nThe map doesn't exist");
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &line) > 0)
	{
		width = 0;
		while (line[width] != 0)
			width++;
		if (data->map.width < width)
			data->map.width = width;
		i++;
	}
	data->map.maparr = (char **)malloc(sizeof(char *) * i + 1);
	data->map.height = i;
	close(fd);
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror("Error\nThe map doesn't exist");
		exit(EXIT_FAILURE);
	}	
	get_map_info(data, fd);
	if (isvalid_map(&data->map, &data->player) < 0)
	{
		perror("Error\nInvalid map");
		exit(EXIT_FAILURE);
	}
	{
		for (int i=0; data->map.maparr[i]; i++) //출력 확인
		{
			printf("%s, %d\n", data->map.maparr[i], i);
		}
		printf("current player position: x_%f, y_%f, dir_%c\n", data->player.x, data->player.y, data->player.dir);
		printf("map.height: %d, width: %d\n", data->map.height, data->map.width);
		printf("NO %s\nSO %s\nWE %s\nEA %s\nF %s\nC %s\n", data->map.info.north, data->map.info.south, data->map.info.west, data->map.info.east, data->map.info.floor, data->map.info.ceiling);
	}

	close(fd);
}

// int main(int argc, char *argv[])
// {
// 	argc =0;
// 	t_data *data;
// 	data = malloc(sizeof(t_data));
// 	ft_memset(data, 0, sizeof(t_data));
// 	get_map(data, argv[1]);
// 	return 0;
// }

// gcc map.c libft.a libgnl.a