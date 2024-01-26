/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:17:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/26 11:28:08 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	count_items(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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

char	*remove_newline(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line  = NULL;
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

void	stock_map(t_data *data)
{
	int		fd_map;
	int		nb_lines;
	int		index;

	nb_lines = 0;
	index = 0;
	fd_map = open("./maps/map1.ber", O_RDONLY);
	if (fd_map == -1)
		return ;
	while (get_next_line(fd_map))
		nb_lines++;
	if (close(fd_map) != 0)
		return ;
	data->map_height = nb_lines;
	data->map = malloc(nb_lines * sizeof(char *));
	fd_map = open("./maps/map1.ber", O_RDONLY);
	while(index < nb_lines)
	{
		data->map[index] = remove_newline(get_next_line(fd_map));
		index++;
	}
	data->map_width = ft_strlen(data->map[0]);
}

void	set_images(t_data *data)
{
	data->image.img_floor = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/floor.xpm",&data->image.width, &data->image.height);
	data->image.img_wall = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/wall.xpm", &data->image.width, &data->image.height);
	data->image.img_item = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/item.xpm", &data->image.width, &data->image.height);
	data->image.img_player = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/player.xpm", &data->image.width, &data->image.height);
	data->image.img_closed_exit = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/closed_exit.xpm", &data->image.width, &data->image.height);
	data->image.img_opened_exit = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/opened_exit.xpm", &data->image.width, &data->image.height);
}

void	init_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return ;
	data->image.img_size = 50;
	data->item_collec = 0;
	stock_map(data);
	count_items(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->image.img_size * data->map_width, data->image.img_size * data->map_height, "the burger quest");
	if (!data->win_ptr)
		return (free(data->mlx_ptr));
	set_images(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, on_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, (void *) exit, 0);
}
