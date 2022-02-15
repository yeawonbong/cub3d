#include "cub3d.h"

int		tracing(int keycode, t_data *data)
{
	//printf("%d\n", keycode);
	
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

	// if (keycode == 13)
	// 	data->player2.up = 1;
	// if (keycode == 1)
	// 	data->player2.down = 1;
	// if (keycode == 0)
	// 	data->player2.left = 1;
	// if (keycode == 2)
	// 	data->player2.right = 1;
	if (keycode == 53)
		exit(0);

	return (0);
}

int		release(int keycode, t_data *data)
{
	if (keycode == 49)
		data->space = 0;
	// else if (keycode == 258)
	// 	data->player.shoot = 0;
	if (keycode == 126)
		data->player.up = 0;
	if (keycode == 125)
		data->player.down = 0;
	if (keycode == 123)
		data->player.left = 0;
	if (keycode == 124)
		data->player.right = 0;

	if (keycode == 53)
		exit(0);
	
	return (0);
}

int		loop_ft(t_data *data)
{
	data->frame++;
	moving(data, &data->player); // (remove)
	draw(data, &data->player, data->player.pcolor); // outside

	// if (data->frame % 50 == 1)
	// 	printf("x:%f, y:%f\n", data->player.x, data->player.y);
	img_set(data); // 
	for(int i = -1 * data->map.width / 2; i < data->map.width / 2; i++)
	{
		find_wall(data, data->player, data->player.theta + ((double)i / (data->map.width / 2)) * (M_PI / 6), i);
	}
	
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->west.img_ptr, 0, 0); // 
	return (0);
}

int		main(int agc, char *argv[])
{
	t_data	data;
	t_data	image;

	dataset(&data);
	
	if (agc == 2)
	{
		get_map(&data, argv[1]);
		data.mlx = mlx_init();
		data.win = mlx_new_window(data.mlx, data.map.width, data.map.height, "minsikim_shooting");
	}
	else
		data.win = mlx_new_window(data.mlx, data.map.width, data.map.height, "minsikim_shooting");
	
	data.img = mlx_new_image(data.mlx, data.map.width, data.map.height + BITSIZE);
	data.addr = (int *)mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	mlx_hook(data.win, 2, 1L<<1, tracing, &data); // keyboard
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 3, 1L<<1, release, &data); // keyboard release
	mlx_loop_hook(data.mlx, loop_ft, &data);
	mlx_loop(data.mlx);
}