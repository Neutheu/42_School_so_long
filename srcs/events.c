/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:20:35 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/26 11:29:18 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (EXIT_SUCCESS);
}

int	check_valid_move(t_data *data, char c)
{
	int	y;
	int	x;

	y = data->pos_y;
	x = data->pos_x;
	if (c == 'a' && data->map[y][x - 1] != '1' && data->map[y][x - 1] != 'E')
		return (1);
	if (c == 'w' && data->map[y - 1][x] != '1' && data->map[y - 1][x] != 'E')
		return (1);
	if (c == 's' && data->map[y + 1][x] != '1' && data->map[y + 1][x] != 'E')
		return (1);
	if (c == 'd' && data->map[y][x + 1] != '1' && data->map[y][x + 1] != 'E')
		return (1);
	return (0);
}

void	collect_items(t_data *data, char c)
{
	int	y;
	int	x;

	y = data->pos_y;
	x = data->pos_x;
	if (c == 'a' && data->map[y][x - 1] == 'C')
		data->item_collec++;
	if (c == 'w' && data->map[y - 1][x] == 'C')
		data->item_collec++;
	if (c == 's' && data->map[y + 1][x] == 'C')
		data->item_collec++;
	if (c == 'd' && data->map[y][x + 1] == 'C')
		data->item_collec++;
}

void	move(t_data *data, char c)
{
	int	y;
	int	x;

	y = data->pos_y;
	x = data->pos_x;
	if (!check_valid_move(data, c))
		return ;
	collect_items(data, c);
	data->map[y][x] = '0';
	if (c == 'a')
		data->map[y][x - 1] = 'P';
	if (c == 'w')
		data->map[y - 1][x] = 'P';
	if (c == 's')
		data->map[y + 1][x] = 'P';
	if (c == 'd')
		data->map[y][x + 1] = 'P';
	display_map(data);
}

int	on_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	if (keycode == XK_a)
		move(data, 'a');
	if (keycode == XK_w)
		move(data, 'w');
	if (keycode == XK_s)
		move(data, 's');
	if (keycode == XK_d)
		move(data, 'd');
	return (0);
}
