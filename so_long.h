#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "./src/get_next_line/get_next_line.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define TILE_SIZE 64
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
	int			collected;
	int			exit;
	int			player;
	t_position	player_pos;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		wall;
	t_img		player;
	t_img		collectible;
	t_img		exit;
	t_img		floor;
	int			moves;
}	t_game;

// Map functions
int		parse_map(t_game *game, char *file_path);
int		validate_map(t_game *game);

// Game functions
int		init_game(t_game *game);
int		init_images(t_game *game);
int		render_map(t_game *game);
int		handle_input(int keysym, t_game *game);
int		game_loop(t_game *game);
void	move_player(t_game *game, int x, int y);
int		close_game(t_game *game);

// Utility functions
void	error_msg(char *message);
void	free_map(t_game *game);
char	*get_next_line(int fd);

#endif
