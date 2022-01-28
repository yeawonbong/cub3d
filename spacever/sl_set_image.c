/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_set_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:07:51 by ybong             #+#    #+#             */
/*   Updated: 2021/07/01 18:08:02 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		set_images(t_mlx *mlx)
{
	int		bitsize;

	bitsize = 64;
	set_player(mlx);
	if (20 < mlx->loop)
	{
		mlx->map->wall = mlx_xpm_file_to_image(mlx->mlx_ptr, \
		"./img/wall/codewall.xpm", &bitsize, &bitsize);
		mlx->map->exitp = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/exit/bye.png", &bitsize, &bitsize);
		mlx->map->blackhole = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/blackhole/blackhole.png", &bitsize, &bitsize);
		mlx->map->collectible = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/collec/mac.png", &bitsize, &bitsize);
	}
	else
		set_images2(mlx);
	mlx->map->floor = mlx_png_file_to_image(mlx->mlx_ptr, \
	"./img/space.png", &bitsize, &bitsize);
	return (0);
}

void	set_images2(t_mlx *mlx)
{
	int		bitsize;

	bitsize = 64;
	mlx->map->wall = mlx_xpm_file_to_image(mlx->mlx_ptr, \
	"./img/wall/codewall2.xpm", &bitsize, &bitsize);
	mlx->map->exitp = mlx_png_file_to_image(mlx->mlx_ptr, \
	"./img/exit/bye2.png", &bitsize, &bitsize);
	mlx->map->blackhole = mlx_png_file_to_image(mlx->mlx_ptr, \
	"./img/blackhole/blackhole2.png", &bitsize, &bitsize);
	mlx->map->collectible = mlx_png_file_to_image(mlx->mlx_ptr, \
	"./img/collec/mac2.png", &bitsize, &bitsize);
}

void	set_player(t_mlx *mlx)
{
	int		bitsize;

	bitsize = BITSIZE;
	if (mlx->check->collectible_num > mlx->change * 2 \
	|| mlx->check->collectible_num == -1)
	{
		if (mlx->check->curkey == 'S')
			mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
			"./img/player/player.png", &bitsize, &bitsize);
		else if (mlx->check->curkey == 'W')
			mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
			"./img/player/playerw.png", &bitsize, &bitsize);
		else if (mlx->check->curkey == 'A')
			mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
			"./img/player/playera.png", &bitsize, &bitsize);
		else if (mlx->check->curkey == 'D')
			mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
			"./img/player/playerd.png", &bitsize, &bitsize);
	}
	else if (mlx->check->collectible_num > mlx->change)
		set_player2(mlx);
	else
		set_player3(mlx);
}

void	set_player2(t_mlx *mlx)
{
	int	bitsize;

	bitsize = BITSIZE;
	if (mlx->check->curkey == 'S')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player2.png", &bitsize, &bitsize);
	else if (mlx->check->curkey == 'W')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player2w.png", &bitsize, &bitsize);
	else if (mlx->check->curkey == 'A')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player2a.png", &bitsize, &bitsize);
	else if (mlx->check->curkey == 'D')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player2d.png", &bitsize, &bitsize);
}

void	set_player3(t_mlx *mlx)
{
	int	bitsize;

	bitsize = BITSIZE;
	if (mlx->check->curkey == 'S')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player3.png", &bitsize, &bitsize);
	else if (mlx->check->curkey == 'W')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player3w.png", &bitsize, &bitsize);
	else if (mlx->check->curkey == 'A')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player3a.png", &bitsize, &bitsize);
	else if (mlx->check->curkey == 'D')
		mlx->map->player = mlx_png_file_to_image(mlx->mlx_ptr, \
		"./img/player/player3d.png", &bitsize, &bitsize);
}
