#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include <fcntl.h>
#include "get_next_line.h"
#include "mlx.h"
#include <math.h>
#include <time.h>
#include <pthread.h>

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124




// gcc -lmlx -framework OpenGL -framework Appkit testmain.c
// gcc -lmlx -framework OpenGL -framework Appkit testmain.c -L. -lgnl

char	arr[16001][10001]; // until 1600 * 1000

typedef struct	s_item
{
	int		x;
	int		y;
	int		ga;
	int		count;
}				t_item;

typedef struct	s_player
{
	float	oldx;
	float	oldy;
	float	x;
	float	y;
	int		up;
	int		down;
	int		left;
	int		right;
	int		num;
	int		count;
	int		color;
	int		pcolor;
	char	*charic;
	int		hack;
	int		hitted;

	float	HP;
	int		shoot;
	int		shooted;
	int		lose_count;
	int		frame;

	double	vec_x;
	double	vec_y;
	double	theta;
	float	move_speed;
}				t_player;


typedef struct	s_data {
	void	*mlx;
	void	*win;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	unsigned long	frame;
	int		item;
	int		now;
	int		clear;
	char	**map;
	int		m_width;
	int		m_height;
	int		wall_x;
	int		wall_y;
	int		short_x;

	t_player	player;

	int		m1;
	int		m2;

	float	aim;
	float	rotate_speed;
}				t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    vec_mlx_pixel_put(t_data *data, t_player *player, int i, int j, int color)
{
    char	*dst;
	float	x = player->x; // 중심점
	float	y = player->y;
	// i -= 40; // why??? -> +aim
	// j -= 40;

	dst = data->addr + ((int)(y + i * player->vec_y + j * sin(player->theta + M_PI_2)) * data->line_length
		+ (int)(x + i * player->vec_x + j * cos(player->theta + M_PI_2)) * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
	int		ga = 15;
	int		HP_count = 0;

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
	
	// if (keycode == 49)
	// 	data->player2.shoot = 1;
	if (keycode == 258)
		data->player.shoot = 1;

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
	// if (keycode == 34)
	// {
	// 	clear(data);
	// }
	if (keycode == 53)
		exit(0);

	return (0);
}

int		release(int keycode, t_data *data)
{
	// if (keycode == 49)
	// 	data->player2.shoot = 0;
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

	// if (keycode == 13)
	// 	data->player2.up = 0;
	// if (keycode == 1)
	// 	data->player2.down = 0;
	// if (keycode == 0)
	// 	data->player2.left = 0;
	// if (keycode == 2)
	// 	data->player2.right = 0;
	if (keycode == 53)
		exit(0);
	
	return (0);
}

void	moving(t_data *data, t_player *player)
{
	int x = player->x;
	int y = player->y;

	remove_pix(data, player);
	player->vec_x = cos(player->theta);
	player->vec_y = sin(player->theta);

	//printf("x, y = %d, %d\n", (int)player->x, (int)player->y);
	
	if (player->left == 1)
	{
		player->theta -= data->rotate_speed;
		//printf("x, y = (%f, %f)\n", player->vec_x, player->vec_y);
		//data->x -= 1;
	}
	if (player->right == 1)
	{
		player->theta += data->rotate_speed;
		//printf("x, y = (%f, %f)\n", player->vec_x, player->vec_y);
		//data->player->x += 1;
	}
	if (player->up == 1)
	{
		remove_pix(data, player);
		player->move_speed = 3;
		player->x += player->vec_x * player->move_speed;
		player->y += player->vec_y * player->move_speed;
	}
	if (player->down == 1) //&& player->y < data->height - 30
	{
		remove_pix(data, player);
		player->move_speed = -3;
		player->x += player->vec_x * player->move_speed;
		player->y += player->vec_y * player->move_speed;
	}
}

void	draw_things(t_data *data)
{
	int		ga = 80;
	int		se = 40;

	for(int i = -ga; i < ga; i++) // 1
	{
		for(int j = -se; j < se; j++)
		{
			my_mlx_pixel_put(data, i + data->width / 4 * 3, j + data->height / 3, 0x80CFCF90);
			arr[i * 10 + data->width / 4 * 10][j * 10 + data->height / 3 * 20] = 2;
		}
	}
	for(int i = -ga; i < ga; i++)
	{
		for(int j = -se; j < se; j++)
		{
			my_mlx_pixel_put(data, i + data->width / 4, j + data->height / 3 * 2, 0x80909FCF);
			arr[i * 10 + data->width / 4 * 30][j * 10 + data->height / 3 * 10] = 1;
		}
	}
	//mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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

void	draw(t_data *data, t_player *player, int color)
{
	float x = player->x;
	float y = player->y;

	draw_aim(*data, *player);
	draw_hack(data, player, 18, 0x0064D897);
	
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int		check_quard(t_player player)
{
	if (player.vec_x >= 0)
	{
		if (player.vec_y >= 0)
			return (1);
		else if (player.vec_y < 0)
			return (4);
	}
	else
	{
		if (player.vec_y >= 0)
			return (2);
		if (player.vec_y < 0)
			return (3);
	}
	return (0);
}

double	follow_x1(t_data *data, t_player player) // 1
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / 100 * 100 + 100;
	w_y = (int)(player.y) / 100 * 100 + 100;
	while (data->map[w_y / 100 - 1][w_x / 100 - 1] != '1') // && (w_x / 100) < data->m_width && (w_y / 100) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(player.theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(player.theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		if (d_x < d_y)
			w_x += 100;
		else
			w_y += 100;
	}

	data->wall_x = w_x - 100;
	data->wall_y = w_y - 100;
	// printf("d_x:%f d_y:%f, w_x:%d w_y:%d\n", d_x, d_y, w_x, w_y);
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

double	follow_x2(t_data *data, t_player player)
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / 100 * 100;
	w_y = (int)(player.y) / 100 * 100 + 100;
	while (data->map[w_y / 100 - 1][w_x / 100] != '1') // && (w_x / 100) < data->m_width && (w_y / 100) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(player.theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(player.theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		// if (data->map[w_y / 100][w_x / 100] == '1')
		// 	break ;
		if (d_x < d_y)
			w_x -= 100;
		else
			w_y += 100;
	}
	// d_x = (w_x - player.x) / cos(player.theta);
	// d_y = (w_y - player.y) / sin(player.theta);

	data->wall_x = w_x + 100;
	data->wall_y = w_y - 100;
	// printf("d_x:%f d_y:%f, w_x:%d w_y:%d\n", d_x, d_y, w_x, w_y);
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

double	follow_x3(t_data *data, t_player player)
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / 100 * 100;
	w_y = (int)(player.y) / 100 * 100;
	while (data->map[w_y / 100][w_x / 100] != '1') // && (w_x / 100) < data->m_width && (w_y / 100) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(player.theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(player.theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		// if (data->map[w_y / 100][w_x / 100] == '1')
		// 	break ;
		if (d_x < d_y)
			w_x -= 100;
		else
			w_y -= 100;
	}
	// d_x = (w_x - player.x) / cos(player.theta);
	// d_y = (w_y - player.y) / sin(player.theta);

	data->wall_x = w_x + 100;
	data->wall_y = w_y + 100;
	// printf("d_x:%f d_y:%f, w_x:%d w_y:%d\n", d_x, d_y, w_x, w_y);
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

