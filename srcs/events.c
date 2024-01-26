/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:20:35 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/25 15:50:04 by nsouchal         ###   ########.fr       */
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
void	move_left(t_data *data)
{
	int	y;
	int	x;
	int i = 0;

	y = data->pos_y;
	x = data->pos_x;
	data->pos_x -= 1;
	data->map[y][x] = '0';
	data->map[y][x - 1] = 'P';
	data->map[1][1] = 'P';
	while(i < 8)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	display_map(data);
}
int	on_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	if (keycode == XK_a)
		move_left(data);
	return (0);
}
