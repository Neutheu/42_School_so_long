/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:24:58 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/07 15:44:48 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_double_array(char **array, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	set_image(t_data *data, int x, int y)
{
	void	*image;

	image = NULL;
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
}

void	display_map(t_data *data)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			set_image(data, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

char	*remove_newline(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = NULL;
	new_line = malloc(ft_strlen(line) * sizeof(char));
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	while (line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

int	close_window(t_data *data, int bool_exit)
{
	if (data->all_items_collec == 1 && bool_exit == 1)
	{
		ft_printf("number of movements = %d\n", data->nb_moves);
		ft_printf("FINISHED WITH %d MOVEMENTS\n", data->nb_moves);
	}
	mlx_destroy_image(data->mlx_ptr, data->image.img_wall);
	mlx_destroy_image(data->mlx_ptr, data->image.img_floor);
	mlx_destroy_image(data->mlx_ptr, data->image.img_item);
	mlx_destroy_image(data->mlx_ptr, data->image.img_player);
	mlx_destroy_image(data->mlx_ptr, data->image.img_exit);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_double_array(data->map, data);
	if (data->map_copy_exist == 1)
		free_double_array(data->map_copy, data);
	exit (EXIT_SUCCESS);
}
