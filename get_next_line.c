/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:48 by randrade          #+#    #+#             */
/*   Updated: 2024/06/02 11:18:09 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	clean_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	if (buf[i] == '\0')
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		return ;
	}
	ft_strlcpy(buf, &buf[i], ft_strlen(&buf[i]) + 1);
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
			return (free(buf), new_line);
		}
		new_line[i] = buf[i];
		i++;
	}
	new_line[i] = '\0';
	return (free(buf), new_line);
}

static char	*read_new_line(int fd, char *buf)
{
	char	*new_line;
	int		bytes_read;

	new_line = NULL;
	if (buf[0])
		new_line = ft_strjoin(new_line, buf);
	while (!ft_check_nl(buf))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == -1)
			{
				ft_bzero(buf, BUFFER_SIZE + 1);
				return (free(new_line), NULL);
			}
			break ;
		}
		buf[bytes_read] = '\0';
		new_line = ft_strjoin(new_line, buf);
	}
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = read_new_line(fd, buf);
	if (!new_line)
		return (NULL);
	new_line = get_new_line(new_line);
	if (!new_line)
		return (NULL);
	clean_buf(buf);
	return (new_line);
}
