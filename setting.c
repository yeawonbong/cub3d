/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:18:26 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:18:27 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_set(t_data *data)
{
	t_mapinfo	info;

	info = data->map.info;
	data->west.img_ptr = mlx_xpm_file_to_image(\
		data->mlx, info.west, &data->west.w, &data->west.h);
	data->south.img_ptr = mlx_xpm_file_to_image(\
	 	data->mlx, info.south, &data->south.w, &data->south.h);
	data->east.img_ptr = mlx_xpm_file_to_image(\
	 	data->mlx, info.east, &data->south.w, &data->south.h);
	data->north.img_ptr = mlx_xpm_file_to_image(\
	 	data->mlx, info.north, &data->north.w, &data->north.h);
	if (!data->west.img_ptr || !data->east.img_ptr || \
		!data->south.img_ptr || !data->north.img_ptr)
		map_error("Invalid map");
	data->north.img_data = (int *)mlx_get_data_addr(data->north.img_ptr, \
		&data->north.bpp, &data->north.line, &data->north.endian);
	data->east.img_data = (int *)mlx_get_data_addr(data->east.img_ptr, \
		&data->east.bpp, &data->east.line, &data->east.endian);
	data->south.img_data = (int *)mlx_get_data_addr(data->south.img_ptr, \
		&data->south.bpp, &data->south.line, &data->south.endian);
	data->west.img_data = (int *)mlx_get_data_addr(data->west.img_ptr, \
		&data->west.bpp, &data->west.line, &data->west.endian);
}

void	dataset(t_data *data)
{
	data->player.left = 0;
	data->player.right = 0;
	data->player.up = 0;
	data->player.down = 0;
	data->player.rotate_left = 0;
	data->player.rotate_right = 0;
	data->player.dir = 0;
	data->frame = 0;
	data->player.move_speed = 3;
	data->rotate_speed = 0.026;
	ft_memset((t_map *)&data->map, 0, sizeof(t_map));
	data->map.maparr = 0;
}
