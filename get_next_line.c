/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:55:15 by bjacobs           #+#    #+#             */
/*   Updated: 2022/11/24 17:10:52 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

static char	*get_newline(char *rem_line)
{
	char	*newline;
	int		i;

	i = 0;
	while (rem_line[i] != '\n' && rem_line[i])
		i++;
	if (rem_line[i] == '\n')
		i++;
	newline = (char *)malloc(sizeof(char) * (i + 1));
	if (!newline)
		return (NULL);
	newline[i] = '\0';
	while (i--)
		newline[i] = rem_line[i];
	return (newline);
}

static char	*get_remainder(char *rem_line, size_t len)
{
	char	*remainder;
	size_t	rem_len;

	if (!rem_line)
		return (NULL);
	rem_len = ft_strlen(&rem_line[len]);
	if (!rem_len)
		return (free(rem_line), NULL);
	remainder = (char *)malloc(sizeof(char) * (rem_len + 1));
	if (!remainder)
		return (free(rem_line), NULL);
	remainder[rem_len] = '\0';
	while (rem_len--)
		remainder[rem_len] = rem_line[len + rem_len];
	return (free(rem_line), remainder);
}

static char	*get_line(char *rem_line, int fd)
{
	char		*buff;
	int			byts_read;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (free(rem_line), NULL);
	byts_read = BUFFER_SIZE;
	while (!ft_strchr(rem_line, '\n') && byts_read == BUFFER_SIZE)
	{
		byts_read = read(fd, buff, BUFFER_SIZE);
		if (byts_read < 0)
			return (free(buff), free(rem_line), NULL);
		else if (byts_read == 0)
			break ;
		buff[byts_read] = '\0';
		rem_line = ft_strjoin(rem_line, buff);
		if (!rem_line)
			return (free(buff), NULL);
	}
	return (free(buff), rem_line);
}

char	*get_next_line(int fd)
{
	static char	*rem_line = NULL;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	rem_line = get_line(rem_line, fd);
	if (!rem_line)
		return (NULL);
	line = get_newline(rem_line);
	if (!line)
		return (free(rem_line), rem_line = NULL, NULL);
	rem_line = get_remainder(rem_line, ft_strlen(line));
	return (line);
}
