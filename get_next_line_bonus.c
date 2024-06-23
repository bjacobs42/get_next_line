/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bjacobs <bjacobs@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 15:59:03 by bjacobs       #+#    #+#                 */
/*   Updated: 2022/12/07 15:59:07 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	static char	*rem_lines[4096];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 4095)
		return (NULL);
	rem_lines[fd] = get_line(rem_lines[fd], fd);
	if (!rem_lines[fd])
		return (NULL);
	line = get_newline(rem_lines[fd]);
	if (!line)
		return (free(rem_lines[fd]), rem_lines[fd] = NULL, NULL);
	rem_lines[fd] = get_remainder(rem_lines[fd], ft_strlen(line));
	return (line);
}
