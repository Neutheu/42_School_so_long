/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:20:35 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/30 15:36:50 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	close_window(t_data *data)
{
	if (data->all_items_collec == 1)
	{
		ft_printf("number of movements = %d\n", data->nb_mouves);
		ft_printf("FINISHED WITH %d MOVEMENTS\n", data->nb_mouves);
	}
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

void	check_exit(t_data *data, char c)
{
	int	y;
	int	x;

	y = data->pos_y;
	x = data->pos_x;
	if (c == 'a' && data->map[y][x - 1] == 'E' && data->all_items_collec == 1)
		close_window(data);
	if (c == 'w' && data->map[y - 1][x] == 'E' && data->all_items_collec == 1)
		close_window(data);
	if (c == 's' && data->map[y + 1][x] == 'E' && data->all_items_collec == 1)
		close_window(data);
	if (c == 'd' && data->map[y][x + 1] == 'E' && data->all_items_collec == 1)
		close_window(data);
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
	if (data->item_collec == data->item_to_coll)
	{
		data->image.img_exit = mlx_xpm_file_to_image(data->mlx_ptr,
		"./assets/opened_exit.xpm", &data->image.width, &data->image.height);
		data->all_items_collec = 1;
	}
}

void	move(t_data *data, char c)
{
	int	y;
	int	x;

	y = data->pos_y;
	x = data->pos_x;
	data->nb_mouves++;
	check_exit(data, c);
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
	ft_printf("number of movements = %d\n", data->nb_mouves);
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
