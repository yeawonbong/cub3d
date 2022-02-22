/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow_quard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:19:01 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:19:01 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	follow_x1(t_data *data, t_player player, double theta)
{
	data->short_x = 0;
	data->follow.w_x = (int)(player.x) / BITSIZE * BITSIZE + BITSIZE;
	data->follow.w_y = (int)(player.y) / BITSIZE * BITSIZE + BITSIZE;
	while (data->map.maparr[(int)data->follow.w_y / BITSIZE - 1] \
							[(int)data->follow.w_x / BITSIZE - 1] != '1')
	{
		while_x1(data, player, theta);
	}
	data->wall_x = data->follow.w_x;
	data->wall_y = data->follow.w_y;
	if (data->follow.d_x < data->follow.d_y)
	{
		data->short_x = 1;
		return (data->follow.d_x);
	}
	else
		return (data->follow.d_y);
}

double	follow_x2(t_data *data, t_player player, double theta)
{
	data->short_x = 0;
	data->follow.w_x = (int)(player.x) / BITSIZE * BITSIZE;
	data->follow.w_y = (int)(player.y) / BITSIZE * BITSIZE + BITSIZE;
	while (data->map.maparr[(int)data->follow.w_y / BITSIZE - 1] \
							[(int)data->follow.w_x / BITSIZE] != '1')
	{
		while_x2(data, player, theta);
	}
	data->wall_x = data->follow.w_x + BITSIZE;
	data->wall_y = data->follow.w_y - BITSIZE;
	if (data->follow.d_x < data->follow.d_y)
	{
		data->short_x = 1;
		return (data->follow.d_x);
	}
	else
		return (data->follow.d_y);
}

double	follow_x3(t_data *data, t_player player, double theta)
{
	data->short_x = 0;
	data->follow.w_x = (int)(player.x) / BITSIZE * BITSIZE;
	data->follow.w_y = (int)(player.y) / BITSIZE * BITSIZE;
	while (data->map.maparr[(int)data->follow.w_y / BITSIZE] \
							[(int)data->follow.w_x / BITSIZE] != '1')
	{
		while_x3(data, player, theta);
	}
	data->wall_x = data->follow.w_x;
	data->wall_y = data->follow.w_y;
	if (data->follow.d_x < data->follow.d_y)
	{
		data->short_x = 1;
		return (data->follow.d_x);
	}
	else
		return (data->follow.d_y);
}

double	follow_x4(t_data *data, t_player player, double theta)
{
	data->short_x = 0;
	data->follow.w_x = (int)(player.x) / BITSIZE * BITSIZE + BITSIZE;
	data->follow.w_y = (int)(player.y) / BITSIZE * BITSIZE;
	while (data->map.maparr[(int)data->follow.w_y / BITSIZE] \
							[(int)data->follow.w_x / BITSIZE - 1] != '1')
	{
		while_x4(data, player, theta);
	}
	data->wall_x = data->follow.w_x - BITSIZE;
	data->wall_y = data->follow.w_y + BITSIZE;
	if (data->follow.d_x < data->follow.d_y)
	{
		data->short_x = 1;
		return (data->follow.d_x);
	}
	else
		return (data->follow.d_y);
}
