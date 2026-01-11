/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekhudol <sekhudol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:56:00 by sekhudol          #+#    #+#             */
/*   Updated: 2026/01/12 00:02:09 by sekhudol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	initial_len_dst;
	size_t	initial_len_src;
	size_t	final_len;
	size_t	j;
	size_t	i;

	initial_len_dst = ft_strlen(dst);
	initial_len_src = ft_strlen(src);
	final_len = initial_len_dst + initial_len_src;
	j = 0;
	if (size <= initial_len_dst)
		return (size + initial_len_src);
	i = initial_len_dst;
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (final_len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	size_t	i;

	if (dsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dsize - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((char) c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		j;
	int		str1_len;
	int		str2_len;
	char	*joined;

	j = 0;
	str1_len = ft_strlen(s1);
	str2_len = ft_strlen(s2);
	joined = malloc((str1_len + str2_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (*s1)
	{
		joined[j] = *s1++;
		j++;
	}
	while (*s2)
	{
		joined[j] = *s2++;
		j++;
	}
	joined[j] = '\0';
	return (joined);
}
