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

typedef struct s_player
{
	float	oldx;
	float	oldy;
	float	x;
	float	y;
	char	dir;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rotate_left;
	int		rotate_right;

	int		frame;

	double	vec_x;
	double	vec_y;
	double	theta;
	float	move_speed;
}				t_player;

typedef struct s_follow
{
	float	w_x;
	float	w_y;
	float	d_x;
	float	d_y;
}			t_follow;

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

typedef struct s_map
{
	char		**maparr;
	int			height;
	int			width;

	t_mapinfo	info;
}				t_map;

typedef struct s_img {
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

typedef struct s_data {
	void		*mlx;
	void		*win;

	void		*img;
	int			*addr;

	int			bits_per_pixel;
	int			line_length;
	int			endian;
	long long	frame;
	int			wall_x;
	int			wall_y;
	int			short_x;
	int			quard;
	int			img_x;
	int			img_y;
	double		fish;

	int			w;
	int			h;

	t_map		map;
	t_player	player;
	t_follow	follow;
	t_img		east;
	t_img		west;
	t_img		south;
	t_img		north;

	float		rotate_speed;
}				t_data;

/*
**map.c
*/
void	get_map_info(t_data *data, int fd);
int		isvalid_map(t_map *map, t_player *player);
void	get_map(t_data *data, char *filename);
int		get_map_info_process(t_data *data, int fd, char *line, int i);
int		isvalid_map_process(t_map *map, char **maparr, int i, int j);

/*
**map_util.c
*/
void	get_map_size(t_data *data, char *line, int fd);
void	set_direction(t_player *player);
int		set_fc(char *fc);
void	map_error(char *msg);

/*
**pixel_put.c
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		set_color_shadow(double short_d, int color);
int		set_color(double short_d);

/*
**draw_not_used.c
*/
void	draw_aim(t_data data, t_player player);
void	draw_hack(t_data *data, t_player *player, int ga, int color);
void	remove_pix(t_data *data, t_player *player);

/*
**draw.c
*/
void	draw_up_down(t_data *data, t_map map);
void	draw(t_data *data, t_player *player, int color);

/*
** follow_quard.c
*/
double	follow_x1(t_data *data, t_player player, double theta);
double	follow_x2(t_data *data, t_player player, double theta);
double	follow_x3(t_data *data, t_player player, double theta);
double	follow_x4(t_data *data, t_player player, double theta);

/*
**follow_while.c
*/
void	while_x1(t_data *data, t_player player, double theta);
void	while_x2(t_data *data, t_player player, double theta);
void	while_x3(t_data *data, t_player player, double theta);
void	while_x4(t_data *data, t_player player, double theta);

/*
** pixel_put_wall.c
*/
void	pixel_put_wall_x(t_data *data, double distance, double theta, int i);
void	pixel_put_wall_y(t_data *data, double distance, double theta, int i);
void	remove_pixel_put_wall(t_data *data, int short_d, int i);

/*
**stopping.c
*/
int		go_stopping(t_map map, t_player player);
int		back_stopping(t_map map, t_player player);
int		left_stopping(t_map map, t_player player);
int		right_stopping(t_map map, t_player player);

/*
**moving.c
*/
void	moving(t_data *data, t_player *player);
void	moving_helper(t_data *data, t_player *player);

/*
**find_wall.c
*/
int		check_quard(double theta);
void	remove_find_wall(t_data *data, t_player player, double theta, int i);
void	find_wall(t_data *data, t_player player, double theta, int i);
void	find_wall_34(t_data *data, t_player player, double theta, int i);

/*
**setting.c
*/
void	img_set(t_data *data);
void	dataset(t_data *data);

#endif