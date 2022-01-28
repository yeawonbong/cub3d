/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:59:10 by ybong             #+#    #+#             */
/*   Updated: 2021/07/05 16:12:06 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*maperror(void)
{
	perror("Error\nThe map is invalid");
	exit(EXIT_FAILURE);
}

void	check_wall(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < mlx->map->height)
	{
		j = 0;
		while (j < mlx->map->width && \
		(i == 0 || i == mlx->map->height - 1))
		{
			if (mlx->map->maparr[i][j] != '1')
				maperror();
			j++;
		}
		if (mlx->map->maparr[i][0] != '1' \
		|| mlx->map->maparr[i][mlx->map->width - 1] != '1')
			maperror();
		i++;
	}
}

void	check(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (mlx->check->collectible_num < 1 || mlx->check->exitp_num < 1 \
	|| mlx->check->player_num != 1)
		maperror();
	check_wall(mlx);
	mlx->change = mlx->check->collectible_num / 3;
	while (i < mlx->map->height && i < mlx->map->width)
	{
		if (mlx->map->maparr[i][i + mlx->map->width / 3] == '0')
			mlx->map->maparr[i][i + mlx->map->width / 3] = 'B';
		i += 2;
	}
}
