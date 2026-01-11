/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekhudol <sekhudol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:58:47 by sekhudol          #+#    #+#             */
/*   Updated: 2026/01/11 16:04:24 by sekhudol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"

#ifndef BUFFER_SIZE
 #define BUFFER_SIZE = 5
#endif

char *get_next_line(int fd)
{
	char		*buffer;
	static char	*leftover;
	char		*tmp;
	char		*str;
	int			bytes;

	// Buffer para leer.
	buffer = malloc(BUFFER_SIZE + 1);
	
	// Inicializando la linea (¿Exisita restos de anterior llamada?)
	if (leftover && ft_strlen(leftover))
	{
		str = malloc(ft_strlen(leftover) + 1);
		ft_strlcpy(str, leftover, ft_strlen(leftover) + 1);
		free(leftover);
	}
	else
	{
		str = malloc(1);
		str[0] = '\0';
	}


	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';

		char *str_con_salto = ft_strchr(buffer, '\n');
		if (str_con_salto)
		{
			// Nueva string concatenada hasta el \n
			tmp = malloc(ft_strlen(str) + ft_strlen(buffer) + 1);
			ft_strlcpy(tmp, str, ft_strlen(str) + 1);
			ft_strlcat(tmp, buffer, ft_strlen(str) + ft_strlen(buffer) - ft_strlen(str_con_salto) + 2);
			// Guardar el restante para siguiente llamada de GNL
			leftover = malloc(ft_strlen(str_con_salto));
			str_con_salto++;
			ft_strlcpy(leftover, str_con_salto, ft_strlen(str_con_salto) + 1);
			free(str);
			str = tmp;
			break;
		}

		if (!bytes && !ft_strlen(str))
		{
			free(str);
			return (NULL);
		}

		if (bytes < BUFFER_SIZE)
			break;

		tmp = malloc(ft_strlen(str) + ft_strlen(buffer));
		ft_strlcpy(tmp, str, ft_strlen(str) + 1);
		free(str);
		ft_strlcat(tmp, buffer, ft_strlen(tmp) + ft_strlen(buffer) + 1);
		str = tmp;
	}

	free(buffer);

	return str;
}

int main()
{
	char *str = malloc(10000);
	for(int i=0; i < 6; i++)
	{
		str = get_next_line(0);
		if(str)
			printf("%s", str);
		else
			printf("%p", str);
	}
	free(str);
	return (0);
}