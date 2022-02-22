/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:19:18 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:19:19 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_x_helper(t_data *data, int i, int j, double theta)
{
	int		color_up;
	int		color_down;

	data->img_y = (double)j * (BITSIZE / 2) / \
					(data->map.height * (BITSIZE / 2) / data->fish);
	if (cos(theta) > 0)
	{
		color_down = data->west.img_data[data->img_x \
			+ BITSIZE * (BITSIZE / 2 + data->img_y)];
		color_up = data->west.img_data[data->img_x \
			+ BITSIZE * (BITSIZE / 2 - data->img_y)];
	}
	else
	{
		color_down = data->east.img_data[data->img_x \
			+ BITSIZE * (BITSIZE / 2 + data->img_y)];
		color_up = data->east.img_data[data->img_x \
			+ BITSIZE * (BITSIZE / 2 - data->img_y)];
	}
	my_mlx_pixel_put(data, i + data->map.width / 2, \
							data->map.height / 2 + j, color_down);
	my_mlx_pixel_put(data, i + data->map.width / 2, \
							data->map.height / 2 - 1 - j, color_up);
}

void	wall_y_helper(t_data *data, int i, int j, double theta)
{
	int		color_down;
	int		color_up;

	data->img_y = (j * (BITSIZE / 2) / \
					(data->map.height * (BITSIZE / 2) / data->fish));
	if (sin(theta) > 0)
	{
		color_down = data->north.img_data[data->img_x \
			+ BITSIZE * (BITSIZE / 2 + data->img_y)];
		color_up = data->north.img_data[data->img_x \
			+ BITSIZE * (BITSIZE / 2 - data->img_y)];
	}
	else
	{
		color_down = data->south.img_data[data->img_x \
			+ (BITSIZE * (BITSIZE / 2 + data->img_y))];
		color_up = data->south.img_data[data->img_x \
			+ (BITSIZE * (BITSIZE / 2 - data->img_y))];
	}
	my_mlx_pixel_put(data, i + data->map.width / 2, \
							data->map.height / 2 + j, color_down);
	my_mlx_pixel_put(data, i + data->map.width / 2, \
							data->map.height / 2 - 1 - j, color_up);
}

void	pixel_put_wall_x(t_data *data, double distance, double theta, int i)
{
	int		j;

	data->fish = distance * cos(((double)i \
		/ (data->map.width / 2)) * (M_PI / 6));
	if (data->fish < 0)
		data->fish *= -1;
	data->img_x = data->wall_y - data->player.y - sin(theta) * distance;
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / data->fish \
			&& j < data->map.height / 2)
	{
		wall_x_helper(data, i, j, theta);
	}
}

void	pixel_put_wall_y(t_data *data, double distance, double theta, int i)
{
	int		j;

	data->fish = distance * cos(((double)i \
		/ (data->map.width / 2)) * (M_PI / 6));
	if (data->fish < 0)
		data->fish *= -1;
	data->img_x = data->wall_x - data->player.x - cos(theta) * distance;
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / data->fish \
			&& j < data->map.height / 2)
	{
		wall_y_helper(data, i, j, theta);
	}
}

void	remove_pixel_put_wall(t_data *data, int short_d, int i)
{
	int		j;

	short_d = short_d * cos(((double)i \
		/ (data->map.width / 2)) * (M_PI / 6));
	if (short_d < 0)
		short_d *= -1;
	if (data->map.height * (BITSIZE / 2) > data->map.height * short_d / 2)
		short_d = data->map.height * (BITSIZE / 2) / (data->map.height / 2);
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / short_d)
	{
		my_mlx_pixel_put(data, i + data->map.width / 2, \
								data->map.height / 2 + j, 0x00000000);
		my_mlx_pixel_put(data, i + data->map.width / 2, \
								data->map.height / 2 - j, 0x00000000);
	}
}
