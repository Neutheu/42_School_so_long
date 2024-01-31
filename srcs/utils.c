/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:24:58 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/31 10:55:06 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_double_array(char **array, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
