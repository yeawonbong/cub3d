#include "cub3d.h"

void	img_set(t_data *data)
{
	t_mapinfo info;

	info = data->map.info;
	data->west.img_ptr = mlx_xpm_file_to_image(data->mlx, info.west, &data->west.w, &data->west.h);
	data->west.img_data = (int *)mlx_get_data_addr(data->west.img_ptr, &data->west.bpp, &data->west.line, &data->west.endian);
	data->south.img_ptr = mlx_xpm_file_to_image(data->mlx, info.south, &data->south.w, &data->south.h);
	data->south.img_data = (int *)mlx_get_data_addr(data->south.img_ptr, &data->south.bpp, &data->south.line, &data->south.endian);
	data->east.img_ptr = mlx_xpm_file_to_image(data->mlx, info.east, &data->south.w, &data->south.h);
	data->east.img_data = (int *)mlx_get_data_addr(data->east.img_ptr, &data->east.bpp, &data->east.line, &data->east.endian);
	data->north.img_ptr = mlx_xpm_file_to_image(data->mlx, info.north, &data->north.w, &data->north.h);
	data->north.img_data = (int *)mlx_get_data_addr(data->north.img_ptr, &data->north.bpp, &data->north.line, &data->north.endian);
	int color;
	// for (int i = 0; i < 10; i++)//west->img_data[i]; i++)
	// printf("img_data:%x\n", west->img_data[15 + 4 * 64]);
	for (int i = 0; i < BITSIZE; i++)
	{
		for (int j = 0; j < BITSIZE; j++)
		{
			color = data->south.img_data[i + BITSIZE * j];
			my_mlx_pixel_put(data, i, j, color);
		}
	}
	
	// my_mlx_pixel_put(west->img)
	// data.imgadd = mlx_xpm_to_image(data.mlx, data.xpmdata, &data.w, &data.h);
}

void	dataset(t_data *data)
{
	data->player.left = 0;
	data->player.right = 0;
	data->player.up = 0;
	data->player.down = 0;
	data->player.dir = 0;

	data->player.color = 0x00FFFF60;
	data->player.pcolor = 0x00FFFF60;
	data->player.hack = 0x80CF50CF;

	data->frame = 0;
	data->now = 0;
	data->aim = 35;
	data->player.move_speed = 3;
	data->rotate_speed = 0.026;
}
