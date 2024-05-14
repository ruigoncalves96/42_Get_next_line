/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:48 by randrade          #+#    #+#             */
/*   Updated: 2024/05/13 21:27:16 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_buf(char *buf)
{
	char	*free_buf;
	char	*buf_cleaned;
	int	i;
	int	k;

	if (!*buf)
		return (NULL);
	free_buf = buf;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			break;
		i++;
	}
	buf += i + 1;
	if (!(buf_cleaned = malloc(ft_strlen(buf) + 1)))
		return (NULL);
	k = 0;
	while (buf[k])
	{
		buf_cleaned[k] = buf[k];
		k++;
	}
	buf_cleaned[k] = '\0';
	free(free_buf);
	return (buf_cleaned);
}

static char	*get_new_line(char *buf)
{
	char	*new_line;
	int	len;
	int	i;
	int	k;

	len = 0;
	while (buf[len] != '\n' && buf[len])
		len ++;
	if (buf[len] == '\n')
		len++;
	if (!(new_line = malloc(len + 1)))
			return (NULL);
	i = 0;
	k = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			new_line[k++] = '\n';
			new_line[k] = '\0';
			return (new_line);
		}
		new_line[k++] = buf[i++];
	}
	new_line[k] = '\0';
	return (new_line);
}

static char	*read_file(int fd, char *buf)
{
	char	*str2;
	char	*str3;
	int	bytes_read;

	if (!buf)
	{
		if (!(buf = malloc(BUFFER_SIZE + 1)))
			return (NULL);
		if (!(bytes_read = read(fd, buf, BUFFER_SIZE)))
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = '\0';
	}
	while (!ft_check_nl(buf))
	{
		if (!(str2 = malloc(BUFFER_SIZE + 1)))
		{
			free(buf);
			return (NULL);
		}
		if (!(bytes_read = read(fd, str2, BUFFER_SIZE)))
		{
			free(buf);
			free(str2);
			return (NULL);
		}
		str2[bytes_read] = '\0';
		if (!(str3 = ft_strjoin(buf, str2)))
		{
			free(buf);
			free(str2);
			return (NULL);
		}
		free(buf);
		buf= str3;
		free(str2);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char	*new_line;

	new_line = NULL;
	if (fd < 0 || BUFFER_SIZE == 0 ||  read(fd, NULL, 0) < 0)
		return (NULL);
	if (!ft_check_nl(buf))
	{
		if ((buf = read_file(fd, buf)) == NULL)
			return (NULL);
	}
	new_line = get_new_line(buf);
	buf = clean_buf(buf);
	return (new_line);
}

int	main(void)
{
	int	fd;
	char	*line;
	
	line = NULL;
//	fd = open("text.txt", O_RDONLY);
	fd = open("nl.txt", O_RDONLY);
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
}
