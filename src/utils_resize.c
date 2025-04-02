/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_resize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:17:21 by manorteg          #+#    #+#             */
/*   Updated: 2025/04/02 19:39:14 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	copy_image_data(t_image_data *data)
{
	int	x;
	int	y;
	int	x_old;
	int	y_old;
	int	new_pos;
	int	old_pos;

	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
		{
			x_old = x * data->img_width / TILE_SIZE;
			y_old = y * data->img_height / TILE_SIZE;
			new_pos = (y * data->new_size_line) + (x * (data->new_bpp / 8));
			old_pos = (y_old * data->old_size_line)
				+ (x_old * (data->old_bpp / 8));
			*(unsigned int *)(data->new_data + new_pos) = *(unsigned int *)(data->old_data + old_pos);
		}
	}
}

void	destroy_old_image(t_game *game, t_img *img, void *new_img)
{
	mlx_destroy_image(game->mlx, img->img);
	img->img = new_img;
	img->width = TILE_SIZE;
	img->height = TILE_SIZE;
}

void	resize_image(t_game *game, t_img *img)
{
	void			*new_img;
	t_image_data	data;

	new_img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!new_img)
		return ;
	data.new_data = mlx_get_data_addr(new_img, &data.new_bpp,
			&data.new_size_line, &data.new_endian);
	data.old_data = mlx_get_data_addr(img->img, &data.old_bpp,
			&data.old_size_line, &data.old_endian);
	data.img_width = img->width;
	data.img_height = img->height;

	copy_image_data(&data);
	destroy_old_image(game, img, new_img);
}
