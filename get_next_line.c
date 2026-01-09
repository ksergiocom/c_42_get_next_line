/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekhudol <sekhudol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:49:28 by sekhudol          #+#    #+#             */
/*   Updated: 2026/01/09 21:04:39 by sekhudol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			leidos;
	char		*buffer;

	static char	str_previo[BUFFER_SIZE];
	char		*str_resultado;
	char		*str_restante;

	// Inicializar buffer y string.
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	buffer[0] = '\0';

	// Comprobamos si hay algo de otras llamada previa
	if (ft_strlen(str_previo))
	{
		str_resultado = malloc((ft_strlen(str_previo) + 1) * sizeof(char));
		ft_strlcpy(str_resultado, str_previo, ft_strlen(str_previo) + 1);
	}
	else
	{
		str_resultado = malloc(1 * sizeof(char));
		str_resultado[0] = '\0';
	}

	while (1)
	{	
		// Recoger buffer una vez y gestionarlo como str acabado en \0
		leidos = read(fd, buffer, BUFFER_SIZE);
		str_restante = ft_strlchr(buffer, '\n', BUFFER_SIZE);

		// Si encontramos un salto de linea acaba el bucle y haz un caso especial.
		if (str_restante)
			break;

		// Si se lee 0 bytes hay que devolver un NULL
		if (leidos == 0 && !ft_strlen(str_resultado))
			return (NULL);
		
		// Si se lee menos que el BUFFER_SIZE es que estamos al final del fichero.
		if (leidos < BUFFER_SIZE)
		{
			ft_strlcat(str_resultado, buffer, ft_strlen(str_resultado) + leidos + 1);
			str_previo[0] = '\0';
			return str_resultado;
		}


		// Concatenamos el buffer leido
		ft_strlcat(str_resultado, buffer, ft_strlen(str_resultado) + BUFFER_SIZE + 1);
	}
	
	// Cuando encuentres un \n debemos dejar solo la parte de la izquierda (del \n y el mismo).
	ft_strlcat(str_resultado, buffer, ft_strlen(str_resultado) + BUFFER_SIZE - ft_strlen(str_restante) + 2);
	
	// Debemos guardar el restante para usarlo en como str inicial en la siguiente llamada
	str_restante++; // Primero avanzamos el \n
	if(leidos == BUFFER_SIZE) // Si se lee menos que el buffer es que estamos en el final(No necesito restante ya!)
		ft_strlcpy(str_previo, str_restante, ft_strlen(str_restante)+1);

	return str_resultado;
}

int	main(void)
{
	

	// printf("%s", get_next_line(0));
	
	char *str = malloc(1000);
	for (int i=0; i<10; i++){
		str = get_next_line(0);
		if (str)
			printf("%s", str);
		else
			printf("NULL\n");
	}

	return (0);
}
