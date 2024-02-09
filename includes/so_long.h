/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:28:58 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/09 10:38:30 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img_floor;
	void	*img_wall;
	void	*img_item;
	void	*img_player;
	void	*img_exit;
	int		img_size;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	char	**map_copy;
	int		map_width;
	int		map_height;
	int		pos_y;
	int		pos_x;
	int		item_collec;
	int		item_to_coll;
	int		all_items_collec;
	int		check_items;
	int		check_exit;
	int		nb_moves;
	int		map_copy_exist;
	t_img	image;
}	t_data;

int		init_data(t_data *data, char *map_path);
int		on_keypress(int keycode, t_data *data);
void	display_map(t_data *data);
int		close_window(t_data *data, int bool_exit);
int		final_check(t_data *data, char *map_path);
char	*remove_newline(char *line);
int		check_valid_path(t_data *data);
void	free_double_array(char **array, t_data *data, int index);
char	*remove_newline(char *line);
void	free_error_image(t_data *data);

#endif
