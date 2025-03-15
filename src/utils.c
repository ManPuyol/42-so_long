#include "../so_long.h"

void	error_msg(char *message)
{
	printf("Error\n%s\n", message);
}

void	free_map(t_game *game)
{
	int	i;
	
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height && game->map.grid[i])
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
}
