/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:55:29 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/31 11:16:12 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_shape_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		if ((int)ft_strlen(data->map[i]) != data->map_width || data->map_height == data->map_width)
		{
			ft_printf("Error\nNon-rectangular map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_data_map(t_data *data, int exit_count, int start_position_count)
{
	int	error;

	error = 0;
	if (exit_count != 1)
	{
		ft_printf("Error\nBad number of exit\n");
		error = 1;
	}
	if (start_position_count != 1)
	{
		ft_printf("Error\nBad number of start position\n");
		error = 1;
	}
	if (data->item_to_coll < 1)
	{
		ft_printf("Error\nBad number of item\n");
		error = 1;
	}
	if (error == 1)
		return (0);
	return (1);
}

int	count_and_check_data_map(t_data *data)
{
	int	x;
	int	y;
	int	exit_count;
	int	start_position_count;

	x = 0;
	y = 0;
	exit_count = 0;
	start_position_count = 0;
	while (y < data->map_height)
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'E')
				exit_count++;
			if (data->map[y][x] == 'P')
				start_position_count++;
			x++;
		}
		x = 0;
		y++;
	}
	if (check_data_map(data, exit_count, start_position_count) == 0)
		return (0);
	return (1);
}

int	check_closed_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_width)
	{
		if (data->map[0][i] != '1' || data->map[data->map_height - 1][i] != '1')
		{
			ft_printf("Error\nNon-closed map\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->map_height)
	{
		if (data->map[i][0] != '1' || data->map[i][data->map_width - 1] != '1')
		{
			ft_printf("Error\nNon-closed map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	final_check(t_data *data, char *map_path)
{
	data->map_copy_exist = 0;
	if (check_shape_map(data) == 0)
		return (0);
	if (check_closed_map(data) == 0)
		return (0);
	if (count_and_check_data_map(data) == 0)
		return (0);
	if (check_valid_path(data, map_path) == 0)
		return (0);
	return (1);
}
