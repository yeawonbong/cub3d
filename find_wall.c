/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:18:58 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:18:58 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_quard(double theta)
{
	double	vec_x;
	double	vec_y;

	vec_y = sin(theta);
	vec_x = cos(theta);
	if (vec_x >= 0)
	{
		if (vec_y >= 0)
			return (1);
		else
			return (4);
	}
	else
	{
		if (vec_y >= 0)
			return (2);
		else
			return (3);
	}
	return (0);
}

void	remove_find_wall(t_data *data, t_player player, double theta, int i)
{
	int		quard;
	int		w_x;
	int		w_y;

	quard = check_quard(theta);
	if (quard == 1)
	{
		remove_pixel_put_wall(data, follow_x1(data, player, theta), i);
	}
	if (quard == 2)
	{
		remove_pixel_put_wall(data, follow_x2(data, player, theta), i);
	}
	if (quard == 3)
	{
		remove_pixel_put_wall(data, follow_x3(data, player, theta), i);
	}
	if (quard == 4)
	{
		remove_pixel_put_wall(data, follow_x4(data, player, theta), i);
	}
}

void	find_wall_34(t_data *data, t_player player, double theta, int i)
{
	if (data->quard == 3)
	{
		if (data->short_x == 1)
			pixel_put_wall_x(data, follow_x3(data, player, theta), theta, i);
		else
			pixel_put_wall_y(data, follow_x3(data, player, theta), theta, i);
	}
	if (data->quard == 4)
	{
		if (data->short_x == 1)
			pixel_put_wall_x(data, follow_x4(data, player, theta), theta, i);
		else
		{
			pixel_put_wall_y(data, follow_x4(data, player, theta), theta, i);
		}
	}
}

void	find_wall(t_data *data, t_player player, double theta, int i)
{
	int		w_x;
	int		w_y;

	data->quard = check_quard(theta);
	if (data->quard == 1)
	{
		if (data->short_x == 1)
			pixel_put_wall_x(data, follow_x1(data, player, theta), theta, i);
		else
			pixel_put_wall_y(data, follow_x1(data, player, theta), theta, i);
	}
	else if (data->quard == 2)
	{
		if (data->short_x == 1)
			pixel_put_wall_x(data, follow_x2(data, player, theta), theta, i);
		else
			pixel_put_wall_y(data, follow_x2(data, player, theta), theta, i);
	}
	else
		find_wall_34(data, player, theta, i);
}
