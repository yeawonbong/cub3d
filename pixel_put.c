/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:19:22 by minsikim          #+#    #+#             */
/*   Updated: 2022/02/21 12:19:22 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->addr + \
		(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	set_color_shadow(double short_d, int color)
{
	int		r;
	int		g;
	int		b;
	int		t;

	r = (color & 0xFF0000 >> 16) - (short_d / 3);
	g = (color & 0xFF00 >> 8) - (short_d) / 3;
	b = (color & 0xFF) - ((short_d) / 3);
	if (r < 0)
		r = 0x00;
	if (g < 0)
		g = 0x00;
	if (b < 0)
		b = 0x00;
	return (r << 16 | g << 8 | b);
}

int	set_color(double short_d)
{
	int		r;
	int		g;
	int		b;
	int		t;

	t = 0x00;
	r = 0xFF - (short_d / 3);
	g = 0xFF - (short_d) / 3;
	b = 0xFF - ((short_d) / 3);
	if (r < 0)
		r = 0x00;
	if (g < 0)
		g = 0x00;
	if (b < 0)
		b = 0x00;
	return (t << 24 | r << 16 | g << 8 | b);
}
