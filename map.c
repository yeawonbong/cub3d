#include "cub3d.h"

void	get_map_info(t_mlx *mlx, int fd)
{
// 	char	*line;
// 	int	i;

// 	i = 0;
// printf ("res: %d\n", get_next_line(fd, &line));
// 	while (get_next_line(fd, &line))
// 	{
// 			printf("here\n");
// 		if (line)
// 		{
// 			if (!ft_strncmp(line, "NO", 2))
// 				mlx->map.info.north = ft_strdup(line + 3);
// 			else if (!ft_strncmp(line, "SO", 2))
// 				mlx->map.info.south = ft_strdup(line + 3);
// 			else if (!ft_strncmp(line, "WE", 2))
// 				mlx->map.info.west = ft_strdup(line + 3);
// 			else if (!ft_strncmp(line, "EA", 2))
// 				mlx->map.info.east = ft_strdup(line + 3);
// 			else if (!ft_strncmp(line, "F", 1))
// 				mlx->map.info.floor = ft_strdup(line + 2);
// 			else if (!ft_strncmp(line, "C", 1))
// 				mlx->map.info.ceiling = ft_strdup(line + 2);
// 			else
// 				mlx->map.maparr[i] = ft_strdup(line);
// 			free(line);
// 			line = NULL;
// 		}
// 	}
}

// void	map_size(t_map *map, char *filename)
// {
// 	char	*line;
// 	int		fd;
// 	int		gnl;

// 	map->height = 1;
// 	map->width = 0;
// 	fd = open(filename, O_RDONLY);
// 	gnl = 1;
// 	while (gnl > 0)
// 	{
// 		gnl = get_next_line(fd, &line);
// 		if (gnl <= 0)
// 			break ;
// 		if (map->width < ft_strlen(line))
// 			map->width = ft_strlen(line);
// 		map->height++;
// 		free(line);
// 	}
// 	free(line);
// 	close(fd);
// }

void	get_map(t_mlx *mlx, char *filename)
{
	int		fd;
	// int		i;

printf("filename: %s\n", filename);
	mlx->map.maparr = malloc((int)sizeof(char*) * 30);
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror("Error\nThe map doesn't exist");
		exit(EXIT_FAILURE);
	}
	printf("fd is %d\n", fd);
	// get_map_info(mlx, fd);
	char	*line;
	int	i;

	i = 0;
printf ("res: %d\n", get_next_line(fd, &line));
printf ("sres: %s\n", line);
	while (0 < get_next_line(fd, &line))
	{
			printf("here\n");
		if (line)
		{
			if (!ft_strncmp(line, "NO", 2))
				mlx->map.info.north = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "SO", 2))
				mlx->map.info.south = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "WE", 2))
				mlx->map.info.west = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "EA", 2))
				mlx->map.info.east = ft_strdup(line + 3);
			else if (!ft_strncmp(line, "F", 1))
				mlx->map.info.floor = ft_strdup(line + 2);
			else if (!ft_strncmp(line, "C", 1))
				mlx->map.info.ceiling = ft_strdup(line + 2);
			else
				mlx->map.maparr[i] = ft_strdup(line);
			free(line);
			line = NULL;
		}
	}
	for (int i=0; mlx->map.maparr[i]; i++)
	{
		printf("%s, %d\n", mlx->map.maparr[i], i);
	}

	// map_size(mlx->map = malloc(sizeof(t_map)), filename);
	// mlx->map->maparr = malloc((int)sizeof(char*) * mlx->map->height);
	// while ((get_next_line(fd, &line)) > 0)
	// {
	// 	mlx->map->maparr[i++] = ft_strdup(line);
	// 	free(line);
	// 	if (ft_strlen(mlx->map->maparr[i - 1]) != mlx->map->width)
	// 	{
	// 		perror("Error\nThe map is not rectangular");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// mlx->map->maparr[i] = ft_strdup(line);
	// free(line);
	close(fd);
}

int main(int argc, char *argv[])
{
	printf("hi\n");
	t_mlx *mlx;
	mlx = malloc(sizeof(t_mlx));
	ft_memset(mlx, 0, sizeof(t_mlx));
	get_map(mlx, argv[1]);
	
	return 0;
}