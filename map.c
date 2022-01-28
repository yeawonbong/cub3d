#include "cub3d.h"

void	map_info(t_map *map, char *fimename)
{

}

void	map_size(t_map *map, char *filename)
{
	char	*line;
	int		fd;
	int		gnl;

	map->height = 1;
	map->width = 0;
	fd = open(filename, O_RDONLY);
	gnl = 1;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		if (gnl <= 0)
			break ;
		if (map->width < ft_strlen(line))
			map->width = ft_strlen(line);
		map->height++;
		free(line);
	}
	free(line);
	close(fd);
}

void	get_map(t_mlx *mlx, char *filename)
{
	char	*line;
	int		fd;
	int		i;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror("Error\nThe map doesn't exist");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 8)
	{
		if (get_next_line(fd, &line) && !ft_strncmp(line, "NO", 2));
			texture
	}

	map_size(mlx->map = malloc(sizeof(t_map)), filename);
	mlx->map->maparr = malloc((int)sizeof(char*) * mlx->map->height);
	while ((get_next_line(fd, &line)) > 0)
	{
		mlx->map->maparr[i++] = ft_strdup(line);
		free(line);
		if (ft_strlen(mlx->map->maparr[i - 1]) != mlx->map->width)
		{
			perror("Error\nThe map is not rectangular");
			exit(EXIT_FAILURE);
		}
	}
	mlx->map->maparr[i] = ft_strdup(line);
	free(line);
	close(fd);
}