double	follow_x4(t_data *data, t_player player)
{
	int		w_x;
	int		w_y;
	double	d_x;
	double	d_y;

	data->short_x = 0;
	w_x = (int)(player.x) / 100 * 100 + 100;
	w_y = (int)(player.y) / 100 * 100;
	while (data->map[w_y / 100][w_x / 100 - 1] != '1') // && (w_x / 100) < data->m_width && (w_y / 100) < data->m_height)
	{
		d_x = (w_x - player.x) / cos(player.theta); // x와 만나는 선의 길이
		d_y = (w_y - player.y) / sin(player.theta); // y와 만나는 선의 길이
		if (d_x < 0)
			d_x *= -1;
		if (d_y < 0)
			d_y *= -1;

		// if (data->map[w_y / 100][w_x / 100] == '1')
		// 	break ;
		if (d_x < d_y)
			w_x += 100;
		else
			w_y -= 100;
	}
	// d_x = (w_x - player.x) / cos(player.theta);
	// d_y = (w_y - player.y) / sin(player.theta);

	data->wall_x = w_x - 100;
	data->wall_y = w_y + 100;
	// printf("d_x:%f d_y:%f, w_x:%d w_y:%d\n", d_x, d_y, w_x, w_y);
	if (d_x < d_y)
	{
		data->short_x = 1;
		return (d_x);
	}
	else
		return (d_y);
}

