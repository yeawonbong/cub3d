#include "cub3d.h"

void	pixel_put_wall_1(t_data *data, double distance, double theta, int i)
{
	int		j;
	int		img_y;
	int		color_up;
	int		color_down;
	int		img_x;
	double	fish;
	int		shadow;

	fish = distance * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));

	img_x = data->wall_y - data->player.y - sin(theta) * distance;
	if (fish < 0)
		fish *= -1;
	
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / fish && j < data->map.height / 2)
	{
		img_y = (double)j * (BITSIZE / 2) / (data->map.height * (BITSIZE / 2) / fish);
		
		// printf("img_y:%d", img_y);
		// for (int k = 0; k < (data->map.height * (BITSIZE / 2) / fish) / BITSIZE; k++)
		if (cos(theta) > 0)
		{
			color_down = data->west.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->west.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		else
		{
			color_down = data->east.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->east.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		color_up = set_color(fish);
		color_down = set_color(fish);
		// printf("%d, %d\n", (i + (data->map.width / 2)) * 64 / data->map.width, (j % 64));
		// data->addr[i + data->west.w * (j)] = color;
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, color_down);
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - 1 - j, color_up);
	}
}

void	pixel_put_wall_2(t_data *data, double distance, double theta, int i)
{
	int		j;
	int		img_y;
	int		color_up;
	int		color_down;
	int		img_x;
	double	fish;
	int		shadow;

	fish = distance * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));

	img_x = data->wall_x + 64 - data->player.x - cos(theta) * distance;
	if (fish < 0)
		fish *= -1;
	
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / fish && j < data->map.height / 2)
	{
		img_y = (double)j * (BITSIZE / 2) / (data->map.height * (BITSIZE / 2) / fish);
		
		// for (int k = 0; k < (data->map.height * (BITSIZE / 2) / fish) / BITSIZE; k++)
		if (sin(theta) > 0)
		{
			color_down = data->north.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->north.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		else
		{
		// printf("img_x:%d, img_y:%d\ntest: %d, %d\n", img_x, img_y,(img_x + BITSIZE * (BITSIZE / 2 + img_y)), data->south.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)]);
			color_down = data->south.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->south.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		color_up = set_color(fish);
		color_down = set_color(fish);
		// printf("%d, %d\n", (i + (data->map.width / 2)) * 64 / data->map.width, (j % 64));
		// data->addr[i + data->west.w * (j)] = color;
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, color_down);
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - 1 - j, color_up);
	}
}

// void	pixel_put_wall_2(t_data *data, int short_d, double theta, int i)
// {
// 	int		j;
// 	int		color;

// 	short_d = short_d * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));
// 	if (short_d < 0)
// 		short_d *= -1;
// 	if (data->map.height * (BITSIZE / 2) > data->map.height * short_d / 2)
// 		short_d = data->map.height * (BITSIZE / 2) / (data->map.height / 2);
// 	color = set_color(short_d) - 0x00151515;
// 	if (color < 0)
// 		color = 0;
// 	j = -1;
// 	while (++j < data->map.height * (BITSIZE / 2) / short_d)
// 	{
// 		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, color);
// 		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - j, color);
// 	}
// }

void	remove_pixel_put_wall(t_data *data, int short_d, int i)
{
	int		j;

	short_d = short_d * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));
	if (short_d < 0)
		short_d *= -1;
	if (data->map.height * (BITSIZE / 2) > data->map.height * short_d / 2)
		short_d = data->map.height * (BITSIZE / 2) / (data->map.height / 2);
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / short_d)
	{
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, 0x00000000);
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - j, 0x00000000);
	}
}