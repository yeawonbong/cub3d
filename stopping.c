/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:19:28 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:29:02 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	go_stopping(t_map map, t_player player)
{
	double	v_x;
	double	v_y;

	v_x = player.vec_x;
	v_y = player.vec_y;
	if (player.vec_y < 0.3 && player.vec_y > 0)
		v_y = 0.3;
	if (player.vec_y > -0.3 && player.vec_y < 0)
		v_y = -0.3;
	if (player.vec_x < 0.3 && player.vec_x > 0)
		v_x = 0.3;
	if (player.vec_x > -0.3 && player.vec_x < 0)
		v_x = -0.3;
	if (map.maparr[(int)(player.y + v_y * 3 * player.move_speed) / BITSIZE] \
		[(int)(player.x + v_x * 3 * player.move_speed) / BITSIZE] == '1')
		return (0);
	if (map.maparr[(int)(player.y + v_y * 2 * player.move_speed) / BITSIZE] \
		[(int)(player.x + v_x * 2 * player.move_speed) / BITSIZE] == '1')
		return (0);
	return (1);
}

int	back_stopping(t_map map, t_player player)
{
	double	v_x;
	double	v_y;

	v_x = player.vec_x;
	v_y = player.vec_y;
	if (player.vec_y < 0.3 && player.vec_y > 0)
		v_y = 0.3;
	if (player.vec_y > -0.3 && player.vec_y < 0)
		v_y = -0.3;
	if (player.vec_x < 0.3 && player.vec_x > 0)
		v_x = 0.3;
	if (player.vec_x > -0.3 && player.vec_x < 0)
		v_x = -0.3;
	if (map.maparr[(int)(player.y - v_y * player.move_speed) / BITSIZE] \
		[(int)(player.x - 3 * v_x * player.move_speed) / BITSIZE] == '1')
		return (0);
	return (1);
}

int	left_stopping(t_map map, t_player player)
{
	if (map.maparr[(int)(player.y + \
		sin(player.theta + 3 * M_PI / 2) * player.move_speed) / BITSIZE] \
		[(int)(player.x + cos(player.theta + 3 * M_PI / 2) * \
			player.move_speed) / BITSIZE] == '1')
		return (0);
	return (1);
}

int	right_stopping(t_map map, t_player player)
{
	if (map.maparr[(int)(player.y + sin(player.theta + M_PI / 2) \
		* player.move_speed) / BITSIZE] \
		[(int)(player.x + cos(player.theta + M_PI / 2) \
			* player.move_speed) / BITSIZE] == '1')
		return (0);
	return (1);
}
