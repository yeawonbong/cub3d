#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_mlx	*mlx;

	if (argc != 2 ||
	ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
	{
		perror("Error\ninvalid input");
		exit(EXIT_FAILURE);
	}
	mlx = malloc(sizeof(t_mlx));
	ft_memset(mlx, 0, sizeof(t_mlx));
	mlx->check = malloc(sizeof(t_check));
	get_map(mlx, argv[1]);
	mlx->mlx_ptr = mlx_init();
	mlx->x = 200;
	mlx->y = 800;
	mlx->window = mlx_new_window(mlx->mlx_ptr, mlx->x, mlx->y, "test");
	mlx->check->curkey = 'S';
	mlx->check->collectible_num = -1;
	mlx_loop(mlx->mlx_ptr);

	// if (argc != 2 ||
	// ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4) != 0)
	// {
	// 	perror("Error\ninvalid input");
	// 	exit(EXIT_FAILURE);
	// }

	return (0);
}
