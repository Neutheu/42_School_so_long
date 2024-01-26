/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:11:38 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/25 15:15:52 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	display_map(t_data *data)
{
	int			x;
	int			y;
	void	*image;

	x = 0;
	y = 0;
	image = NULL;
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				image = data->image.img_wall;
			if (data->map[y][x] == '0')
				image = data->image.img_floor;
			if (data->map[y][x] == 'P')
			{
				data->pos_x = x;
				data->pos_y = y;
				image = data->image.img_player;
			}
			if (data->map[y][x] == 'E')
				image = data->image.img_closed_exit;
			if (data->map[y][x] == 'C')
				image = data->image.img_item;
			if (!mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				image, x * data->image.img_size, y * data->image.img_size))
					return ;
			x++;
		}
		x = 0;
		y++;
	}
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	display_map(&data);
	// printf("y=%d\n", data.pos_y);
	// printf("x=%d\n", data.pos_x);
	// printf("%c", data.map[data.pos_y][data.pos_x]);
	mlx_loop(data.mlx_ptr);
	// mlx_destroy_window(mlx_ptr, win_ptr);
	// mlx_destroy_display(mlx_ptr);
	// free(mlx_ptr);
	return (0);
}
