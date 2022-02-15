#include "cub3d.h"

int	free_exit(t_data *data)
{
	int		i;

	free(data->map.info.north);
	free(data->map.info.south);
	free(data->map.info.west);
	free(data->map.info.east);
	free(data->map.info.floor);
	free(data->map.info.ceiling);
	i = 0;
	while (data->map.maparr[i])
	{
		free(data->map.maparr[i]);
		i++;
	}
	free(data->map.maparr);
	system("leaks cub3d");
	exit(0);
}

int	tracing(int keycode, t_data *data)
{
	if (keycode == 49)
		data->space = 1;
	if (keycode == 126)
		data->player.up = 1;
	if (keycode == 125)
		data->player.down = 1;
	if (keycode == 123)
		data->player.left = 1;
	if (keycode == 124)
		data->player.right = 1;
	if (keycode == 53)
	{
		free_exit(data);
	}
	return (0);
}

int	release(int keycode, t_data *data)
{
	if (keycode == 49)
		data->space = 0;
	if (keycode == 126)
		data->player.up = 0;
	if (keycode == 125)
		data->player.down = 0;
	if (keycode == 123)
		data->player.left = 0;
	if (keycode == 124)
		data->player.right = 0;
	if (keycode == 53)
	{
		free_exit(data);
	}
	return (0);
}

int	loop_ft(t_data *data)
{
	int		i;

	data->frame++;
	moving(data, &data->player);
	draw_up_down(data, data->map);
	i = -1 * data->map.width / 2;
	while (i < data->map.width / 2)
	{
		find_wall(data, data->player, data->player.theta + \
			((double)i / (data->map.width / 2)) * (M_PI / 6), i);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int agc, char *argv[])
{
	t_data	data;
	t_data	image;

	dataset(&data);
	if (agc == 2)
	{
		get_map(&data, argv[1]);
		data.mlx = mlx_init();
		data.win = mlx_new_window(data.mlx, \
			data.map.width, data.map.height, "cub3D");
	}
	else
		map_error("Invalid input");
	data.img = mlx_new_image(data.mlx, \
		data.map.width, data.map.height + BITSIZE);
	data.addr = (int *)mlx_get_data_addr(data.img, \
		&data.bits_per_pixel, &data.line_length, &data.endian);
	img_set(&data);
	mlx_hook(data.win, 2, 1L << 1, tracing, &data);
	mlx_hook(data.win, 17, 1L << 1, free_exit, &data);
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 3, 1L << 1, release, &data);
	mlx_loop_hook(data.mlx, loop_ft, &data);
	mlx_loop(data.mlx);
}
