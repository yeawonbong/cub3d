#include "cub3d.h"

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
		free(line);
	}
	free(line);
	close(fd);
}

void	set_direction(t_player *player)
{
	if (player->dir == 'N')
	{
		player->theta = 3 * M_PI / 2 + 0.001;
		player->vec_x = 0;
		player->vec_y = 1;
	}
	if (player->dir == 'S')
	{
		player->theta = M_PI / 2 + 0.001;
		player->vec_x = 0;
		player->vec_y = -1;
	}
	if (player->dir == 'E')
	{
		player->theta = 0.001;
		player->vec_x = 1;
		player->vec_y = 0;
	}
	if (player->dir == 'W')
	{
		player->theta = M_PI + 0.001;
		player->vec_x = -1;
		player->vec_y = 0;
	}
}

int	set_fc(char *fc)
{
	int		r;
	int		g;
	int		b;
	char	**arr;
	int		color;

	arr = ft_split(fc, ',');
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	free(arr[0]);
	free(arr[1]);
	free(arr[2]);
	free(arr);
	color = (r << 16 | g << 8 | b);
	return (color);
}

void	map_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
