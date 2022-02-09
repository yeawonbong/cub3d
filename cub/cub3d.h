#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
// # include "./minilibx_mms_20200219/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "./libft/libft.h"

# define KEYPRESS 2
# define REDCROSS 17
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define BITSIZE 64



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

// gcc -lmlx -framework OpenGL -framework Appkit testmain.c map.c libft.a -L. -lgnl
// arch -x86_64 gcc -lmlx -framework OpenGL -framework Appkit testmain.c map.c libft.a -L. -lgnl

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

typedef struct s_mapinfo
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
}			t_mapinfo;

typedef struct	s_map
{
	char		**maparr;
	int			height;
	int			width;

	t_mapinfo	info;
	
}				t_map;

typedef struct	s_data {
	void	*mlx;
	void	*win;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	// int		width;
	// int		height;
	unsigned long	frame;
	int		item;
	int		now;
	int		clear;
	int		wall_x;
	int		wall_y;
	int		short_x;

	t_map		map;
	t_player	player;

	int		m1;
	int		m2;

	float	aim;
	float	rotate_speed;
}				t_data;

void	get_map_info(t_data *data, int fd);
int		isvalid_map(t_map *map, t_player *player);
void	get_map(t_data *data, char *filename);



// typedef struct	s_mlx
// {
// 	void		*mlx_ptr;
// 	void		*window;
// 	int			x;
// 	int			y;
// 	t_map		map;
// 	t_check		*check;
// 	int			loop;
// 	int			change;
// 	int			movement;
// }				t_mlx;

// typedef struct	s_check
// {
// 	int			collectible_num;
// 	int			player_num;
// 	int			exitp_num;
// 	char		curkey;
// }				t_check;

// /*
// **	so_long.c
// */
// int				finish_game(t_mlx *mlx);
// void			move_player(t_mlx *mlx, int	*idx, char c);
// int				get_key(int keycode, t_mlx *mlx);

// /*
// **	sl_set_mlx.c
// */
// void			set_window(t_mlx *mlx);
// int				loop_draw(t_mlx *mlx);

// /*
// **	sl_set_image.c
// */
// int				set_images(t_mlx *mlx);
// void			set_images2(t_mlx *mlx);
// void			set_player(t_mlx *mlx);
// void			set_player2(t_mlx *mlx);
// void			set_player3(t_mlx *mlx);

// /*
// **	sl_get_map.c
// */
// void			map_size(t_map *map, char *filename);
// void			get_map(t_mlx *mlx, char *filename);
// void			draw_map(t_mlx *mlx);

// /*
// **	sl_error_check.c
// */
// void			*maperror(void);
// void			check_wall(t_mlx *mlx);
// void			check(t_mlx *mlx);

// /*
// **	sl_utils.c
// */
// char			*ft_itoa(int n);
// int				ft_strncmp(const char *str1, const char *str2, size_t n);

#endif