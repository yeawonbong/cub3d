/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsikim <minsikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:15:00 by ybong             #+#    #+#             */
/*   Updated: 2022/02/21 12:26:58 by minsikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	get_NO(t_data *data, char *line)
{
	data->map.info.no++;
	data->map.info.north = ft_strtrim(line + 2, " ");
}

void	get_SO(t_data *data, char *line)
{
	data->map.info.so++;
	data->map.info.south = ft_strtrim(line + 2, " ");
}

void	get_WE(t_data *data, char *line)
{
	data->map.info.we++;
	data->map.info.west = ft_strtrim(line + 2, " ");
}

void	get_EA(t_data *data, char *line)
{
	data->map.info.ea++;
	data->map.info.east = ft_strtrim(line + 2, " ");
}
