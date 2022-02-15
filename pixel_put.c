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

	t = 0x00;
	r = 0xFF - (short_d / 3);// 0xTTRRGGBB, 00000000 00000000 00000000 00000000
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