#include "cub3d.h"

int		check_quard(double theta)
{
	double	vec_x;
	double	vec_y;

	vec_y = sin(theta);
	vec_x = cos(theta);
	if (vec_x >= 0)
	{
		if (vec_y >= 0)
			return (1);
		else if (vec_y < 0)
			return (4);
	}
	else
	{
		if (vec_y >= 0)
			return (2);
		if (vec_y < 0)
			return (3);
	}
	return (0);
}

void	remove_find_wall(t_data *data, t_player player, double theta, int i)
{
	int		quard;
	int		w_x;
	int		w_y;
	double	short_d;

	quard = check_quard(theta);
	if (quard == 1) // 근데 여기선 4사분면 (보이는것만 4사분면이고 계산은 1사분면으로!)
	{
		short_d = follow_x1(data, player, theta);
		remove_pixel_put_wall(data, (int)short_d, i);
	}
	if (quard == 2) // 근데 여기선 3사분면
	{
		short_d = follow_x2(data, player, theta);
		remove_pixel_put_wall(data, (int)short_d, i);
	}
	if (quard == 3)
	{
		short_d = follow_x3(data, player, theta);
		remove_pixel_put_wall(data, (int)short_d, i);
	}
	if (quard == 4)
	{
		short_d = follow_x4(data, player, theta);
		remove_pixel_put_wall(data, (int)short_d, i);
	}
}

void	find_wall(t_data *data, t_player player, double theta, int i)
{
	int		quard;
	int		w_x;
	int		w_y;
	double	short_d;

	quard = check_quard(theta); // for ray casting
	if (quard == 1) // 근데 여기선 4사분면 (보이는것만 4사분면이고 계산은 1사분면으로!)
	{
		short_d = follow_x1(data, player, theta);
		if (data->short_x == 1)
			pixel_put_wall_1(data, short_d, theta, i);
		else
			pixel_put_wall_2(data, short_d, theta, i);
	}
	if (quard == 2) // 근데 여기선 3사분면
	{
		short_d = follow_x2(data, player, theta);
		
		if (data->short_x == 1)
			pixel_put_wall_1(data, short_d, theta, i);
		else
			pixel_put_wall_2(data, short_d, theta, i);
	}
	if (quard == 3)
	{
		short_d = follow_x3(data, player, theta);
		if (data->short_x == 1)
			pixel_put_wall_1(data, short_d, theta, i);
		else
			pixel_put_wall_2(data, short_d, theta, i);
	}
	if (quard == 4)
	{
		short_d = follow_x4(data, player, theta);
		if (data->short_x == 1)
			pixel_put_wall_1(data, short_d, theta, i);
		else
			pixel_put_wall_2(data, short_d, theta, i);
	}
}

// int	follow_x1_no(t_data *data, t_player player, double theta) // 1
// {
// 	int		w_x;
// 	int		w_y;
// 	double	d_x;
// 	double	d_y;

// 	w_x = (int)(player.x) / BITSIZE * BITSIZE + BITSIZE;
// 	w_y = (int)(player.y) / BITSIZE * BITSIZE + BITSIZE;
// 	while (data->map.maparr[w_y / BITSIZE - 1][w_x / BITSIZE - 1] != '1') // && (w_x / BITSIZE) < data->map.width && (w_y / BITSIZE) < data->m_height)
// 	{
// 		d_x = (w_x - player.x) / cos(theta); // x와 만나는 선의 길이
// 		d_y = (w_y - player.y) / sin(theta); // y와 만나는 선의 길이
// 		if (d_x < 0)
// 			d_x *= -1;
// 		if (d_y < 0)
// 			d_y *= -1;

// 		if (d_x < d_y)
// 			w_x += BITSIZE;
// 		else
// 			w_y += BITSIZE;
// 	}

// 	if (d_x < d_y)
// 	{
// 		return (1);
// 	}
// 	else
// 		return (0);
// }