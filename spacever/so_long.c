/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:01:16 by ybong             #+#    #+#             */
/*   Updated: 2021/07/05 16:09:14 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		finish_game(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	exit(EXIT_SUCCESS);
	return (0);
}

void	move_player(t_mlx *mlx, int *idx, char c)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->window);
	mlx->map->maparr[mlx->map->curi][mlx->map->curj] = '0';
	if (c == '-')
		(*idx)--;
	else if (c == '+')
		(*idx)++;
	if ((mlx->map->maparr[mlx->map->curi][mlx->map->curj] == 'E' \
	&& 0 < mlx->check->collectible_num) \
	|| (mlx->map->maparr[mlx->map->curi][mlx->map->curj] == '1'))
	{
		if (c == '-')
			(*idx)++;
		else if (c == '+')
			(*idx)--;
		mlx->map->maparr[mlx->map->curi][mlx->map->curj] = 'P';
		draw_map(mlx);
		return ;
	}
	if (ft_strchr("EB", mlx->map->maparr[mlx->map->curi][mlx->map->curj]))
		finish_game(mlx);
	if (mlx->map->maparr[mlx->map->curi][mlx->map->curj] == 'C')
		mlx->check->collectible_num--;
	mlx->map->maparr[mlx->map->curi][mlx->map->curj] = 'P';
	mlx->movement++;
	draw_map(mlx);
}

int		get_key(int keycode, t_mlx *mlx)
{
	if (keycode == W)
	{
		mlx->check->curkey = 'W';
		move_player(mlx, &mlx->map->curi, '-');
	}
	if (keycode == S)
	{
		mlx->check->curkey = 'S';
		move_player(mlx, &mlx->map->curi, '+');
	}
	if (keycode == A)
	{
		mlx->check->curkey = 'A';
		move_player(mlx, &mlx->map->curj, '-');
	}
	if (keycode == D)
	{
		mlx->check->curkey = 'D';
		move_player(mlx, &mlx->map->curj, '+');
	}
	if (keycode == ESC)
		finish_game(mlx);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_mlx	*mlx;

	if (argc != 2 ||
	ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4) != 0)
	{
		perror("Error\ninvalid input");
		exit(EXIT_FAILURE);
	}
	mlx = malloc(sizeof(t_mlx));
	ft_memset(mlx, 0, sizeof(t_mlx));
	mlx->check = malloc(sizeof(t_check));
	get_map(mlx, argv[1]);
	mlx->mlx_ptr = mlx_init();
	set_window(mlx);
	draw_map(mlx);
	check(mlx);
	mlx_hook(mlx->window, KEYPRESS, 0, &get_key, mlx);
	mlx_hook(mlx->window, REDCROSS, 0, &finish_game, mlx);
	mlx_loop_hook(mlx->mlx_ptr, &loop_draw, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
