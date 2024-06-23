/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:10:34 by bjacobs           #+#    #+#             */
/*   Updated: 2024/06/23 23:17:21 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while  (line)
	{
		printf("[%s]\n", line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (EXIT_SUCCESS);
}
