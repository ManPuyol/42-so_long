#include "../includes/so_long.h"

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

// Implementation of get_next_line function (simplified version for this project)
char	*get_next_line(int fd)
{
	char	buffer[4096];
	char	*line;
	int		i;
	int		rd;
	int		count;

	line = NULL;
	rd = read(fd, buffer, 4095);
	if (rd <= 0)
		return (NULL);
	
	buffer[rd] = '\0';
	count = 0;
	while (count < rd && buffer[count] != '\n')
		count++;
	
	line = (char *)malloc(count + 1);
	if (!line)
		return (NULL);
	
	i = 0;
	while (i < count)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	
	return (line);
}
