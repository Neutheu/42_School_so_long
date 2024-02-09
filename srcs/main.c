/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:11:38 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/08 15:40:13 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;
	char	*map_path;

	if (argc == 1)
		ft_printf("Error\nNo map inclued\n");
	if (argc == 2)
	{
		map_path = argv[1];
		if (init_data(&data, map_path) == 0)
			return (0);
		if (final_check(&data, map_path) == 0)
		{
			close_window(&data, 0);
			return (0);
		}
		display_map(&data);
		mlx_loop(data.mlx_ptr);
	}
	if (argc > 2)
		ft_printf("Error\nToo many arguments\n");
	return (0);
}
