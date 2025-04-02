/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:52:55 by manorteg          #+#    #+#             */
/*   Updated: 2025/04/02 20:28:47 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	parse_map(t_game *game, char *file_path)
{
	if (!strstr(file_path, ".ber")
		||strcmp(strrchr(file_path, '.'), ".ber") != 0)
	{
		error_msg("Map file must have .ber extension");
		return (0);
	}

	if (!allocate_map(game, file_path))
		return (0);

	if (!fill_map(game, file_path))
	{
		free_map(game);
		return (0);
	}

	if (!validate_map(game))
	{
		free_map(game);
		return (0);
	}

	return (1);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor.img,
				x * TILE_SIZE, y * TILE_SIZE);

			if (game->map.grid[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall.img,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map.grid[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->collectible.img,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map.grid[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit.img,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map.grid[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player.img,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}

	return (1);
}

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
