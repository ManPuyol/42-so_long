/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:52:24 by manorteg          #+#    #+#             */
/*   Updated: 2025/04/02 20:30:39 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	get_map_height(char *file_path)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		height++;
		free(line);
	}

	close(fd);
	return (height);
}

int	allocate_map(t_game *game, char *file_path)
{
	game->map.height = get_map_height(file_path);
	if (game->map.height <= 2)
	{
		error_msg("Map is too small");
		return (0);
	}

	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
	{
		error_msg("Memory allocation failed");
		return (0);
	}

	return (1);
}

int	fill_map(t_game *game, char *file_path)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);

	i = 0;
	while (i < game->map.height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		game->map.grid[i] = strdup(line);
		free(line);
		if (i == 0)
			game->map.width = strlen(game->map.grid[i]);
		else if (strlen(game->map.grid[i]) != (size_t)game->map.width)
		{
			error_msg("Map lines have different lengths");
			close(fd);
			return (0);
		}
		i++;
	}

	game->map.grid[i] = NULL;
	close(fd);
	return (1);
}

static int	count_map_elements(t_game *game)
{
	int	i;
	int	j;

	game->map.collectibles = 0;
	game->map.exit = 0;
	game->map.player = 0;
	game->map.collected = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'C')
				game->map.collectibles++;
			else if (game->map.grid[i][j] == 'E')
				game->map.exit++;
			else if (game->map.grid[i][j] == 'P')
			{
				game->map.player++;
				game->map.player_pos.x = j;
				game->map.player_pos.y = i;
			}
			else if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1')
			{
				error_msg("Map contains invalid characters");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int	i;
	int	j;

	if (!count_map_elements(game))
		return (0);
	if (game->map.collectibles < 1 || game->map.exit != 1 || game->map.player != 1)
	{
		error_msg("Map must have at least 1 collectible, exactly 1 exit and 1 player");
		return (0);
	}
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if ((i == 0 || i == game->map.height - 1 || j == 0 || j == game->map.width - 1)
				&& game->map.grid[i][j] != '1')
			{
				error_msg("Map must be surrounded by walls");
				return (0);
			}
		}
	}
	return (1);
}
