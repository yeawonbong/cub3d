/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow_while.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:19:04 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:19:05 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	while_x1(t_data *data, t_player player, double theta)
{
	data->follow.d_x = (data->follow.w_x - player.x) / cos(theta);
	data->follow.d_y = (data->follow.w_y - player.y) / sin(theta);
	if (data->follow.d_x < 0)
		data->follow.d_x *= -1;
	if (data->follow.d_y < 0)
		data->follow.d_y *= -1;
	if (data->follow.d_x <= data->follow.d_y)
		data->follow.w_x += BITSIZE;
	else
		data->follow.w_y += BITSIZE;
}

void	while_x2(t_data *data, t_player player, double theta)
{
	data->follow.d_x = (data->follow.w_x - player.x) / cos(theta);
	data->follow.d_y = (data->follow.w_y - player.y) / sin(theta);
	if (data->follow.d_x < 0)
		data->follow.d_x *= -1;
	if (data->follow.d_y < 0)
		data->follow.d_y *= -1;
	if (data->follow.d_x < data->follow.d_y)
		data->follow.w_x -= BITSIZE;
	else
		data->follow.w_y += BITSIZE;
}

void	while_x3(t_data *data, t_player player, double theta)
{
	data->follow.d_x = (data->follow.w_x - player.x) / cos(theta);
	data->follow.d_y = (data->follow.w_y - player.y) / sin(theta);
	if (data->follow.d_x < 0)
		data->follow.d_x *= -1;
	if (data->follow.d_y < 0)
		data->follow.d_y *= -1;
	if (data->follow.d_x < data->follow.d_y)
		data->follow.w_x -= BITSIZE;
	else
		data->follow.w_y -= BITSIZE;
}

void	while_x4(t_data *data, t_player player, double theta)
{
	data->follow.d_x = (data->follow.w_x - player.x) / cos(theta);
	data->follow.d_y = (data->follow.w_y - player.y) / sin(theta);
	if (data->follow.d_x < 0)
		data->follow.d_x *= -1;
	if (data->follow.d_y < 0)
		data->follow.d_y *= -1;
	if (data->follow.d_x < data->follow.d_y)
		data->follow.w_x += BITSIZE;
	else
		data->follow.w_y -= BITSIZE;
}
