/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:48 by randrade          #+#    #+#             */
/*   Updated: 2024/05/14 20:11:05 by randrade         ###   ########.fr       */
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

static char	*read_file(int fd, char *buf)
{
	char	*str_read;
	char	*str_joined;
	int	bytes_read;

	if (!(str_read = malloc(BUFFER_SIZE + 1)))
		return (NULL);
	while ((bytes_read = read(fd, str_read, BUFFER_SIZE)) > 0)
	{
		str_read[bytes_read] = '\0';
		if (buf == NULL)
		{
			if (!(buf = malloc(bytes_read + 1)))
			{
				free(str_read);
				return (NULL);
			}
			ft_strlcpy(buf, str_read, bytes_read + 1);
		}
		else
		{
			str_joined = ft_strjoin(buf, str_read);
			free(buf);
			buf = str_joined;
		}
		if (ft_check_nl(buf))
		{
			free (str_read);
			return (buf);
		}
	}
	if (bytes_read == 0)
	{
		free(str_read);
		return (buf);
	}
	else
	{
		free(str_read);
		free(buf);
		return (NULL);
	}
	
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char	*new_line;

	new_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_check_nl(buf))
	{
		buf = read_file(fd, buf);
		if (buf == NULL)
			return (NULL);
	}
	new_line = get_new_line(buf);
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
//	fd = open("no_nl.txt", O_RDONLY);
//	fd = open("empty.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	printf("main %s", line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		printf(". %s", line);
      		free(line);
	}
	close(fd);
	return (0);
}*/
