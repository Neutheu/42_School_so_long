/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:11:38 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/31 11:20:20 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	display_map(t_data *data)
{
	int			x;
	int			y;
	void		*image;

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
				image = data->image.img_exit;
			if (data->map[y][x] == 'C')
				image = data->image.img_item;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				image, x * data->image.img_size, y * data->image.img_size);
			x++;
		}
		x = 0;
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*map_path;

	if (argc == 1)
		ft_printf("Error\nNo map inclued\n");
	if (argc == 2)
	{
		map_path = argv[1];
		if (init_data(&data, map_path) == 0)
			return (0);
		if (final_check(&data, map_path) == 0)
		{
			close_window(&data);
			return (0);
		}
		display_map(&data);
		mlx_loop(data.mlx_ptr);
	}
	if (argc > 2)
		ft_printf("Error\nToo many arguments\n");
	return (0);
}
