/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:57:12 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/09 10:46:52 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_error_image(t_data *data)
{
	if (data->image.img_exit)
		mlx_destroy_image(data->mlx_ptr, data->image.img_exit);
	if (data->image.img_wall)
		mlx_destroy_image(data->mlx_ptr, data->image.img_wall);
	if (data->image.img_floor)
		mlx_destroy_image(data->mlx_ptr, data->image.img_floor);
	if (data->image.img_item)
		mlx_destroy_image(data->mlx_ptr, data->image.img_item);
	if (data->image.img_player)
		mlx_destroy_image(data->mlx_ptr, data->image.img_player);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_double_array(data->map, data, -1);
	if (data->map_copy_exist == 1)
		free_double_array(data->map_copy, data, -1);
	exit (EXIT_SUCCESS);
}
