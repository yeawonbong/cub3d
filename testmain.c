#include "cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

	dst = (char *)data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    vec_mlx_pixel_put(t_data *data, t_player *player, int i, int j, int color)
{
    char	*dst;
	float	x = player->x; // 중심점
	float	y = player->y;
	// i -= 40; // why??? -> +aim
	// j -= 40;

	dst = (char *)data->addr + ((int)(y + i * player->vec_y + j * sin(player->theta + M_PI_2)) * data->line_length
		+ (int)(x + i * player->vec_x + j * cos(player->theta + M_PI_2)) * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		set_color_shadow(double short_d, int color)
{
	int		r;
	int		g;
	int		b;
	int		t;

	r = (color & 0xFF0000 >> 16) - (short_d / 3);// 0xTTRRGGBB, 00000000 00000000 00000000 00000000
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

int		set_color(double short_d)
{
	int		r;
	int		g;
	int		b;
	int		t;

	r = 0xFF - (short_d / 3);// 0xTTRRGGBB, 00000000 00000000 00000000 00000000
	g = 0xFF - (short_d) / 3;
	b = 0xFF - ((short_d) / 3);
	if (r < 0)
		r = 0x00;
	if (g < 0)
		g = 0x00;
	if (b < 0)
		b = 0x00;
	return (r << 16 | g << 8 | b);
}

void	draw_aim(t_data data, t_player player)
{
	float x = player.x;
	float y = player.y;

	for (int i = 0; i < 4; i++) // aim
	{
		for (int j = 0; j < 4; j++)
		{
			my_mlx_pixel_put(&data, x + player.vec_x * (data.aim + 19) + i - 2, y + player.vec_y * (data.aim + 19) + j - 2, 0x00FF0000);
		}
	}
}

void	remove_pix(t_data *data, t_player *player)
{
	int		x = player->x;
	int		y = player->y;

	// printf("x:%d y:%d %f %f\n", x, y, player->vec_x, player->vec_y);
	for (int i = 0; i < 6; i++) // remove aim
	{
		for (int j = 0; j < 6; j++)
		{
			my_mlx_pixel_put(data, x + player->vec_x * (data->aim + 19) + i - 3, y + player->vec_y * (data->aim + 19) + j - 3, 0x00000000);
		}
	}
	for(int i = -20 / 2; i < 20 / 2; i++) // remove hack
	{
		for(int j = -20 / 2; j < 20 / 2; j++)
		{
			my_mlx_pixel_put(data, x + i, y + j, 0);
		}
	}
}

int		tracing(int keycode, t_data *data)
{
	//printf("%d\n", keycode);
	
	if (keycode == 49)
		data->space = 1;

	if (keycode == 126)
		data->player.up = 1;
	if (keycode == 125)
		data->player.down = 1;
	if (keycode == 123)
		data->player.left = 1;
	if (keycode == 124)
		data->player.right = 1;

	// if (keycode == 13)
	// 	data->player2.up = 1;
	// if (keycode == 1)
	// 	data->player2.down = 1;
	// if (keycode == 0)
	// 	data->player2.left = 1;
	// if (keycode == 2)
	// 	data->player2.right = 1;
	if (keycode == 53)
		exit(0);

	return (0);
}

int		release(int keycode, t_data *data)
{
	if (keycode == 49)
		data->space = 0;
	// else if (keycode == 258)
	// 	data->player.shoot = 0;
	if (keycode == 126)
		data->player.up = 0;
	if (keycode == 125)
		data->player.down = 0;
	if (keycode == 123)
		data->player.left = 0;
	if (keycode == 124)
		data->player.right = 0;

	if (keycode == 53)
		exit(0);
	
	return (0);
}

void	draw_hack(t_data *data, t_player *player, int ga, int color)
{
	int		x = player->x;
	int		y = player->y;

	for(int i = -ga / 2; i < ga / 2; i++)
	{
		for(int j = -ga / 2; j < ga / 2; j++)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
		}
	}
}



void	draw_up_down(t_data *data, t_map map)
{
	int		i;
	int		j;
	
	i = -1;
	while (++i < map.width)
	{
		j = -1;
		while(++j < map.height / 2)
		{
			my_mlx_pixel_put(data, i, map.height / 2 + j, map.info.f);
			my_mlx_pixel_put(data, i, map.height / 2 - j, map.info.c);
		}
	}
}

void	draw(t_data *data, t_player *player, int color)
{
	draw_aim(*data, *player);
	draw_hack(data, player, 18, 0x0064D897);
	draw_up_down(data, data->map);
}

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

int	follow_x1_no(t_data *data, t_player player, double theta) // 1
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	w_x = (int)(player.x) / BITSIZE * BITSIZE + BITSIZE;
	w_y = (int)(player.y) / BITSIZE * BITSIZE + BITSIZE;
	while (data->map.maparr[w_y / BITSIZE - 1][w_x / BITSIZE - 1] != '1') // && (w_x / BITSIZE) < data->map.width && (w_y / BITSIZE) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		if (d_x < d_y)
			w_x += BITSIZE;
		else
			w_y += BITSIZE;
	}

	if (d_x < d_y)
	{
		return (1);
	}
	else
		return (0);
}

