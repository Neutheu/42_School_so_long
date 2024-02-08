/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_valid_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:37:28 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/08 10:17:14 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	fill_map_copy(t_data *data, char *map_path, int nb_lines, int fd_map)
{
	int	index;

	index = -1;
	data->map_copy = malloc(nb_lines * sizeof(char *));
	if (!data->map_copy)
		return (-1);
	fd_map = open(map_path, O_RDONLY);
	if (fd_map == -1)
	{
		free(data->map_copy);
		return (-1);
	}
	while (++index < nb_lines)
	{
		data->map_copy[index] = remove_newline(get_next_line(fd_map));
		if (!data->map_copy[index])
			return (free_double_array(data->map_copy, data, index), -1);
	}
	if (close(fd_map) != 0)
		return (free_double_array(data->map_copy, data, 0), -1);
	return (0);
}

int	stock_map_copy(t_data *data, char *map_path)
{
	int		fd_map;
	int		nb_lines;
	char	*line;

	nb_lines = -1;
	line = "line";
	data->check_items = 0;
	data->check_exit = 0;
	fd_map = open(map_path, O_RDONLY);
	if (fd_map == -1)
		return (-1);
	while (line != NULL)
	{
		line = get_next_line(fd_map);
		if (!line)
			return (-1);
		free(line);
		nb_lines++;
	}
	if (close(fd_map) != 0)
		return (-1);
	if (fill_map_copy(data, map_path, nb_lines, fd_map) == -1)
		return (-1);
	return (0);
}

void	p_replace(t_data *data, int x, int y)
{
	if (data->map_copy[y][x] == '0')
		data->map_copy[y][x] = 'P';
	if (data->map_copy[y][x] == 'C')
	{
		data->map_copy[y][x] = 'P';
		data->check_items++;
	}
	if (data->map_copy[y][x] == 'E')
		data->check_exit++;
}

void	p_filling(t_data *data, int x, int y)
{
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			if (data->map_copy[y][x] == 'P')
			{
				p_replace(data, x + 1, y);
				p_replace(data, x - 1, y);
				p_replace(data, x, y + 1);
				p_replace(data, x, y - 1);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int	check_valid_path(t_data *data, char *map_path)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	if (stock_map_copy(data, map_path) == -1)
	{
		ft_printf("Error\nOpening or closing map\n");
		return (0);
	}
	data->map_copy_exist = 1;
	while (i < 500)
	{
		p_filling(data, x, y);
		y = 0;
		i++;
	}
	if (data->check_exit <= 0 || data->check_items != data->item_to_coll)
	{
		ft_printf("Error\nInvalid path in map\n");
		return (0);
	}
	return (1);
}
