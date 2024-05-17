/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:48 by randrade          #+#    #+#             */
/*   Updated: 2024/05/17 12:34:16 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_buf(char *buf)
{
	char	*buf_cleaned;
	char	*free_buf;

	free_buf = buf;
	while (*buf)
	{
		if (*buf == '\n')
		{
			buf++;
			break ;
		}
		buf++;
	}
	if (*buf == '\0')
		return (free(free_buf), NULL);
	buf_cleaned = malloc(ft_strlen(buf) + 1);
	if (!buf_cleaned)
		return (free(free_buf), NULL);
	ft_strlcpy(buf_cleaned, buf, ft_strlen(buf) + 1);
	free(free_buf);
	return (buf_cleaned);
}

static char	*get_new_line(char *buf)
{
	char	*new_line;
	int		i;

	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (buf[i] == '\n')
		i++;
	new_line = malloc(i + 1);
	if (!new_line)
		return (free(buf), NULL);
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			new_line[i++] = '\n';
			new_line[i] = '\0';
			return (new_line);
		}
		new_line[i] = buf[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

static char	*find_new_line(int fd, char *buf)
{
	char	*str_read;
	int		bytes_read;

	str_read = malloc(BUFFER_SIZE + 1);
	if (!str_read)
		return (free(buf), NULL);
	while (!ft_check_nl(buf))
	{
		bytes_read = read(fd, str_read, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == -1)
				return (free(str_read), free(buf), NULL);
			break ;
		}
		str_read[bytes_read] = '\0';
		buf = ft_strjoin(buf, str_read);
	}
	free(str_read);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = find_new_line(fd, buf);
	if (!buf)
		return (NULL);
	new_line = get_new_line(buf);
	if (!new_line)
	{
		buf = NULL;
		return (NULL);
	}
	buf = clean_buf(buf);
	return (new_line);
}
/*
int	main(void)
{
	int	fd;
	char	*line;
	
	line = NULL;
//	fd = open("1char.txt", O_RDONLY);
//	fd = open("text.txt", O_RDONLY);
//	fd = open("nl.txt", O_RDONLY);
	fd = open("no_nl.txt", O_RDONLY);
//	fd = open("empty.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
    		free(line);
	}
	close(fd);
	return (0);
}*/