double	follow_x1(t_data *data, t_player player, double theta) // 1
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / BITSIZE * BITSIZE + BITSIZE;
	w_y = (int)(player.y) / BITSIZE * BITSIZE + BITSIZE;
	while (data->map.maparr[w_y / BITSIZE - 1][w_x / BITSIZE - 1] != '1') // && (w_x / BITSIZE) < data->map.width && (w_y / BITSIZE) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		if (d_x < d_y)
			w_x += BITSIZE;
		else
			w_y += BITSIZE;
	}

	data->wall_x = w_x;
	data->wall_y = w_y;
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

double	follow_x2(t_data *data, t_player player, double theta)
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / BITSIZE * BITSIZE;
	w_y = (int)(player.y) / BITSIZE * BITSIZE + BITSIZE;
	while (data->map.maparr[w_y / BITSIZE - 1][w_x / BITSIZE] != '1') // && (w_x / BITSIZE) < data->map.width && (w_y / BITSIZE) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		if (d_x < d_y)
			w_x -= BITSIZE;
		else
			w_y += BITSIZE;
	}

	data->wall_x = w_x;
	data->wall_y = w_y;
	// printf("d_x:%f d_y:%f, w_x:%d w_y:%d\n", d_x, d_y, w_x, w_y);
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

double	follow_x3(t_data *data, t_player player, double theta)
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / BITSIZE * BITSIZE;
	w_y = (int)(player.y) / BITSIZE * BITSIZE;
	while (data->map.maparr[w_y / BITSIZE][w_x / BITSIZE] != '1') // && (w_x / BITSIZE) < data->map.width && (w_y / BITSIZE) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		if (d_x < d_y)
			w_x -= BITSIZE;
		else
			w_y -= BITSIZE;
	}

	data->wall_x = w_x;
	data->wall_y = w_y;
	// printf("d_x:%f d_y:%f, w_x:%d w_y:%d\n", d_x, d_y, w_x, w_y);
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

double	follow_x4(t_data *data, t_player player, double theta)
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / BITSIZE * BITSIZE + BITSIZE;
	w_y = (int)(player.y) / BITSIZE * BITSIZE;
	while (data->map.maparr[w_y / BITSIZE][w_x / BITSIZE - 1] != '1') // && (w_x / BITSIZE) < data->map.width && (w_y / BITSIZE) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		if (d_x < d_y)
			w_x += BITSIZE;
		else
			w_y -= BITSIZE;
	}

	data->wall_x = w_x;
	data->wall_y = w_y;
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

void	pixel_put_wall_1(t_data *data, double distance, double theta, int i)
{
	int		j;
	int		img_y;
	int		color_up;
	int		color_down;
	int		img_x;
	double	fish;
	int		shadow;

	fish = distance * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));

	img_x = data->wall_y - data->player.y - sin(theta) * distance;
	if (fish < 0)
		fish *= -1;
	
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / fish && j < data->map.height / 2)
	{
		img_y = (double)j * (BITSIZE / 2) / (data->map.height * (BITSIZE / 2) / fish);
		
		// printf("img_y:%d", img_y);
		// for (int k = 0; k < (data->map.height * (BITSIZE / 2) / fish) / BITSIZE; k++)
		if (cos(theta) > 0)
		{
			color_down = data->west.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->west.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		else
		{
			color_down = data->east.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->east.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		// color_up = set_color(fish);
		// color_down = set_color(fish);
		// printf("%d, %d\n", (i + (data->map.width / 2)) * 64 / data->map.width, (j % 64));
		// data->addr[i + data->west.w * (j)] = color;
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, color_down);
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - 1 - j, color_up);
	}
}

