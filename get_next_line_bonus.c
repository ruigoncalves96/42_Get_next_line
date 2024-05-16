/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:05:52 by randrade          #+#    #+#             */
/*   Updated: 2024/05/15 15:56:24 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	{
		free(free_buf);
		return (NULL);
	}
	buf_cleaned = malloc(ft_strlen(buf) + 1);
	if (!buf_cleaned)
		return (NULL);
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
		return (NULL);
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

static char	*buffer_alloc(char *buf, char *str_read)
{
	char	*str_joined;

	if (buf == NULL)
	{
		buf = malloc(ft_strlen(str_read) + 1);
		if (!buf)
		{
			free(str_read);
			return (NULL);
		}
		ft_strlcpy(buf, str_read, ft_strlen(str_read) + 1);
	}
	else
	{
		str_joined = ft_strjoin(buf, str_read);
		free(buf);
		buf = str_joined;
	}
	return (buf);
}

static char	*find_new_line(int fd, char *buf)
{
	char	*str_read;

	while (!ft_check_nl(buf))
	{
		str_read = ft_read_buffer(fd, &buf);
		if (!str_read)
			break ;
		buf = buffer_alloc(buf, str_read);
		if (!buf)
			return (NULL);
		free(str_read);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[4095];
	char		*new_line;

	new_line = NULL;
	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_check_nl(buf[fd]))
	{
		buf[fd] = find_new_line(fd, buf[fd]);
		if (buf[fd] == NULL)
			return (NULL);
	}
	new_line = get_new_line(buf[fd]);
	buf[fd] = clean_buf(buf[fd]);
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
