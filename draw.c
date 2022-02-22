/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:18:51 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:18:51 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_up_down(t_data *data, t_map map)
{
	int		i;
	int		j;
	int		color;

	i = -1;
	while (++i < map.width)
	{
		j = -1;
		while (++j < map.height / 2)
		{
			my_mlx_pixel_put(data, i, map.height / 2 + j, map.info.f);
			my_mlx_pixel_put(data, i, map.height / 2 - j, map.info.c);
		}
	}
}