void	pixel_put_wall_2(t_data *data, double distance, double theta, int i)
{
	int		j;
	int		img_y;
	int		color_up;
	int		color_down;
	int		img_x;
	double	fish;
	int		shadow;

	fish = distance * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));

	img_x = data->wall_x + 64 - data->player.x - cos(theta) * distance;
	if (fish < 0)
		fish *= -1;
	
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / fish && j < data->map.height / 2)
	{
		img_y = (double)j * (BITSIZE / 2) / (data->map.height * (BITSIZE / 2) / fish);
		
		// for (int k = 0; k < (data->map.height * (BITSIZE / 2) / fish) / BITSIZE; k++)
		if (sin(theta) > 0)
		{
			color_down = data->north.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->north.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		else
		{
		// printf("img_x:%d, img_y:%d\ntest: %d, %d\n", img_x, img_y,(img_x + BITSIZE * (BITSIZE / 2 + img_y)), data->south.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)]);
			color_down = data->south.img_data[img_x + BITSIZE * (BITSIZE / 2 + img_y)];
			color_up = data->south.img_data[img_x + BITSIZE * (BITSIZE / 2 - img_y)];
		}
		// color_up = set_color(fish);
		// color_down = set_color(fish);
		// printf("%d, %d\n", (i + (data->map.width / 2)) * 64 / data->map.width, (j % 64));
		// data->addr[i + data->west.w * (j)] = color;
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, color_down);
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - 1 - j, color_up);
	}
}

// void	pixel_put_wall_2(t_data *data, int short_d, double theta, int i)
// {
// 	int		j;
// 	int		color;

// 	short_d = short_d * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));
// 	if (short_d < 0)
// 		short_d *= -1;
// 	if (data->map.height * (BITSIZE / 2) > data->map.height * short_d / 2)
// 		short_d = data->map.height * (BITSIZE / 2) / (data->map.height / 2);
// 	color = set_color(short_d) - 0x00151515;
// 	if (color < 0)
// 		color = 0;
// 	j = -1;
// 	while (++j < data->map.height * (BITSIZE / 2) / short_d)
// 	{
// 		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, color);
// 		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - j, color);
// 	}
// }

void	remove_pixel_put_wall(t_data *data, int short_d, int i)
{
	int		j;

	short_d = short_d * cos(((double)i / (data->map.width / 2)) * (M_PI / 6));
	if (short_d < 0)
		short_d *= -1;
	if (data->map.height * (BITSIZE / 2) > data->map.height * short_d / 2)
		short_d = data->map.height * (BITSIZE / 2) / (data->map.height / 2);
	j = -1;
	while (++j < data->map.height * (BITSIZE / 2) / short_d)
	{
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 + j, 0x00000000);
		my_mlx_pixel_put(data, i + data->map.width / 2, data->map.height / 2 - j, 0x00000000);
	}
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

// int	go_stopping(t_data *data, t_player player, double theta)
// {
// 	int		quard;
// 	int		w_x;
// 	int		w_y;
// 	double	short_d;

// 	quard = check_quard(theta); // for ray casting
// 	if (quard == 1) // 근데 여기선 4사분면 (보이는것만 4사분면이고 계산은 1사분면으로!)
// 	{
// 		short_d = follow_x1(data, player, theta);
// 	}
// 	if (quard == 2) // 근데 여기선 3사분면
// 	{
// 		short_d = follow_x2(data, player, theta);
// 	}
// 	if (quard == 3)
// 	{
// 		short_d = follow_x3(data, player, theta);
// 	}
// 	if (quard == 4)
// 	{
// 		short_d = follow_x4(data, player, theta);
// 	}
// 	printf("short_d = %f, player.m_s : %f", short_d, player.move_speed);
// 	if (short_d > 2 * player.move_speed)
// 		return (1);
// 	else
// 		return (0);
// }

