/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:20:37 by tibarike          #+#    #+#             */
/*   Updated: 2024/12/04 18:40:03 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*tmp;
	int		index;

	if (!(*buffer) || **buffer == '\0')
		return (NULL);
	index = find_newline(*buffer);
	if (index >= 0)
	{
		line = ft_substr(*buffer, 0, index + 1);
		tmp = ft_substr(*buffer, index + 1, ft_strlen(*buffer) - index - 1);
		free(*buffer);
		*buffer = tmp;
	}
	else
	{
		line = ft_substr(*buffer, 0, ft_strlen(*buffer));
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	size_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (find_newline(buffer) == -1)
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		tmp[read_bytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (NULL);
	}
	free(tmp);
	if (!buffer)
		return (NULL);
	return (extract_line(&buffer));
}
