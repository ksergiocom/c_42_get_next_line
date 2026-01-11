/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekhudol <sekhudol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:58:47 by sekhudol          #+#    #+#             */
/*   Updated: 2026/01/12 00:58:10 by sekhudol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

char	*join_buffer(char **str, char *buffer)
{
	char	*tmp;

	tmp = malloc(ft_strlen(*str) + ft_strlen(buffer) + 1);
	ft_strlcpy(tmp, *str, ft_strlen(*str) + 1);
	ft_strlcat(tmp, buffer, ft_strlen(*str) + ft_strlen(buffer) + 1);
	free(*str);
	return (tmp);
}

char	*join_linebreak(char **str, char *str_with_linebreak, char **leftover)
{
	char	*tmp;

	tmp = malloc(ft_strlen(*str) - ft_strlen(str_with_linebreak) + 2);
	ft_strlcpy(tmp, *str, ft_strlen(*str) - ft_strlen(str_with_linebreak) + 2);
	str_with_linebreak++;
	*leftover = malloc(ft_strlen(str_with_linebreak) + 1);
	ft_strlcpy(
		*leftover,
		str_with_linebreak,
		ft_strlen(str_with_linebreak) + 1);
	free(*str);
	return (tmp);
}

void	handle_leftover(char **str, char **leftover)
{
	if (*leftover)
	{
		*str = malloc(ft_strlen(*leftover) + 1);
		ft_strlcpy(*str, *leftover, ft_strlen(*leftover) + 1);
		free(*leftover);
		*leftover = NULL;
	}
	else
	{
		*str = malloc(1);
		*str[0] = '\0';
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*leftover;
	char		*str;
	char		*str_with_linebreak;
	int			bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	handle_leftover(&str, &leftover);
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		if (!bytes && !ft_strlen(str))
			return (free(str), free(buffer), NULL);
		str = join_buffer(&str, buffer);
		str_with_linebreak = ft_strchr(str, '\n');
		if (str_with_linebreak)
		{
			str = join_linebreak(&str, str_with_linebreak, &leftover);
			break ;
		}
		if (bytes < BUFFER_SIZE)
			break ;
	}
	return (free(buffer), str);
}
