#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <pthread.h>

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"

# define KEYPRESS 2
# define REDCROSS 17
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define BITSIZE 64

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

// gcc -lmlx -framework OpenGL -framework Appkit testmain.c
// gcc -lmlx -framework OpenGL -framework Appkit testmain.c -L. -lgnl

// gcc -lmlx -framework OpenGL -framework Appkit testmain.c map.c libft.a -L. -lgnl
// arch -x86_64 gcc -lmlx -framework OpenGL -framework Appkit testmain.c map.c libft.a -L. -lgnl

char	arr[16001][10001]; // until 1600 * 1000

typedef struct	s_player
{
	float	oldx;
	float	oldy;
	float	x;
	float	y;
	char	dir;////임시로 방향 저장해놓음
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

	int		frame;

	double	vec_x;
	double	vec_y;
	double	theta;
	float	move_speed;
}				t_player;

typedef struct s_mapinfo
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
	int		f;
	int		c;
}			t_mapinfo;

typedef struct	s_map
{
	char		**maparr;
	int			height;
	int			width;

	t_mapinfo	info;
	
}				t_map;

typedef struct	s_img {
	void	*img_ptr;
	int		*img_data;
	int		w;
	int		h;
	int		bpp;
	int		line;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct	s_data {
	void	*mlx;
	void	*win;

	void	*img;
	int		*addr;

	int		bits_per_pixel;
	int		line_length;
	int		endian;
	unsigned long	frame;
	int		item;
	int		now;
	int		clear;
	int		wall_x;
	int		wall_y;
	int		short_x;
	int		space;

	void	*imgadd;
	char	**xpmdata;
	int		w;
	int		h;

	t_map		map;
	t_player	player;
	t_img		east;
	t_img		west;
	t_img		south;
	t_img		north;

	int		m1;
	int		m2;

	float	aim;
	float	rotate_speed;
}				t_data;

void	get_map_info(t_data *data, int fd);
int		isvalid_map(t_map *map, t_player *player);
void	get_map(t_data *data, char *filename);
void	map_error(char *msg);
int	get_map_info_process(t_data *data, int fd, char *line, int i);
int	isvalid_map_process(t_map *map, char **maparr, int i, int j);
void	get_map_size(t_data *data, char *line, int fd);

void    my_mlx_pixel_put(t_data *data, int x, int y, int color); //pixel_put.c
void    vec_mlx_pixel_put(t_data *data, t_player *player, int i, int j, int color);
int		set_color_shadow(double short_d, int color);
int		set_color(double short_d);

void	draw_aim(t_data data, t_player player); // draw_not_used.c
void	draw_hack(t_data *data, t_player *player, int ga, int color);

void	draw_up_down(t_data *data, t_map map); // draw.c
void	draw(t_data *data, t_player *player, int color);
void	remove_pix(t_data *data, t_player *player);

double	follow_x1(t_data *data, t_player player, double theta); // follow_quard.c
double	follow_x2(t_data *data, t_player player, double theta);
double	follow_x3(t_data *data, t_player player, double theta);
double	follow_x4(t_data *data, t_player player, double theta);

void	pixel_put_wall_1(t_data *data, double distance, double theta, int i); // pixel_put_wall.c
void	pixel_put_wall_2(t_data *data, double distance, double theta, int i);
void	remove_pixel_put_wall(t_data *data, int short_d, int i);

int		go_stopping(t_map map, t_player player); // moving.c
int		back_stopping(t_map map, t_player player);
void	moving(t_data *data, t_player *player);

int		check_quard(double theta); // find_wall.c
void	remove_find_wall(t_data *data, t_player player, double theta, int i);
void	find_wall(t_data *data, t_player player, double theta, int i);

void	img_set(t_data *data); // setting.c
void	dataset(t_data *data);

#endif