int		go_stopping(t_map map, t_player player)
{
	double	v_x;
	double	v_y;

	v_x = player.vec_x;
	v_y = player.vec_y;
	if (player.vec_y < 0.3 && player.vec_y > 0) // 0 ~ 0.2
		v_y = 0.3;
	if (player.vec_y > -0.3 && player.vec_y < 0) // -0.2 < 0
		v_y = -0.3;
	if (player.vec_x < 0.3 && player.vec_x > 0) // 0 ~ 0.2
		v_x = 0.3;
	if (player.vec_x > -0.3 && player.vec_x < 0) // -0.2 < 0
		v_x = -0.3;

	if (map.maparr [(int)(player.y + v_y * 3 * player.move_speed) / BITSIZE]\
		[(int)(player.x + v_x * 3 * player.move_speed) / BITSIZE] == '1')
		return (0);
	return (1);
}

int		back_stopping(t_map map, t_player player)
{
	double	v_x;
	double	v_y;

	v_x = player.vec_x;
	v_y = player.vec_y;
	if (player.vec_y < 0.3 && player.vec_y > 0) // 0 ~ 0.2
		v_y = 0.3;
	if (player.vec_y > -0.3 && player.vec_y < 0) // -0.2 < 0
		v_y = -0.3;
	if (player.vec_x < 0.3 && player.vec_x > 0) // 0 ~ 0.2
		v_x = 0.3;
	if (player.vec_x > -0.3 && player.vec_x < 0) // -0.2 < 0
		v_x = -0.3;

	if (map.maparr [(int)(player.y - v_y * player.move_speed) / BITSIZE]\
		[(int)(player.x - 3 * v_x * player.move_speed) / BITSIZE] == '1')
		return (0);
	return (1);
}

void	moving(t_data *data, t_player *player)
{
	int x = player->x;
	int y = player->y;

	remove_pix(data, player);
	if (player->up || player->down || player->left || player->right)
	{
		for(int i = (-1) * data->map.width / 2; i < data->map.width / 2; i++)
		{
			remove_find_wall(data, data->player, data->player.theta + ((double)i / (data->map.width / 2)) * (M_PI / 6), i);
		}
	}
	player->vec_x = cos(player->theta);
	player->vec_y = sin(player->theta);

	if (player->left == 1)
		player->theta -= data->rotate_speed;
	if (player->right == 1)
		player->theta += data->rotate_speed;
	if (player->up == 1 && go_stopping(data->map, *player))
	{
		remove_pix(data, player);
		player->x += player->vec_x * player->move_speed;
		player->y += player->vec_y * player->move_speed;
	}
	if (player->down == 1 && back_stopping(data->map, *player)) //&& player->y < data->map.height - (BITSIZE / 2))
	{
		remove_pix(data, player);
		player->x -= player->vec_x * player->move_speed;
		player->y -= player->vec_y * player->move_speed;
	}
}

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

int		loop_ft(t_data *data)
{
	data->frame++;
	moving(data, &data->player); // (remove)
	draw(data, &data->player, data->player.pcolor); // outside

	// if (data->frame % 50 == 1)
	// 	printf("x:%f, y:%f\n", data->player.x, data->player.y);
	img_set(data); // 
	for(int i = -1 * data->map.width / 2; i < data->map.width / 2; i++)
	{
		find_wall(data, data->player, data->player.theta + ((double)i / (data->map.width / 2)) * (M_PI / 6), i);
	}
	
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->west.img_ptr, 0, 0); // 
	return (0);
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
	data->rotate_speed = 0.023;
}

int		main(int agc, char *argv[])
{
	t_data	data;
	t_data	image;

	dataset(&data);
	
	if (agc == 2)
	{
		get_map(&data, argv[1]);
		data.mlx = mlx_init();
		data.win = mlx_new_window(data.mlx, data.map.width, data.map.height, "minsikim_shooting");
	}
	else
		data.win = mlx_new_window(data.mlx, data.map.width, data.map.height, "minsikim_shooting");
	
	data.img = mlx_new_image(data.mlx, data.map.width, data.map.height + BITSIZE);
	data.addr = (int *)mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	mlx_hook(data.win, 2, 1L<<1, tracing, &data); // keyboard
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 3, 1L<<1, release, &data); // keyboard release
	mlx_loop_hook(data.mlx, loop_ft, &data);
	mlx_loop(data.mlx);
}