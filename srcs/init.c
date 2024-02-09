/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:17:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/09 10:58:14 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	count_items(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->item_to_coll = 0;
	while (y < data->map_height)
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'C')
				data->item_to_coll++;
			x++;
		}
		x = 0;
		y++;
	}
}

int	fill_map(t_data *data, char *map_path, int nb_lines, int fd_map)
{
	int	index;

	index = -1;
	data->map_height = nb_lines;
	data->map = malloc(nb_lines * sizeof(char *));
	if (!data->map)
		return (-1);
	fd_map = open(map_path, O_RDONLY);
	if (fd_map == -1)
	{
		free(data->map);
		return (-1);
	}
	while (++index < nb_lines)
	{
		data->map[index] = remove_newline(get_next_line(fd_map));
		if (!data->map[index])
			return (free_double_array(data->map, data, index), -1);
	}
	if (close(fd_map) != 0)
		return (free_double_array(data->map, data, -1), -1);
	data->map_width = ft_strlen(data->map[0]);
	return (0);
}

int	stock_map(t_data *data, char *map_path)
{
	int		fd_map;
	int		nb_lines;
	char	*line;

	nb_lines = -1;
	line = "line";
	fd_map = open(map_path, O_RDONLY);
	if (fd_map == -1)
		return (-1);
	while (line != NULL)
	{
		line = get_next_line(fd_map);
		free(line);
		nb_lines++;
	}
	if (nb_lines == 0)
		return (-1);
	if (close(fd_map) != 0)
		return (-1);
	if (fill_map(data, map_path, nb_lines, fd_map) == -1)
		return (-1);
	return (0);
}

void	set_images(t_data *data)
{
	data->image.img_exit = NULL;
	data->image.img_floor = NULL;
	data->image.img_wall = NULL;
	data->image.img_item = NULL;
	data->image.img_player = NULL;
	data->image.img_floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/floor.xpm", &data->image.width, &data->image.height);
	if (!data->image.img_floor)
		return (free_error_image(data));
	data->image.img_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/wall.xpm", &data->image.width, &data->image.height);
	if (!data->image.img_wall)
		return (free_error_image(data));
	data->image.img_item = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/item.xpm", &data->image.width, &data->image.height);
	if (!data->image.img_item)
		return (free_error_image(data));
	data->image.img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/player.xpm", &data->image.width, &data->image.height);
	if (!data->image.img_player)
		return (free_error_image(data));
	data->image.img_exit = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/close_exit.xpm", &data->image.width, &data->image.height);
	if (!data->image.img_exit)
		return (free_error_image(data));
}

int	init_data(t_data *data, char *map_path)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->image.img_size = 50;
	data->item_collec = 0;
	data->all_items_collec = 0;
	data->nb_moves = 0;
	if (stock_map(data, map_path) == -1)
	{
		ft_printf("Error\nOpening or closing map\n");
		mlx_destroy_display(data->mlx_ptr);
		return (free(data->mlx_ptr), 0);
	}
	count_items(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->image.img_size * data->map_width,
			data->image.img_size * data->map_height, "the burger quest");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		return (free_double_array(data->map, data, -1), free(data->mlx_ptr), 0);
	}
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, on_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	return (set_images(data), 1);
}
