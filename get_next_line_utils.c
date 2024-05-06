/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:04:34 by randrade          #+#    #+#             */
/*   Updated: 2024/05/06 16:44:02 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t  ft_strlcpy(char *dst, const char *src, size_t size)
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= size)
		return (src_len + size);
	else
		size -= dst_len;
	ft_strlcpy(dst + dst_len, src, size);
	return (dst_len + src_len);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int	s1_len;
	int	s2_len;
	
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(s1_len + s2_len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, s1_len + 1);
	ft_strlcat(ptr, s2, s1_len + s2_len + 1);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i])
	        i++;
	if (s[i] != (unsigned char)c)
	        return (NULL);
	return ((char *)s);
}

char    *ft_strdup(const char *s1)
{
        char    *ptr;
        int             size;

        size = ft_strlen(s1);
        ptr = malloc(size + 1);
        if (ptr == NULL)
                return (NULL);
        ft_strlcpy(ptr, s1, size + 1);
        return (ptr);
}
