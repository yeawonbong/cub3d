#include "cub3d.h"

void	moving_helper(t_data *data, t_player *player)
{
	if (player->right == 1 && right_stopping(data->map, *player))
	{
		player->x += cos(player->theta + M_PI / 2) * player->move_speed;
		player->y += sin(player->theta + M_PI / 2) * player->move_speed;
	}
	if (player->left == 1 && left_stopping(data->map, *player))
	{
		player->x += cos(player->theta + 3 * M_PI / 2) * player->move_speed;
		player->y += sin(player->theta + 3 * M_PI / 2) * player->move_speed;
	}
	if (player->up == 1 && go_stopping(data->map, *player))
	{
		player->x += player->vec_x * player->move_speed;
		player->y += player->vec_y * player->move_speed;
	}
	if (player->down == 1 && back_stopping(data->map, *player))
	{
		player->x -= player->vec_x * player->move_speed;
		player->y -= player->vec_y * player->move_speed;
	}
}

void	moving(t_data *data, t_player *player)
{
	int		i;

	player->vec_x = cos(player->theta);
	player->vec_y = sin(player->theta);
	if (player->up || player->down || player->left || player->right \
		|| player->rotate_left || player->rotate_right)
	{
		i = (-1) * data->map.width / 2 - 1;
		while (++i < data->map.width / 2)
			remove_find_wall(data, data->player, data->player.theta \
				+ ((double)i / (data->map.width / 2)) * (M_PI / 6), i);
	}
	if (player->rotate_left == 1)
		player->theta -= data->rotate_speed;
	if (player->rotate_right == 1)
		player->theta += data->rotate_speed;
	moving_helper(data, player);
}
