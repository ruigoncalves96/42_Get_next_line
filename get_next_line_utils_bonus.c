/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:07:09 by randrade          #+#    #+#             */
/*   Updated: 2024/05/15 00:07:16 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_check_nl(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == NULL || src == NULL || !size)
		return (src_len);
	while (*src && --size)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(s1_len + s2_len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, s1_len + 1);
	ft_strlcpy(&(ptr)[ft_strlen(ptr)], s2, s1_len + s2_len + 1);
	return (ptr);
}

char	*ft_read_buffer(int fd, char **buf)
{
	char	*str_read;
	int		bytes_read;

	str_read = malloc(BUFFER_SIZE + 1);
	if (!str_read)
		return (NULL);
	bytes_read = read(fd, str_read, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		if (bytes_read == -1)
		{
			free(*buf);
			*buf = NULL;
		}
		free(str_read);
		return (NULL);
	}
	str_read[bytes_read] = '\0';
	return (str_read);
}
