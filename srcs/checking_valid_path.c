/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_valid_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:37:28 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/09 10:48:26 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	copy_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = -1;
	data->check_items = 0;
	data->check_exit = 0;
	data->map_copy = malloc(data->map_height * sizeof(char *));
	if (!data->map_copy)
		return (-1);
	while (y < data->map_height)
	{
		data->map_copy[y] = malloc(data->map_width * sizeof(char));
		if (!data->map_copy[y])
			return (free_double_array(data->map_copy, data, y), -1);
		y++;
	}
	y = -1;
	while (++y < data->map_height)
	{
		while (++x < data->map_width)
			data->map_copy[y][x] = data->map[y][x];
		x = -1;
	}
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

int	check_valid_path(t_data *data)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	if (copy_map(data) == -1)
	{
		ft_printf("Error\nCopying map\n");
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
