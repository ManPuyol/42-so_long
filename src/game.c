#include "../so_long.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		error_msg("Failed to initialize MLX");
		return (0);
	}
	
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE, 
		game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		error_msg("Failed to create window");
		return (0);
	}
	
	return (1);
}

int	init_images(t_game *game)
{
	game->wall.img = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm", 
		&game->wall.width, &game->wall.height);
	game->player.img = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", 
		&game->player.width, &game->player.height);
	game->collectible.img = mlx_xpm_file_to_image(game->mlx, "assets/collectible.xpm", 
		&game->collectible.width, &game->collectible.height);
	game->exit.img = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm", 
		&game->exit.width, &game->exit.height);
	game->floor.img = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm", 
		&game->floor.width, &game->floor.height);
	
	if (!game->wall.img || !game->player.img || !game->collectible.img
		|| !game->exit.img || !game->floor.img)
	{
		error_msg("Failed to load images");
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
				mlx_put_image_to_window(game->mlx, game->win, game->collectible.img, 
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

void	move_player(t_game *game, int x, int y)
{
	int	new_x;
	int	new_y;
	
	new_x = game->map.player_pos.x + x;
	new_y = game->map.player_pos.y + y;
	
	// Check for wall collision
	if (game->map.grid[new_y][new_x] == '1')
		return;
	
	// Check for exit (can only exit if all collectibles are collected)
	if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->map.collected == game->map.collectibles)
		{
			printf("Game completed in %d moves!\n", game->moves + 1);
			close_game(game);
			exit(0);
		}
		return;
	}
	
	// Check for collectible
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.collected++;
		game->map.grid[new_y][new_x] = '0';
	}
	
	// Update grid and player position
	game->map.grid[game->map.player_pos.y][game->map.player_pos.x] = '0';
	game->map.grid[new_y][new_x] = 'P';
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	
	// Count move
	game->moves++;
	printf("Moves: %d\n", game->moves);
	
	// Render updated map
	render_map(game);
}

int	handle_input(int keysym, t_game *game)
{
	if (keysym == ESC)
		close_game(game);
	else if (keysym == W || keysym == UP)
		move_player(game, 0, -1);
	else if (keysym == A || keysym == LEFT)
		move_player(game, -1, 0);
	else if (keysym == S || keysym == DOWN)
		move_player(game, 0, 1);
	else if (keysym == D || keysym == RIGHT)
		move_player(game, 1, 0);
	
	return (0);
}

int	close_game(t_game *game)
{
	// Clean up images
	if (game->wall.img)
		mlx_destroy_image(game->mlx, game->wall.img);
	if (game->player.img)
		mlx_destroy_image(game->mlx, game->player.img);
	if (game->collectible.img)
		mlx_destroy_image(game->mlx, game->collectible.img);
	if (game->exit.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->floor.img)
		mlx_destroy_image(game->mlx, game->floor.img);
	
	// Clean up window and MLX
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	
	// Free allocated memory
	free_map(game);
	free(game->mlx);
	
	exit(0);
	return (0);
}
