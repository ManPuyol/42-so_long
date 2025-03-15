#include "../so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		error_msg("Usage: ./so_long map_file.ber");
		return (1);
	}
	
	game.moves = 0;
	if (!parse_map(&game, argv[1]))
		return (1);
	
	if (!init_game(&game))
	{
		free_map(&game);
		return (1);
	}
	
	if (!init_images(&game))
	{
		close_game(&game);
		return (1);
	}
	
	render_map(&game);
	mlx_hook(game.win, 2, 1L<<0, handle_input, &game);
	mlx_hook(game.win, 17, 1L<<17, close_game, &game);
	mlx_loop(game.mlx);
	
	return (0);
}
