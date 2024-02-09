/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:05:12 by nsouchal          #+#    #+#             */
/*   Updated: 2024/02/08 14:01:39 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_line(char *stock)
{
	int		i;
	char	*line;

	if (!*stock)
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (stock[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (stock[++i] != '\n' && stock[i] != '\0')
		line[i] = stock[i];
	if (stock[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	cut(char *stock)
{
	int		i;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i);
}

char	*fill_stock(int fd, char *stock, char *stash)
{
	int		i;
	ssize_t	read_result;

	i = 0;
	read_result = 1;
	stock = gnl_strdup(stash);
	if (!stock)
		return (NULL);
	while (check_line(stock) == 0 && read_result > 0)
	{
		read_result = read(fd, stash, BUFFER_SIZE);
		if (read_result == -1)
		{
			free(stock);
			while (i <= BUFFER_SIZE)
				stash[i++] = '\0';
			return (NULL);
		}
		stash[read_result] = '\0';
		stock = gnl_strjoin(stock, stash);
		if (!stock)
			return (NULL);
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	char		*stock;
	char		*futur_stash;

	if (fd < 0)
		return (NULL);
	stock = NULL;
	stock = fill_stock(fd, stock, stash);
	if (!stock)
		return (NULL);
	line = extract_line(stock);
	if (*stash && line)
	{
		futur_stash = stock + cut(stock) + 1;
		if (*futur_stash)
			gnl_memmove(stash, futur_stash, gnl_strlen(stock) - cut(stock));
		else
			stash[0] = '\0';
	}
	free(stock);
	return (line);
}