void	find_wall(t_data *data, t_player player)
{
	int		quard;
	int		w_x;
	int		w_y;
	double	short_d;

	quard = check_quard(player);
	if (quard == 1) // 근데 여기선 4사분면 (보이는것만 4사분면이고 계산은 1사분면으로!)
	{
		short_d = follow_x1(data, player);
		if (short_d < 0)
			short_d *= -1;
		if (data->short_x == 1)
			my_mlx_pixel_put(data, data->wall_x, player.y + sin(player.theta) * short_d, 0x00FF0000);
		else
			my_mlx_pixel_put(data, player.x + cos(player.theta) * short_d, data->wall_y, 0x00FF0000);
	}
	if (quard == 2) // 근데 여기선 3사분면
	{
		short_d = follow_x2(data, player);
		if (short_d < 0)
			short_d *= -1;
		if (data->short_x == 1)
			my_mlx_pixel_put(data, data->wall_x, player.y + sin(player.theta) * short_d, 0x00FF0000);
		else
			my_mlx_pixel_put(data, player.x + cos(player.theta) * short_d, data->wall_y, 0x00FF0000);
	}
	if (quard == 3)
	{
		short_d = follow_x3(data, player);
		if (short_d < 0)
			short_d *= -1;
		if (data->short_x == 1)
			my_mlx_pixel_put(data, data->wall_x, player.y + sin(player.theta) * short_d, 0x00FF0000);
		else
			my_mlx_pixel_put(data, player.x + cos(player.theta) * short_d, data->wall_y, 0x00FF0000);
	}
	if (quard == 4)
	{
		short_d = follow_x4(data, player);
		if (short_d < 0)
			short_d *= -1;
		if (data->short_x == 1)
			my_mlx_pixel_put(data, data->wall_x, player.y + sin(player.theta) * short_d, 0x00FF0000);
		else
			my_mlx_pixel_put(data, player.x + cos(player.theta) * short_d, data->wall_y, 0x00FF0000);
	}
}

int		loop_ft(t_data *data)
{
	data->frame++;
	moving(data, &data->player);
	draw(data, &data->player, data->player.pcolor); // outside

	// printf("%lu\n", data->frame);
	if (data->frame % 50 == 1)
		printf("x:%f, y:%f\n", data->player.x, data->player.y);

	for(int i = 0; i < 10000; i++)
	{
		find_wall(data, data->player);
	}

	return (0);
}

void	dataset(t_data *data)
{
	data->width = 1080;
	data->height = 720;

	data->player.left = 0;
	data->player.right = 0;
	data->player.up = 0;
	data->player.down = 0;
	data->player.theta = 0; //M_PI;
	data->player.vec_x = 1;
	data->player.vec_y = 0;

	data->player.color = 0x00FFFF60;
	data->player.pcolor = 0x00FFFF60;
	data->player.hack = 0x80CF50CF;

	data->player.num = 2;
	data->player.charic = "left";

	data->frame = 0;
	data->now = 0;
	data->aim = 35;
	data->player.move_speed = 1.8;
	data->rotate_speed = 0.04;
}

void	set_map(int fd, char **argv, t_data *data)
{
	int		i;
	char	*line;
	int		width;

	line = 0;
	data->m_width = 0;
	get_next_line(fd, &line);
	while (line[data->m_width] != 0)
		data->m_width++;
	i = 1;
	while (get_next_line(fd, &line) > 0)
	{
		width = 0;
		while (line[width] != 0)
			width++;
		// if (data->width != width)
		// 	exit(1);
		i++;
	}
	data->map = (char **)malloc(sizeof(char *) * i + 1);
	data->m_height = i;
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (get_next_line(fd, &(data->map[i])))
		i++;
}

void	make_map(int fd, char **map)
{
	int		i;
	char	*line;
	int		width;

	line = 0;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		map[i] = line;
		// if (data->width != width)
		// 	exit(1);
		i++;
	}
}

void	mappasing(t_data *data, char **agv)
{
	int		fd;

	fd = open(agv[1], O_RDONLY);
	set_map(fd, agv, data);
	make_map(fd, data->map);
	data->player.x = data->m_width * 50;
	data->player.y = data->m_height * 50;
	data->width = data->m_width * 100;
	data->height = data->m_height * 100;
}

int		main(int agc, char *agv[])
{
	t_data	data;
	t_data	image;

	dataset(&data);
	data.mlx = mlx_init();
	if (agc == 2)
	{
		mappasing(&data, agv);
		// int i = -1;
		// while (data.map[++i])
		// 	printf("%s\n", data.map[i]);
		data.win = mlx_new_window(data.mlx, data.m_width * 100, data.m_height * 100, "minsikim_shooting");
	}
	else
		data.win = mlx_new_window(data.mlx, data.width, data.height, "minsikim_shooting");

	data.img = mlx_new_image(data.mlx, data.width, data.height + 100);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	mlx_hook(data.win, 2, 1L<<1, tracing, &data); // keyboard
	mlx_do_key_autorepeaton(data.mlx);
	mlx_hook(data.win, 3, 1L<<1, release, &data); // keyboard release
	mlx_loop_hook(data.mlx, loop_ft, &data);
	mlx_loop(data.mlx);
}