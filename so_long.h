/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:52:38 by manorteg          #+#    #+#             */
/*   Updated: 2025/04/02 19:31:25 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_image_data
{
	char	*new_data;
	char	*old_data;
	int		new_size_line;
	int		old_size_line;
	int		new_bpp;
	int		old_bpp;
	int		new_endian;
	int		old_endian;
	int		img_width;
	int		img_height;
}	t_image_data;

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

int		parse_map(t_game *game, char *file_path);
int		validate_map(t_game *game);

int		init_game(t_game *game);
int		init_images(t_game *game);
int		render_map(t_game *game);
int		handle_input(int keysym, t_game *game);
int		game_loop(t_game *game);
void	move_player(t_game *game, int x, int y);
int		close_game(t_game *game);

void	error_msg(char *message);
void	free_map(t_game *game);
char	*get_next_line(int fd);
void	resize_image(t_game *game, t_img *img);

#endif
