/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:28:58 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/25 14:34:49 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img_floor;
	void	*img_wall;
	void	*img_item;
	void	*img_player;
	void	*img_closed_exit;
	void	*img_opened_exit;
	int		img_size;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_width;
	int		map_height;
	int		pos_y;
	int		pos_x;
	t_img	image;
}	t_data;

void	init_data(t_data *data);
int		on_keypress(int keycode, t_data *data);
void	display_map(t_data *data);

#endif
