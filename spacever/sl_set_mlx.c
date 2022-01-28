/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_set_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybong <ybong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:08:11 by ybong             #+#    #+#             */
/*   Updated: 2021/07/01 21:09:48 by ybong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_window(t_mlx *mlx)
{
	mlx->x = mlx->map->width * BITSIZE;
	mlx->y = mlx->map->height * BITSIZE;
	mlx->window = mlx_new_window(mlx->mlx_ptr, mlx->x, mlx->y, "test");
	mlx->check->curkey = 'S';
	mlx->check->collectible_num = -1;
}

int		loop_draw(t_mlx *mlx)
{
	mlx->loop++;
	if (mlx->loop == 40)
		mlx->loop = 0;
	set_images(mlx);
	draw_map(mlx);
	return (0);
}
