/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:09:57 by ybong             #+#    #+#             */
/*   Updated: 2021/07/05 16:31:39 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>

# include <stdlib.h>
# include "./minilibx_mms_20200219/mlx.h"
# include "./get_next_line/get_next_line.h"

# define KEYPRESS 2
# define REDCROSS 17
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define BITSIZE 64

typedef struct	s_check
{
	int			collectible_num;
	int			player_num;
	int			exitp_num;
	char		curkey;
}				t_check;

typedef struct	s_map
{
	char		**maparr;
	int			width;
	int			height;

	void		*wall;
	void		*floor;
	void		*collectible;
	void		*player;
	void		*exitp;
	void		*blackhole;

	int			curi;
	int			curj;
}				t_map;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*window;
	int			x;
	int			y;
	t_map		*map;
	t_check		*check;
	int			loop;
	int			change;
	int			movement;
}				t_mlx;

/*
**	so_long.c
*/
int				finish_game(t_mlx *mlx);
void			move_player(t_mlx *mlx, int	*idx, char c);
int				get_key(int keycode, t_mlx *mlx);

/*
**	sl_set_mlx.c
*/
void			set_window(t_mlx *mlx);
int				loop_draw(t_mlx *mlx);

/*
**	sl_set_image.c
*/
int				set_images(t_mlx *mlx);
void			set_images2(t_mlx *mlx);
void			set_player(t_mlx *mlx);
void			set_player2(t_mlx *mlx);
void			set_player3(t_mlx *mlx);

/*
**	sl_get_map.c
*/
void			map_size(t_map *map, char *filename);
void			get_map(t_mlx *mlx, char *filename);
void			draw_map(t_mlx *mlx);

/*
**	sl_error_check.c
*/
void			*maperror(void);
void			check_wall(t_mlx *mlx);
void			check(t_mlx *mlx);

/*
**	sl_utils.c
*/
char			*ft_itoa(int n);
int				ft_strncmp(const char *str1, const char *str2, size_t n);

#endif
