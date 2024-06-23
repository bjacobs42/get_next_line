/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:55:30 by bjacobs           #+#    #+#             */
/*   Updated: 2022/11/17 17:13:18 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

size_t	ft_strlen(const char *str);

char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
#endif
