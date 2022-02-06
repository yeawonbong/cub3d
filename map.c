#include "cub3d.h"

void	get_map_info(t_mlx *mlx, int fd)
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
			mlx->map.info.north = ft_strtrim(line + 2, " ");
		else if (!ft_strncmp(line, "SO", 2) && !ismap)
			mlx->map.info.south = ft_strtrim(line + 2, " ");
		else if (!ft_strncmp(line, "WE", 2) && !ismap)
			mlx->map.info.west = ft_strtrim(line + 2, " ");
		else if (!ft_strncmp(line, "EA", 2) && !ismap)
			mlx->map.info.east = ft_strtrim(line + 2, " ");
		else if (!ft_strncmp(line, "F", 1) && !ismap)
			mlx->map.info.floor = ft_strtrim(line + 1, " ");
		else if (!ft_strncmp(line, "C", 1) && !ismap)
			mlx->map.info.ceiling = ft_strtrim(line + 1, " ");
		else if (*line && ft_strchr("1 ", *line))
		{
			ismap = 1;
			mlx->map.maparr[i++] = ft_strdup(line);
		}
		else if (ismap == 1)
		{
			perror("Error\nInvalid map");
			exit(EXIT_FAILURE);
		}
		free(line);
		line = NULL;
		if (res == 0)
			break;
	}
	mlx->map.height = i;
}

int		isvalid_map(t_map *map)
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
			if (ft_strchr("NSEW", maparr[i][j]) && !map->curdir)
			{
				map->curx = j;
				map->cury = i;
				map->curdir = maparr[i][j];
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

void	get_map(t_mlx *mlx, char *filename)
{
	int		fd;
	int		i;
	char	*line;
	
	mlx->map.maparr = malloc((int)sizeof(char*) * 50);
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror("Error\nThe map doesn't exist");
		exit(EXIT_FAILURE);
	}
	get_map_info(mlx, fd);
	if (isvalid_map(&mlx->map) < 0)
	{
		perror("Error\nInvalid map");
		exit(EXIT_FAILURE);
	}
	// {
	// 	printf("NO %s\nSO %s\nWE %s\nEA %s\nF %s\nC %s\n", mlx->map.info.north, mlx->map.info.south, mlx->map.info.west, mlx->map.info.east, mlx->map.info.floor, mlx->map.info.ceiling);
	// 	for (int i=0; mlx->map.maparr[i]; i++) //출력 확인
	// 	{
	// 		printf("%s, %d\n", mlx->map.maparr[i], i);
	// 	}
	// 	printf("current player position: x_%d, y_%d, dir_%c", mlx->map.curx, mlx->map.cury, mlx->map.curdir);
	// }

	close(fd);
}

int main(int argc, char *argv[])
{
	argc =0;
	t_mlx *mlx;
	mlx = malloc(sizeof(t_mlx));
	ft_memset(mlx, 0, sizeof(t_mlx));
	get_map(mlx, argv[1]);
	return 0;
}