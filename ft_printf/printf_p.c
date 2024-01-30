/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:27:05 by nsouchal          #+#    #+#             */
/*   Updated: 2024/01/29 13:32:31 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	printf_p(long unsigned int ptr)
{
	int	result;
	int	x;

	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	x = 'x';
	printf_s("0x");
	result = printf_xlow_xupp(ptr, x);
	return (result + 2);
}
