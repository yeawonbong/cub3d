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
	t_img		iiii;

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

#endif